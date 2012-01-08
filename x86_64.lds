OUTPUT_FORMAT("elf64-x86-64", "elf64-x86-64", "elf64-x86-64")
OUTPUT_ARCH(i386:x86-64)
ENTRY(_start)
SECTIONS
{
   . = 0x0;
   _text = .;
   .text : { *(.text) }
  .ctors : {
        __CTOR_LIST__ = .;
        QUAD((__CTOR_END__ - __CTOR_LIST__) / 8 - 2)
        *(.ctors)
        CONSTRUCTORS
        QUAD(0)
        __CTOR_END__ = .;
        }
   .data : { *(.data) }
   .bss : { *(.bss) }
}
