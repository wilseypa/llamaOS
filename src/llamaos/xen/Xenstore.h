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

#ifndef llamaos_xen_xenstore_h_
#define llamaos_xen_xenstore_h_

#include <cstdint>

#include <stdexcept>
#include <iostream>
#include <sstream>
#include <string>

#include <xen/xen.h>
#include <xen/event_channel.h>
#include <xen/io/xs_wire.h>

namespace llamaos {
namespace xen {

/**
 * @brief C++ wrapper class for Xen Xenstore interface.
 *
 */
class Xenstore
{
public:
   /**
    * @brief Constructor.
    *
    * @param interface  Xenstore share page
    * @param port       Xenstore event channel port
    * 
    */
   Xenstore (xenstore_domain_interface *interface, evtchn_port_t port);

   /**
    * @brief Destructor.
    *
    */
   virtual ~Xenstore ();

   void start_transaction (uint32_t id);
   void end_transaction (uint32_t id);

   /**
    * @brief Read information from the Xenstore.
    *
    * @param key
    * 
    * @return value
    *
    */
   std::string read_string (const std::string &key) const;

   template <typename T>
   T read (const std::string &key) const
   {
      T t;
      std::stringstream sstream (read_string (key));

      if ((sstream >> t).fail ())
      {
         // !BAM
         // don't throw for now 
         // throw std::runtime_error ("failed to convert xenstore string to type");
         std::cout << "failed to convert xenstore string to type: " << sstream.str () << std::endl;
         std::cout.flush();
         for (;;);
      }

      return t;
   }

   /**
    * @brief Write information to the Xenstore.
    *
    * @param key
    * @param value
    *
    */
   void write (const std::string &key, const std::string &value) const;

   template <typename T>
   void write (const std::string &key, const T &value) const
   {
      std::stringstream sstream;

      if ((sstream << value).fail ())
      {
         // !BAM
         // don't throw for now 
         // throw std::runtime_error ("failed to convert xenstore type to string");
         std::cout << "failed to convert xenstore string to type: " << sstream.str () << std::endl;
         std::cout.flush();
         for (;;);
      }

      write (key, sstream.str ());
   }

private:
   Xenstore ();
   Xenstore (const Xenstore &);
   Xenstore &operator= (const Xenstore &);

   void write_request (const char *data, unsigned int length) const;
   void write_read_request (const std::string &key) const;
   void write_write_request (const std::string &key, const std::string &value) const;

   void read_response (char *data, unsigned int length) const;
   std::string read_response (unsigned int length) const;
   std::string read_response () const;

   xenstore_domain_interface *const interface;
   const evtchn_port_t port;

};

} }

#endif  // llamaos_xen_xenstore_h_
