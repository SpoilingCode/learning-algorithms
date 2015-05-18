
CC=gcc

pupil.o: pupil.c pupil.h
	$(CC) -c pupil.c

example.o: example.c pupil.o pupil.c pupil.h
	$(CC) -c example.c

example: example.o pupil.o
	$(CC) -o example example.o pupil.o

smoke_tests.o: smoke_tests.c pupil.o pupil.c pupil.h
	$(CC) -c smoke_tests.c

smoke_tests: smoke_tests.o pupil.o
	$(CC) -o smoke_tests smoke_tests.o pupil.o

stress_tests.o: stress_tests.c pupil.o pupil.c pupil.h
	$(CC) -c stress_tests.c

stress_tests: stress_tests.o pupil.o
	$(CC) -o stress_tests stress_tests.o pupil.o