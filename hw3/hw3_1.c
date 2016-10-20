#include <stdio.h>
#include <stdlib.h>

void checkArgument(int, int);
void convertIntegToBin(int);
void convertFloatToBin(float);
void printBin(unsigned);

int main(int argc, char *argv[]){
	int N = (argc == 3) ? atoi(argv[1]) : -1;
	checkArgument(argc, N);
	if(N == 1){
		int X = atoi(argv[2]);
		convertIntegToBin(X);
	}
	else if(N == 2){
		float X = atof(argv[2]);
		convertFloatToBin(X);
	}
	else ;
	return 0;
}

void checkArgument(int argc, int N){
	if(argc != 3 || (N != 1 && N != 2)){
		printf("Argument error\n");
		exit(1);
	}
}

void convertIntegToBin(int X){
	unsigned bin = *(unsigned *)&X;
	printBin(bin);
}

void convertFloatToBin(float X){
	unsigned bin = *(unsigned *)&X;
	printBin(bin);
}

void printBin(unsigned bin){
	unsigned mask = 0x80000000U;
	while(mask){
		printf("%d", (bin & mask) != 0U);
		mask >>= 1;
	}
}
