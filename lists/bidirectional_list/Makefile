
CC=gcc

pupil.o: pupil.c pupil.h
	$(CC) -c pupil.c

example.o: example.c pupil.o pupil.c pupil.h
	$(CC) -c example.c

example: example.o pupil.o
	$(CC) -o example example.o pupil.o