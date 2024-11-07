SECTIONS
{
    .text : {
        KEEP(*(.text.syscall.c))
        *(.text.*)
    }
}
