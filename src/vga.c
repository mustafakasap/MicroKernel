#include "vga.h"

vga_terminal *get_terminal_instance()
{
  static vga_terminal vga;

  return &vga;
}

void terminal_setcolor(vga_terminal *pterm, vga_color fg, vga_color bg)
{
  pterm->terminal_color = MAKE_COLOR(fg, bg);
}

void terminal_initialize(vga_terminal *pterm)
{
  terminal_initialize_with_color(pterm, fg_default_color, bg_default_color);
}

void terminal_clear_buffer(vga_terminal *pterm)
{
  uint32_t idx;
  uint16_t c;

  c = MAKE_VGAENTRY(' ', 0);
  idx = (VGA_HEIGHT * VGA_WIDTH);
  while (idx--)
    {
      pterm->terminal_buffer[idx] = c;
    }
}

void terminal_initialize_with_color(vga_terminal *pterm, vga_color fg, vga_color bg)
{
  pterm->terminal_buffer = (uint16_t*) VGA_BUFFER_MODE;
  pterm->terminal_row = 0;
  pterm->terminal_column = 0;
  terminal_setcolor(pterm, fg, bg);
  terminal_clear_buffer(pterm);
}

void terminal_put_vgaentry_at(vga_terminal *pterm, uint32_t c, vga_color color, size_t x, size_t y)
{
  const size_t index = y * VGA_WIDTH + x;
  if (c == MICRO_CHAR)
    c = 0xE6;
  pterm->terminal_buffer[index] = MAKE_VGAENTRY(c, color);
}

void terminal_putchar(vga_terminal *pterm, uint32_t c)
{
  terminal_putchar_with_color(pterm, c);
}

void terminal_putchar_with_color(vga_terminal *pterm, uint32_t c)
{
  if (c == '\n')
    {
      pterm->terminal_row++;
      pterm->terminal_column = 0;
    }
  else
    {
      terminal_put_vgaentry_at(pterm, c, pterm->terminal_color, pterm->terminal_column, pterm->terminal_row);
      pterm->terminal_column++;
    }
  if (pterm->terminal_column == VGA_WIDTH)
    {
      pterm->terminal_column = 0;
      pterm->terminal_row++;
    }

  if (pterm->terminal_row == VGA_HEIGHT)
    {
      memcpy(pterm->terminal_buffer, pterm->terminal_buffer + VGA_WIDTH, (VGA_WIDTH * (VGA_HEIGHT-1)));
      pterm->terminal_row = 0;
    }
}

void terminal_putstr_with_color(vga_terminal *pterm, const char* data)
{
  size_t datalen = strlen(data);
  for (size_t i = 0; i < datalen; i++)
    terminal_putchar_with_color(pterm, data[i]);
}

void terminal_putstr(vga_terminal *pterm, const char* data)
{
  terminal_putstr_with_color(pterm, data);
}

void printkc(int color, char c) {
  vga_terminal *pterm = get_terminal_instance();
  int lastColor = pterm->terminal_color;

  pterm->terminal_color = color;

  terminal_putchar_with_color(pterm, c);
  pterm->terminal_color = lastColor;
}

void printk(int color, char *str) {
  vga_terminal *pterm = get_terminal_instance();
  int lastColor = pterm->terminal_color;

  pterm->terminal_color = color;
  //TODO call printf of mylib
  terminal_putstr_with_color(pterm, str);
  pterm->terminal_color = lastColor;
}
