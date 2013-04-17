/*

Copyright (c) 2013, William Magato
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

OUTPUT_FORMAT("elf64-x86-64", "elf64-x86-64", "elf64-x86-64")
OUTPUT_ARCH(i386:x86-64)
ENTRY(_start)

SECTIONS
{
  . = 0x0;

  /* needs to be at zero so hypercall page is located */
  .absolute :
  {
    *(.absolute)
  }

  .text ALIGN (0x1000) :
  {
    _text = .;
    *(.text)
    *(.gnu.linkonce.t*)
  }

   .ctors :
   {
      __CTOR_LIST__ = .;
      QUAD((__CTOR_END__ - __CTOR_LIST__) / 8 - 2)
      *(.ctors)
      QUAD(0)
      __CTOR_END__ = .;
   }

   .dtors :
   {
      __DTOR_LIST__ = .;
      QUAD((__DTOR_END__ - __DTOR_LIST__) / 8 - 2)
      *(.dtors)
      QUAD(0)
      __DTOR_END__ = .;
   }

/*
  .rodata ALIGN (0x1000) :
  {
    start_ctors = .;
    *(SORT(.ctors*))
    end_ctors = .;

    start_dtors = .;
    *(SORT(.dtors*))
    end_dtors = .;

    *(.rodata*)
    *(.gnu.linkonce.r*)
  }
*/

  .data ALIGN (0x1000) :
  {
    *(.data)
    *(.gnu.linkonce.d*)
  }

  .bss :
  {
    sbss = .;
    *(COMMON)
    *(.bss)
    *(.gnu.linkonce.b*)
    ebss = .;
  }

  /* Thread Local Storage sections  */
  .tdata	  : { *(.tdata .tdata.* .gnu.linkonce.td.*) }
  .tbss		  : { *(.tbss .tbss.* .gnu.linkonce.tb.*) *(.tcommon) }

  /DISCARD/ :
  {
    *(.comment)
  }
}
