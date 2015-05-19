
CC=gcc

pupil.o: pupil.c pupil.h
	$(CC) -c pupil.c

bidirectional_list.o: bidirectional_list.c bidirectional_list.h
	$(CC) -c bidirectional_list.c

example.o: example.c bidirectional_list.h pupil.h
	$(CC) -c example.c

example: example.o pupil.o bidirectional_list.o
	$(CC) -o example example.o pupil.o bidirectional_list.o

sorting.o: sorting.c bidirectional_list.h
	$(CC) -c sorting.c

sorting: sorting.o bidirectional_list.o
	$(CC) -o sorting sorting.o bidirectional_list.o