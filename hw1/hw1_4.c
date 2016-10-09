#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	int money = atoi(argv[1]);
	printf("$20 bills :%d\n", money / 20);
	money %= 20;
	printf("$10 bills :%d\n", money / 10);
	money %= 10;
	printf("$5  bills :%d\n", money / 5);
	money %= 5;
	printf("$1  bills :%d\n", money / 1);
	return 0;
}
