/*
 * Milkymist VJ SoC (OHCI firmware)
 * Copyright (C) 2007, 2008, 2009, 2010 Sebastien Bourdeauducq
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "progmem.h"

#define REG_DEBUG *((volatile char *)0x1000)

static char debug_buffer[256];
static unsigned char debug_consume;
static unsigned char debug_produce;

void debug_service()
{
	if((debug_consume != debug_produce) && (REG_DEBUG == 0x00)) {
		REG_DEBUG = debug_buffer[debug_consume];
		debug_consume++;
	}
}

void print_char(char c)
{
	debug_buffer[debug_produce] = c;
	debug_produce++;
}

void print_string(const char *s) /* in program memory */
{
	char c;
	
	while(c = read_pgm_byte(s)) {
		print_char(c);
		s++;
	}
}

static const char hextab[] PROGMEM = "0123456789ABCDEF";

void print_hex(unsigned char h)
{
	print_char(read_pgm_byte(&hextab[(h & 0xf0) >> 4]));
	print_char(read_pgm_byte(&hextab[h & 0x0f]));
}
