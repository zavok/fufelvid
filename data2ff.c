#include <arpa/inet.h>

#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

const char *header = "farbfeld";
const uint32_t width = 1920;
const uint32_t height = 1080;

void
write_header(void)
{
	uint32_t b[2];
	write(1, "farbfeld", 8);
	b[0] = htonl(width);
	b[1] = htonl(height);
	write(1, b, 8);
}


void
convert(uint8_t b, uint16_t *buf)
{
	long i;
	uint16_t chan;
	for (i = 0; i < 8; i++) {
		chan = (b & (1 << i)) ? 0xFFFF : 0x0000;
		buf[i*4] = buf[1+i*4] = buf[2+i*4] = chan;
	}
}

int
main(void)
{
	uint16_t ffbuf[width * 4 * 8];
	uint8_t dbuf[width];
	long n, i;
	write_header();
	total = 0;
	while (total < width * height) {
		for (i = 0; i < width; i++) dbuf[i] = 0;
		for (i = 0; i < width * 4 * 8; i++) {
			ffbuf[i] = (i%4 == 3) ? 0xFFFF : 0x0000;
		}
		n = read(0, dbuf, width);
		if (n == 0) n = width;
		else for (i = 0; i < n; i++) {
			convert(dbuf[i], ffbuf + (i * 4 * 8));
		}
		write(1, ffbuf, n * 4 * 8);
		total += n;
	}
	return 0;
}

