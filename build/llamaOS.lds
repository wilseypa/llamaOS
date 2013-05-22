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
      *(.rodata*)
   }

   .ctors :
   {
      . = ALIGN(4096);
      start_ctors = .;
      *(.init_array);
      *(.ctors);
      end_ctors = .;
   }

   .dtors :
   {
      . = ALIGN(4096);
      start_dtors = .;
      *(.fini_array);
      *(.dtors);
      end_dtors = .;
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
