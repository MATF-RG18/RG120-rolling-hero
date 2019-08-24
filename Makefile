roll: rh.c image.c image.h boundaries.h sumpoints.h draw.h
	gcc -o roll image.c boundaries.c sumpoints.c draw.c rh.c -Wall -lGL -lGLU -lglut -lm

.PHONY: clean

clean:
	rm -rf *.o *~ roll