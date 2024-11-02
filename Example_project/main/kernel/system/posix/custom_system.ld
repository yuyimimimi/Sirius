/* custom_system.ld */
SECTIONS
{
    .text : {
        KEEP(*(.text.custom_system.*))  /* 确保你的实现优先 */
        *(.text.*)                      /* 链接其他所有 .text 段 */
    }
    /* 其他段的定义可以在这里 */
}
