\
    CC=gcc
    CFLAGS=-Wall -Wextra -std=c11

    all: student_app

    student_app: main.o student.o
    	$(CC) $(CFLAGS) -o student_app main.o student.o

    main.o: main.c student.h
    	$(CC) $(CFLAGS) -c main.c

    student.o: student.c student.h
    	$(CC) $(CFLAGS) -c student.c

    clean:
    	rm -f *.o student_app
