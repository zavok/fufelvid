#include <arpa/inet.h>

#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

#include "util.h"

const uint32_t width = 1920;
const uint32_t height = 1080;

void
setbyte(uint8_t b, uint64_t *p)
{
	int i;
	uint8_t f;
	const uint64_t alpha = 0xFFFF000000000000;
	for (i = 0; i < 8; i++) {
		f = 1 && (b & (0x80 >> i));
		*p = alpha | (0x0000FFFFFFFFFFFF * f);
		p += 1;
	} 	
}

int
main(void)
{
	size_t i, j;
	size_t rowlen, drowlen;
	uint64_t *row;
	uint8_t *drow;
	ff_write_header(width, height);
	row = ereallocarray(NULL, width, sizeof(uint64_t));
	drow = ereallocarray(NULL, width/8, sizeof(uint8_t));
	rowlen = width;
	drowlen = width / 8;
	for (i = 0; i < height; ++i) {
		for (j = 0; j < drowlen; j++) drow[j] = 0;
		fread(drow, sizeof(uint8_t), drowlen, stdin);
		for (j = 0; j < drowlen; j++) {
			setbyte(drow[j], row + j * 8);
		}
		efwrite(row, sizeof(uint64_t), rowlen, stdout);
	}
	return 0;
}

