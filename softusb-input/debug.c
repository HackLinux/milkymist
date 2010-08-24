/*
 * Milkymist VJ SoC (USB firmware)
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
#include "comloc.h"

void print_char(char c)
{
	COMLOC_DEBUG(COMLOC_DEBUG_PRODUCE) = c;
	COMLOC_DEBUG_PRODUCE++;
}

void print_string(const char *s) /* in program memory */
{
	char c;
	
	while((c = read_pgm_byte(s))) {
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

void dump_hex(unsigned char *buf, unsigned int len)
{
	unsigned int i;

	for(i=0;i<len;i++) {
		print_hex(buf[i]);
		print_char(' ');
	}
	print_char('\n');
}

void print_bin(unsigned char h, unsigned char count)
{
	unsigned char i;

	h <<= 8-count;
	for(i=0;i<count;i++) {
		print_char(h & 0x80 ? '1' : '0');
		h <<= 1;
	}
}