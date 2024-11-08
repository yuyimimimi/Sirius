SECTIONS
{
    .text : {
        *(.text.your_custom_namespace.*) // 确保你的实现优先
        *(.text.*)
    }
}
