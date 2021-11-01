#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "keys.h"

enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg)
{
	return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color)
{
	return (uint16_t)uc | (uint16_t)color << 8;
}

size_t strlen(const char* str)
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}

static inline void outb(uint16_t port, uint8_t val)
{
	asm volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}


static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

void terminal_poscursor(size_t row, size_t col) {
	unsigned short position = (row * 80) + col;

	outb(0x3D4, 0x0F);
	outb(0x3D5, (unsigned char)(position & 0xFF));
	
	outb(0x3D4, 0x0E);
	outb(0x3D5, (unsigned char)((position >> 8) & 0xFF));
}

static inline uint8_t inb(uint16_t port)
{
    uint8_t ret;
    asm volatile ( "inb %1, %0" : "=a"(ret) : "Nd"(port) );
    return ret;
}

void terminal_newline()
{
	terminal_row = terminal_row + 1;
	terminal_column = 0;
}

void terminal_initialize(void)
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_buffer = (uint16_t*)0xB8000;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}

void terminal_setcolor(uint8_t color)
{
	terminal_color = color;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}

void terminal_putchar(char c)
{
	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	if (++terminal_column >= VGA_WIDTH) {
		terminal_column = 0;
		if (++terminal_row >= VGA_HEIGHT)
			terminal_row = 0;
	}
}

void terminal_delchar()
{
	terminal_putentryat(' ', terminal_color, --terminal_column, terminal_row);
	if (terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		if (--terminal_row == VGA_HEIGHT)
			terminal_row = 0;
	}
}

void terminal_write(const char* data, size_t size)
{
	for (size_t i = 0; i < size; i++) {
		if (data[i] == '\n') {
			terminal_newline();
		}
		else {
			terminal_putchar(data[i]);
		}
	}
}

void terminal_writestring(const char* data)
{
	terminal_write(data, strlen(data));
	terminal_poscursor(terminal_row, terminal_column);
}

char keyboard_buffer_ps2(){
	switch(inb(0x60)){
		case AKey:
            outb(0x60, 0);
			return 'a';
			
		case BKey:
            outb(0x60, 0);
			return 'b';
			
		case CKey:
            outb(0x60, 0);
			return 'c';
			
		case DKey:
            outb(0x60, 0);
			return 'd';
			
		case EKey:
            outb(0x60, 0);
			return 'e';
			
		case FKey:
            outb(0x60, 0);
			return 'f';
			
		case GKey:
            outb(0x60, 0);
			return 'g';
			
		case HKey:
            outb(0x60, 0);
			return 'h';
			
		case IKey:
            outb(0x60, 0);
			return 'i';
			
		case JKey:
            outb(0x60, 0);
			return 'j';
			
		case KKey:
            outb(0x60, 0);
			return 'k';
			
		case LKey:
            outb(0x60, 0);
			return 'l';
			
		case MKey:
            outb(0x60, 0);
			return 'm';
		case NKey:
            outb(0x60, 0);
			return 'n';
			
		case OKey:
            outb(0x60, 0);
			return 'o';
			
		case PKey:
            outb(0x60, 0);
			return 'p';
			
		case QKey:
            outb(0x60, 0);
			return 'q';
			
		case RKey:
            outb(0x60, 0);
			return 'r';
			
		case SKey:
            outb(0x60, 0);
			return 's';
			
		case TKey:
            outb(0x60, 0);
			return 't';
			
		case UKey:
            outb(0x60, 0);
			return 'u';
			
		case VKey:
            outb(0x60, 0);
			return 'v';
			
		case WKey:
            outb(0x60, 0);
			return 'w';
			
		case XKey:
            outb(0x60, 0);
			return 'x';
			
		case YKey:
            outb(0x60, 0);
			return 'y';
			
		case ZKey:
            outb(0x60, 0);
			return 'z';
			
		case SpaceKey:
            outb(0x60, 0);
			return ' ';
		case BackSpaceKey:
            outb(0x60, 0);
			return 1;
		case 0x1C:
		    outb(0x60, 0);
			return 2;
		default:
		    return 0;
		}
}
char convert_scancode_to_char(volatile unsigned char scancode){
	switch(scancode){
		case AKey:
			return 'a';
		case BKey:
			return 'b';
		case CKey:
			return 'c';
		case DKey:
			return 'd';
		case EKey:
			return 'e';
		case FKey:
			return 'f';
		case GKey:
			return 'g';
		case HKey:
			return 'h';
		case IKey:
			return 'i';
		case JKey:
			return 'j';
		case KKey:
			return 'k';
		case LKey:
			return 'l';
		case MKey:
			return 'm';
		case NKey:
			return 'n';
		case OKey:
			return 'o';
		case PKey:
			return 'p';
		case QKey:
			return 'q';
		case RKey:
			return 'r';
		case SKey:
			return 's';
		case TKey:
			return 't';
		case UKey:
			return 'u';
		case VKey:
			return 'v';
		case WKey:
			return 'w';
		case XKey:
			return 'x';
		case YKey:
			return 'y';
		case ZKey:
			return 'z';
		case SpaceKey:
			return ' ';
		case BackSpaceKey:
			return 1;
		case 0x1C:
			return 2;
		default:
		    return 0;
	}
}
void OffPC(){
	
}
void kernel_main(){
	char buff_command[70];
	volatile unsigned char charcode;
	terminal_initialize(); 
	terminal_writestring("MaDaMiOS");
	terminal_newline();
	terminal_poscursor(terminal_row, terminal_column);
	terminal_writestring("> ");
	terminal_poscursor(terminal_row, terminal_column);
	
	while(1){
		outb(0x20,0x20);
	    charcode = inb(0x60);
		if((charcode & 128) == 128){
			continue;
		}
		charcode = convert_scancode_to_char(charcode);
		
		if(charcode == 0){
			continue;
		}
		
		else if(charcode == 1){
			terminal_delchar();
			terminal_poscursor(terminal_row, terminal_column);
		}
		else if(charcode == 2){
			for(int i = 0; i < 70; ++i){
				buff_command[i] = terminal_buffer[terminal_row * 80 + i + 2];
			}
			if(buff_command[0] == 'i' && buff_command[1] == 'n' && buff_command[2] == 'f' && buff_command[3] == 'o'){
				terminal_newline();
				terminal_writestring("MaDaMiOS");
			}
			else if(buff_command[0] == 'o' && buff_command[1] == 'f' && buff_command[2] == 'f'){
				inb(0x16);
				break;
			}		
			terminal_newline();
			terminal_writestring("> ");
			terminal_poscursor(terminal_row, terminal_column);
		}
		else{
			terminal_putchar(charcode);
			terminal_poscursor(terminal_row, terminal_column);
			
		}
		outb(0x60,0);
	}
}