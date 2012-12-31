/*
Copyright (c) 2012, William Magato
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

   1. Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.

   2. Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER(S) AND CONTRIBUTORS ''AS IS''
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER(S) OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those
of the authors and should not be interpreted as representing official policies,
either expressed or implied, of the copyright holder(s) or contributors.
*/

#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>

#include <cstring>

#include <iostream>
#include <stdexcept>
#include <sstream>

#include <latency/protocols/TCPIP.h>
#include <latency/parse_args.cpp>
#include <latency/verify.h>

using namespace std;
using namespace latency;
using namespace latency::protocols;

Protocol *Protocol::create (int argc, char *argv [])
{
   return new TCPIP (argc, argv);
}

static unsigned char *alloc_buffer ()
{
   void *mem;
   posix_memalign (&mem, 4096, 4096);

   return reinterpret_cast<unsigned char *>(mem);
}

static const unsigned short PORT = 45150;

TCPIP::TCPIP (int argc, char *argv [])
   :  host_ip(parse<string>(argc, argv, "--host-ip", "0.0.0.0")),
      client(host_ip != "0.0.0.0"),
      datagram(parse<bool>(argc, argv, "--udp", false)),
      blocking(parse<bool>(argc, argv, "--blocking", false)),
      buffer(alloc_buffer ()),
      socket(-1)
{
   memset (buffer, '\0', 4096);

   cout << "latency-TCPIP" << endl
        << "  host-ip: " << host_ip
        << ", " << (datagram ? "UDP" : "TCP")
        << ", " << (blocking ? "blocking" : "non-blocking") << endl;
}

TCPIP::~TCPIP ()
{
   free (buffer);
}

bool TCPIP::root_node ()
{
   return client;
}

bool TCPIP::startup (unsigned long max_msg_size)
{
   memset (&sock_addr, 0, sizeof(struct sockaddr_in));
   sock_addr.sin_family = AF_INET;
   sock_addr.sin_port = htons (PORT);
   sock_addr.sin_addr.s_addr = inet_addr (host_ip.c_str ());

   if (sock_addr.sin_addr.s_addr == INADDR_NONE)
   {
      cout << "error invalid ip address: " << host_ip << endl;
   }
   else if (max_msg_size > 4096)
   {
      cout << "max msg size greater than 4K" << endl;
   }
   else if (   (client)
            && (datagram)
            && (!udp_client_init ()))
   {
      cout << "failed to initialize UDP client" << endl;
   }
   else if (   (!client)
            && (datagram)
            && (!udp_server_init ()))
   {
      cout << "failed to initialize UDP server" << endl;
   }
   else if (   (client)
            && (!datagram)
            && (!tcp_client_init ()))
   {
      cout << "failed to initialize TCP client" << endl;
   }
   else if (   (!client)
            && (!datagram)
            && (!tcp_server_init ()))
   {
      cout << "failed to initialize TCP server" << endl;
   }
   else if (   (!blocking)
            && (!set_nonblocking ()))
   {
      cout << "failed to set non-blocking mode" << endl;
   }
   else
   {
      return true;
   }

   if (-1 != socket)
   {
      close (socket);
   }

   return false;
}

bool TCPIP::cleanup ()
{
   if (-1 != socket)
   {
      close (socket);
   }

   return true;
}

bool TCPIP::run_verify (unsigned long msg_size)
{
   // TCP doesn't send anything for a zero length message, so make it 8 bytes
   msg_size = max (8UL, msg_size);

   // client initiates the trial
   if (client)
   {
      // marks all bytes with alpha chars (a,b,c,...)
      mark_data_alpha (buffer, msg_size);

      // send/recv and verify the data has been changed to numerals (1,2,3,...)
      if (   (send_buffer (msg_size))
          && (recv_buffer (msg_size))
          && (verify_data_numeric (buffer, msg_size)))
      {
         return true;
      }
   }
   else
   {
      // wait for mesg and verify alpha chars
      if (   (recv_buffer (msg_size))
          && (verify_data_alpha (buffer, msg_size)))
      {
         // marks all bytes with numerals and send
         mark_data_numeric (buffer, msg_size);
         return send_buffer (msg_size);
      }
   }

   return false;
}

bool TCPIP::run_trial (unsigned long msg_size, unsigned long trial_number)
{
   // TCP doesn't send anything for a zero length message, so make it 8 bytes
   msg_size = max (8UL, msg_size);

   // client initiates the trial
   if (client)
   {
      // send/recv mesg, check first "int" in buffer is the trial number just
      // as a low cost sanity check to verify both machines are in sync
      if (   (send_buffer (msg_size))
          && (recv_buffer (msg_size))
          && (*(reinterpret_cast<unsigned long *>(buffer)) == trial_number))
      {
         return true;
      }
   }
   else
   {
      // wait for message to arrive
      if (recv_buffer (msg_size))
      {
         // place trial number in first "int" for master to verify
         *(reinterpret_cast<unsigned long *>(buffer)) = trial_number;
         return send_buffer (msg_size);
      }
   }

   return true;
}

bool TCPIP::tcp_client_init ()
{
   socket = ::socket (AF_INET, SOCK_STREAM, 0);

   if (-1 == socket)
   {
      cout << "error: opening socket." << endl;
   }
   else if (-1 == connect (socket,
                           (struct sockaddr *)&sock_addr,
                           sizeof(struct sockaddr_in)))
   {
      cout << "error: connecting socket." << endl;
   }
   else
   {
      int opt = 1;

      if (-1 == setsockopt (socket,
                            IPPROTO_TCP,
                            TCP_NODELAY,
                            &opt,
                            sizeof(int)))
      {
         cout << "error: setsockopt TCP_NODELAY." << endl;
      }
      else
      {
         return true;
      }
   }

   return false;
}

bool TCPIP::tcp_server_init ()
{
   int listener = ::socket (AF_INET, SOCK_STREAM, 0);

   if (-1 == listener)
   {
      cout << "error: opening listening socket." << endl;
   }
   else
   {
      int opt = 1;

      if (-1 == setsockopt (listener,
                            SOL_SOCKET,
                            SO_REUSEADDR,
                            &opt,
                            sizeof(int)))
      {
         cout << "error: setsockopt SO_REUSEADDR." << endl;
      }
      else if (-1 == bind (listener,
                           (struct sockaddr *)&sock_addr,
                           sizeof(struct sockaddr_in)))
      {
         cout << "error: binding socket." << endl;
      }
      else if (-1 == listen (listener, 1))
      {
         cout << "error: listening socket." << endl;
      }
      else
      {
         cout << "waiting for connection..." << endl;

         unsigned int len = 0;
         socket = accept (listener, (struct sockaddr *)&sock_addr, &len);

         if (-1 == socket)
         {
            cout << "error: accepting socket." << endl;
         }
         else
         {
            close (listener);
            opt = 1;

            if (-1 == setsockopt (socket,
                                  IPPROTO_TCP,
                                  TCP_NODELAY,
                                  &opt,
                                  sizeof(int)))
            {
               cout << "error: setsockopt TCP_NODELAY." << endl;
            }
            else
            {
               return true;
            }
         }
      }
   }

   return false;
}

bool TCPIP::udp_client_init ()
{
   socket = ::socket (AF_INET, SOCK_DGRAM, IPPROTO_UDP);

   if (-1 == socket)
   {
      cout << "error: opening socket." << endl;
   }
   else
   {
      return true;
   }

   return false;
}

bool TCPIP::udp_server_init ()
{
   socket = ::socket (AF_INET, SOCK_DGRAM, IPPROTO_UDP);

   if (-1 == socket)
   {
      cout << "error: opening socket." << endl;
   }
   else
   {
      int opt = 1;

      if (-1 == setsockopt (socket,
                            SOL_SOCKET,
                            SO_REUSEADDR,
                            &opt,
                            sizeof(int)))
      {
         cout << "error: setsockopt SO_REUSEADDR." << endl;
      }
      else if (-1 == bind (socket,
                           (struct sockaddr *)&sock_addr,
                           sizeof(struct sockaddr_in)))
      {
         cout << "error: binding socket." << endl;
      }
      else
      {
         return true;
      }
   }

   return false;
}

bool TCPIP::set_nonblocking ()
{
   int opt = 0;

   if (-1 == (opt = fcntl (socket, F_GETFL, 0)))
   {
      printf ("error: fcntl F_GETFL.\n");
   }
   else if (-1 == fcntl (socket, F_SETFL, opt | O_NONBLOCK))
   {
      printf ("error: setting non-blocking socket.\n");
   }
   else
   {
      return true;
   }

   return false;
}

bool TCPIP::recv_buffer (unsigned long length)
{
   if (datagram)
   {
      socklen_t address_len = sizeof(struct sockaddr_in);

      for (;;)
      {
         int result = recvfrom (socket,
                                buffer,
                                length,
                                0,
                                (struct sockaddr *)&sock_addr,
                                &address_len);

         if (   (result == -1)
             && (errno == EAGAIN))
         {
            continue;
         }
         else if (result != static_cast<int>(length))
         {
            return false;
         }

         break;
      }
   }
   else
   {
      unsigned long bytes = 0;

      while (bytes < length)
      {
         int result = recv (socket, &buffer [bytes], length - bytes, 0);

         if (   (result == -1)
             && (errno == EAGAIN))
         {
            continue;
         }
         else if (result <= 0)
         {
            return false;
         }

         bytes += result;
      }
   }

   return true;
}

bool TCPIP::send_buffer (unsigned long length)
{
   if (datagram)
   {
      for (;;)
      {
         int result = sendto (socket,
                              buffer,
                              length,
                              0,
                              (struct sockaddr *)&sock_addr,
                              sizeof(struct sockaddr_in));

         if (   (result == -1)
             && (errno == EAGAIN))
         {
            continue;
         }
         else if (result != static_cast<int>(length))
         {
            return false;
         }

         break;
      }
   }
   else
   {
      unsigned long bytes = 0;

      while (bytes < length)
      {
         int result = send (socket, &buffer [bytes], length - bytes, 0);

         if (result < 0)
         {
            if (   (result == -1)
               && (errno == EAGAIN))
            {
               continue;
            }

            return false;
         }

         bytes += result;
      }
   }

   return true;
}
