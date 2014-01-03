#ifndef VGA_H
#define VGA_H

#include <stddef.h>
#include <stdint.h>

#define VGA_BUFFER_MODE 0xB8000;

typedef enum e_vga_color
  {
    COLOR_BLACK = 0,
    COLOR_BLUE = 1,
    COLOR_GREEN = 2,
    COLOR_CYAN = 3,
    COLOR_RED = 4,
    COLOR_MAGENTA = 5,
    COLOR_BROWN = 6,
    COLOR_LIGHT_GREY = 7,
    COLOR_DARK_GREY = 8,
    COLOR_LIGHT_BLUE = 9,
    COLOR_LIGHT_GREEN = 10,
    COLOR_LIGHT_CYAN = 11,
    COLOR_LIGHT_RED = 12,
    COLOR_LIGHT_MAGENTA = 13,
    COLOR_LIGHT_BROWN = 14,
    COLOR_WHITE = 15,
  } vga_color;

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static const vga_color fg_default_color = COLOR_LIGHT_GREEN;
static const vga_color bg_default_color = COLOR_BLACK;

uint8_t  make_color(uint8_t fg, uint8_t bg);
uint16_t make_vgaentry(char c, uint8_t color);
void     terminal_clear_buffer();
void     terminal_initialize();
void     terminal_initialize_with_color(vga_color fg, vga_color bg);
void     terminal_setcolor(vga_color fg, vga_color bg);
void     terminal_put_vgaentry_at(char c, vga_color color, size_t x, size_t y);
void     terminal_putchar(char c);
void     terminal_putstr(const char *str);

#endif