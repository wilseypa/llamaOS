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

#ifndef llamaos_config_h_
#define llamaos_config_h_

#define __STR(x) #x
#define STR(x) __STR(x)

// llamaOS version
#define LLAMAOS_VERSION_MAJOR 1
#define LLAMAOS_VERSION_MINOR 0
#define LLAMAOS_VERSION_TEXT  "llamaOS-" STR(LLAMAOS_VERSION_MAJOR) "." STR(LLAMAOS_VERSION_MINOR)

#define LLAMAOS_STACK_SIZE     0x1000000  // 16MB
#define LLAMAOS_IRQ_STACK_SIZE 0x400000  // 4MB
//#define LLAMAOS_STACK_SIZE     0x1E00000
//#define LLAMAOS_IRQ_STACK_SIZE 0x10000

#define LLAMAOS_PAGE_SIZE      0x1000  // 4KB

#ifdef __cplusplus

namespace llamaos {

/**
 * @brief llamaOS major version number.
 *
 */
static const unsigned int VERSION_MAJOR = LLAMAOS_VERSION_MAJOR;

/**
 * @brief llamaOS minor version number.
 *
 */
static const unsigned int VERSION_MINOR = LLAMAOS_VERSION_MINOR;

/**
 * @brief llamaOS version text.
 *
 */
static const char VERSION_TEXT[] = LLAMAOS_VERSION_TEXT;

/**
 * @brief General system stack size.
 *
 */
// be sure to make this a power-of-2 number
static const unsigned long STACK_SIZE = LLAMAOS_STACK_SIZE;

/**
 * @brief Interrupt context stack size.
 *
 */
// be sure to make this a power-of-2 number
static const unsigned long IRQ_STACK_SIZE = LLAMAOS_IRQ_STACK_SIZE;

/**
 * @brief System memory page size.
 *
 */
static const unsigned long PAGE_SIZE = LLAMAOS_PAGE_SIZE;

}

#endif  // __cplusplus
#endif  // llamaos_config_h_
