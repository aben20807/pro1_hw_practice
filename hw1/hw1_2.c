#include <stdio.h>
#include <stdlib.h>

int power(int x, int n);

int main(int argc, char *argv[]){
	int x = atoi(argv[1]);
	printf("%d", 3 * power(x, 5) + 2 * power(x, 4) - 5 * power(x, 3) - power(x, 2) + 7 * x - 6);
	return 0;
}

int power(int x, int n){
	int s = 1;
	while(n--){
		s *= x;
	}
	return s;
}
