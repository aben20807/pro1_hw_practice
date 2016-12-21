main: main.o shuffleDeal.o remain.o
	gcc -o main main.o shuffleDeal.o remain.o

main.o: main.c main.h shuffleDeal.h remain.h
	gcc -c main.c

shuffleDeal.o: shuffleDeal.c shuffleDeal.h
	gcc -c shuffleDeal.c

remain.o: remain.c remain.h
	gcc -c remain.c

clean:
	rm *.o
	rm *.exe
