OUTPUT_FORMAT("elf64-x86-64", "elf64-x86-64", "elf64-x86-64")
OUTPUT_ARCH(i386:x86-64)
ENTRY(_start)
SECTIONS
{
   . = 0x0;
   _text = .;
   .text :
   {
      *(.text)
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

   /* Thread Local Storage sections  */
  .tdata	  : { *(.tdata .tdata.* .gnu.linkonce.td.*) }
  .tbss		  : { *(.tbss .tbss.* .gnu.linkonce.tb.*) *(.tcommon) }

  .data :
   {
      *(.data)
   }

   .bss :
   {
      *(.bss)
   }
}
