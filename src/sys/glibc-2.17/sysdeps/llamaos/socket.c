/*
Copyright (c) 2014, William Magato
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

#include <errno.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <netdb.h>

int select (int __nfds, fd_set *__restrict __readfds,
            fd_set *__restrict __writefds,
            fd_set *__restrict __exceptfds,
            struct timeval *__restrict __timeout)
{
  __set_errno (ENOSYS);
   return -1;
}

int socket (int __domain, int __type, int __protocol)
{
  __set_errno (ENOSYS);
   return -1;
}

/* Give the socket FD the local address ADDR (which is LEN bytes long).  */
int bind (int __fd, __CONST_SOCKADDR_ARG __addr, socklen_t __len)
{
  __set_errno (ENOSYS);
   return -1;
}

int accept (int __fd, __SOCKADDR_ARG __addr,
            socklen_t *__restrict __addr_len)
{
  __set_errno (ENOSYS);
   return -1;
}

int connect (int __fd, __CONST_SOCKADDR_ARG __addr, socklen_t __len)
{
  __set_errno (ENOSYS);
   return -1;
}

int listen (int __fd, int __n)
{
  __set_errno (ENOSYS);
   return -1;
}

int shutdown (int __fd, int __how)
{
  __set_errno (ENOSYS);
   return -1;
}

ssize_t recvfrom (int __fd, void *__restrict __buf, size_t __n,
                  int __flags, __SOCKADDR_ARG __addr,
                  socklen_t *__restrict __addr_len)
{
  __set_errno (ENOSYS);
   return -1;
}

ssize_t sendto (int __fd, const void *__buf, size_t __n,
                int __flags, __CONST_SOCKADDR_ARG __addr,
                socklen_t __addr_len)
{
  __set_errno (ENOSYS);
   return -1;
}

in_addr_t inet_addr (const char *__cp)
{
  __set_errno (ENOSYS);
   return 0;
}

//struct hostent *gethostbyname(const char *name)
//{
//   return 0;
//}

int
setsockopt (fd, level, optname, optval, optlen)
     int fd;
     int level;
     int optname;
     const __ptr_t optval;
     socklen_t optlen;
{
  __set_errno (ENOSYS);
  return -1;
}
