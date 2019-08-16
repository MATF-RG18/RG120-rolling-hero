test: rh.c image.c image.h boundaries.h
	gcc -o test image.c boundaries.c rh.c -Wall -lGL -lGLU -lglut -lm

.PHONY: clean

clean:
	rm -rf *.o *~ test