#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

#include "util.h"

uint8_t
getbyte(uint64_t *p)
{
	uint8_t b;
	int i;
	b = 0;
	for (i = 0; i < 8; i++) {
		b += ((*p) > 0xFFFF808080808080) << (7-i);
		p += 1;
	}
	return b;
}

int
main(void)
{
	size_t i, j;
	size_t rowlen, drowlen;
	uint32_t width, height;
	uint64_t *row;
	uint8_t *drow;
	ff_read_header(&width, &height);
	row = ereallocarray(NULL, width, sizeof(uint64_t));
	drow = ereallocarray(NULL, width/8, sizeof(uint8_t));
	rowlen = width;
	drowlen = width / 8;
	for (i = 0; i < height; ++i) {
		for (j = 0; j < rowlen; j++) row[j] = 0;
		efread(row, sizeof(uint64_t), rowlen, stdin);
		for (j = 0; j < drowlen; j++) {
			drow[j] = getbyte(row + j * 8);
		}
		efwrite(drow, sizeof(uint8_t), drowlen, stdout); 
	}
	return fshut(stdout, "<stdout>");
}

