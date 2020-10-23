OUTPUT_FORMAT("binary")
SECTIONS
{
        . = 0x10000;
        .text : ALIGN(0x10000) {
    _TEXT_START_ = .;
    *(.text)
    _TEXT_END_ = .;
    }
}