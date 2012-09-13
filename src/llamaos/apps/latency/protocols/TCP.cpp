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

#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <sys/time.h>

#include <iostream>
#include <string>

#include "TCP.h"

using namespace std;
using namespace latency;

static const unsigned short PORT = 45150;

static int client_init (const string &ip_addr)
{
   struct sockaddr_in sock_addr;
   memset (&sock_addr, 0, sizeof(struct sockaddr_in));
   sock_addr.sin_family = AF_INET;
   sock_addr.sin_port = htons (PORT);
   sock_addr.sin_addr.s_addr = inet_addr (ip_addr.c_str ());

   if (sock_addr.sin_addr.s_addr == INADDR_NONE)
   {
      cout << "error invalid ip address: " << ip_addr << endl;
   }
   else
   {
      int s = socket (AF_INET, SOCK_STREAM, 0);

      if (-1 == s)
      {
         cout << "error: opening socket." << endl;
      }
      else if (-1 == connect (s, (struct sockaddr *)&sock_addr, sizeof(struct sockaddr_in)))
      {
         cout << "error: connecting socket." << endl;
      }
      else
      {
         int opt = 1;

         if (-1 == setsockopt (s, IPPROTO_TCP, TCP_NODELAY, &opt, sizeof(int)))
         {
            cout << "error: setsockopt TCP_NODELAY." << endl;
         }
         else
         {
            return s;
         }
      }
   }

   return -1;
}

static int server_init ()
{
   struct sockaddr_in sock_addr;
   memset (&sock_addr, 0, sizeof(struct sockaddr_in));
   sock_addr.sin_family = AF_INET;
   sock_addr.sin_port = htons (PORT);
   sock_addr.sin_addr.s_addr = INADDR_ANY;

   int listener = socket (AF_INET, SOCK_STREAM, 0);

   if (-1 == listener)
   {
      cout << "error: opening listening socket." << endl;
   }
   else
   {
      int opt = 1;

      if (-1 == setsockopt (listener, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int)))
      {
         cout << "error: setsockopt SO_REUSEADDR." << endl;
      }
      else if (-1 == bind (listener, (struct sockaddr *)&sock_addr, sizeof(struct sockaddr_in)))
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
         int s = accept (listener, (struct sockaddr *)&sock_addr, &len);

         if (-1 == s)
         {
            cout << "error: accepting socket." << endl;
         }
         else
         {
            close (listener);
            opt = 1;

            if (-1 == setsockopt (s, IPPROTO_TCP, TCP_NODELAY, &opt, sizeof(int)))
            {
               cout << "error: setsockopt TCP_NODELAY." << endl;
            }
            else
            {
               return s;
            }
         }
      }
   }

   return -1;
}

Experiment_tcp::Experiment_tcp (int argc, char **argv)
   :  Experiment(argc, argv),
      client(argc > 3),
      ip_addr(client ? argv[3] : ""),
      socket(client ? client_init(ip_addr) : server_init()),
      buffer(new unsigned char [length])
{

}

Experiment_tcp::~Experiment_tcp ()
{
   delete[] buffer;
}

bool Experiment_tcp::verify ()
{
   // client initiates the trial
   if (client)
   {
      // marks all bytes with alpha chars (a,b,c,...)
      mark_data_alpha (buffer, length);

      // send/recv and verify the data has been changed to numerals (1,2,3,...)
      if (   (send_buffer ())
          && (recv_buffer ())
          && (verify_data_numeric (buffer, length)))
      {
         return true;
      }
   }
   else
   {
      // wait for mesg and verify alpha chars
      if (   (recv_buffer ())
          && (verify_data_alpha (buffer, length)))
      {
         // marks all bytes with numerals and send
         mark_data_numeric (buffer, length);
         return send_buffer ();
      }
   }

   return false;
}

bool Experiment_tcp::run_trials ()
{
   if (client)
   {
      struct timeval tv1;
      struct timeval tv2;
      unsigned long usec1;
      unsigned long usec2;
      bool result;

      // run timed trials
      for (unsigned long i = 0; i < trials; i++)
      {
         gettimeofday (&tv1, 0);
         result = run (i);
         gettimeofday (&tv2, 0);

         if (!result)
         {
            cout << "failed to complete trial " << i << endl;
            return false;
         }

         usec1 = (tv1.tv_sec*1000000) + tv1.tv_usec;
         usec2 = (tv2.tv_sec*1000000) + tv2.tv_usec;

         results [i] = (usec2 >= usec1) ? usec2 - usec1 : 0xFFFFFFFF;
      }

      compute_statistics ();
   }
   else
   {
      for (unsigned long i = 0; i < trials; i++)
      {
         if (!run (i))
         {
            cout << "failed to complete trial " << i << endl;
            return false;
         }
      }
   }

   return true;
}

bool Experiment_tcp::run (unsigned long trial)
{
   // client initiates the trial
   if (client)
   {
      // send/recv mesg, check first "int" in buffer is the trial number just
      // as a low cost sanity check to verify both machines are in sync
      if (   (send_buffer ())
          && (recv_buffer ())
          && (*(reinterpret_cast<unsigned long *>(buffer)) == trial))
      {
         return true;
      }
   }
   else
   {
      // wait for message to arrive
      if (recv_buffer ())
      {
         // place trial number in first "int" for master to verify
         *(reinterpret_cast<unsigned long *>(buffer)) = trial;
         return send_buffer ();
      }
   }

   return true;
}

bool Experiment_tcp::recv_buffer ()
{
   int result;
   unsigned long bytes = 0;

   while (bytes < length)
   {
      result = recv (socket, &buffer [bytes], length - bytes, 0);

      if (result <= 0)
      {
         return false;
      }

      bytes += result;
   }

   return true;
}

bool Experiment_tcp::send_buffer ()
{
   int result;
   unsigned long bytes = 0;

   while (bytes < length)
   {
      result = send (socket, &buffer [bytes], length - bytes, 0);

      if (result < 0)
      {
         return false;
      }

      bytes += result;
   }

   return true;
}

Experiment *Experiment_factory::create (int argc, char **argv)
{
   return new Experiment_tcp (argc, argv);
}
