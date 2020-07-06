CC = gcc
CFLAGS = -g

all: ThreadRun ThreadJoin MultiThreadRun MultiThreadJoin MultiThreadYield

ThreadRun: ThreadRun.c my_pthread.h my_pthread.c
	$(CC) $(CFLAGS) ThreadRun.c my_pthread.c -o ThreadRun

ThreadJoin: ThreadJoin.c my_pthread.h my_pthread.c
	$(CC) $(CFLAGS) ThreadJoin.c my_pthread.c -o ThreadJoin

MultiThreadRun: MultiThreadRun.c my_pthread.h my_pthread.c
	$(CC) $(CFLAGS) MultiThreadRun.c my_pthread.c -o MultiThreadRun

MultiThreadJoin: MultiThreadJoin.c my_pthread.h my_pthread.c
	$(CC) $(CFLAGS) MultiThreadJoin.c my_pthread.c -o MultiThreadJoin

MultiThreadYield: MultiThreadYield.c my_pthread.h my_pthread.c
	$(CC) $(CFLAGS) MultiThreadYield.c my_pthread.c -o MultiThreadYield

run:
	./ThreadRun
clean:
	rm -f ThreadRun ThreadJoin MultiThreadRun MultiThreadJoin MultiThreadYield
