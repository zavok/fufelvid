.POSIX:

REQ = util
BIN = png2ff ff2png data2ff ff2data

CFLAGS = -std=c99 -pedantic -Wall -Wextra -Os
CPPFLAGS = -D_DEFAULT_SOURCE
LDFLAGS = -s
CC = cc

PNG_LDLIBS = -lpng

all: $(BIN)

png2ff-LDLIBS = $(PNG_LDLIBS)
ff2png-LDLIBS = $(PNG_LDLIBS)


png2ff: png2ff.o $(REQ:=.o)
ff2png: ff2png.o $(REQ:=.o)
data2ff: data2ff.o $(REQ:=.o)
ff2data: ff2data.o $(REQ:=.o)

png2ff.o: png2ff.c $(REQ:=.h)
ff2png.o: ff2png.c $(REQ:=.h)
data2ff.o: data2ff.c $(REQ:=.h)
ff2data.o: ff2data.c $(REQ:=.h)

.o:
	$(CC) -o $@ $(LDFLAGS) $< $(REQ:=.o) $($*-LDLIBS)

.c.o:
	$(CC) -c $(CPPFLAGS) $(CFLAGS) $<

clean:
	rm -f $(BIN) $(BIN:=.o) $(REQ:=.o)

