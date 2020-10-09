#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

#include "util.h"

int
main(void)
{
	long i;
	size_t rowlen, drowlen;
	uint32_t width, height;
	uint16_t *row;
	uint8_t *drow;
	ff_read_header(&width, &height);
	row = ereallocarray(NULL, width, (sizeof("RGBA") - 1) * sizeof(uint16_t));
	drow = ereallocarray(NULL, width/8, sizeof(uint8_t));
	rowlen = width * (sizeof("RGBA") - 1);
	drowlen = width / 8;
	for (i = 0; i < height; ++i) {
		efread(row, sizeof(uint16_t), rowlen, stdin);
		efwrite(drow, sizeof(uint16_t), drowlen, stdout); 
	}
	return fshut(stdout, "<stdout>");
}

