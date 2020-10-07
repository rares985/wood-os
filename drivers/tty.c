#include "tty.h"
#include "vga.h"

#define VGA_WIDTH   80
#define VGA_HEIGHT  25
#define VGA_MEM     (uint16_t*) 0xB8000;

static tty_t display;

static void terminal_putentryat(unsigned char uch, uint8_t color, size_t x, size_t y);


static void terminal_putentryat(unsigned char uch, uint8_t color, size_t x, size_t y)
{
    display.buffer[y * VGA_WIDTH + x] = vga_entry(uch, color);
}


void terminal_initialize(void)
{
    size_t index = -1;
    size_t x, y;

    display.row = 0;
    display.col = 0;
    display.color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    display.buffer = VGA_MEM;

    for(y = 0; y < VGA_HEIGHT; y++)
    {
        for (x = 0; x < VGA_WIDTH; x++)
        {
            index = y * VGA_WIDTH + x;
            display.buffer[index] = vga_entry(' ', display.color);
        }
    }
}

void terminal_putchar(char c)
{
    unsigned char uch = c;
    terminal_putentryat(uch, display.color, display.col, display.row);

    /* Scroll when row or screen is filled */
    display.col += 1;
    if (VGA_WIDTH == display.col)
    {
        display.col = 0;
        display.row += 1;
        if (VGA_HEIGHT == display.row)
        {
            display.row = 0;
        }
    }
}

void terminal_write(const char* data, size_t size)
{
    size_t i;
    for (i = 0; i < size; i++)
    {
        terminal_putchar(data[i]);
    }
}

void terminal_writestring(const char* data)
{
    (void)data;
}