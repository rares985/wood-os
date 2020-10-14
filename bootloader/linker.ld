OUTPUT_FORMAT("binary")
SECTIONS
{
        . = 0x1000;
        .text : ALIGN(0x1000) {
    _TEXT_START_ = .;
    *(.text)
    _TEXT_END_ = .;
    }
}