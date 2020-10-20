OUTPUT_FORMAT("binary")
SECTIONS
{
        . = 0xF000;
        .text : ALIGN(0xF000) {
    _TEXT_START_ = .;
    *(.text)
    _TEXT_END_ = .;
    }
}