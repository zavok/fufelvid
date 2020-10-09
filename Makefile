
.PHONY=all

all: data2ff ff2data ff2png png2ff

data2ff: data2ff.c
	gcc data2ff.c -o data2ff

ff2data: ff2data.c
	gcc ff2data.c -o ff2data

ff2png:	ff2png.c util.c util.h
	gcc -lpng ff2png.c util.c -o ff2png

png2ff: png2ff.c util.c util.h
	gcc -lpng png2ff.c util.c -o png2ff

clean:
	rm -rf data2ff ff2data ff2png png2ff *.o


