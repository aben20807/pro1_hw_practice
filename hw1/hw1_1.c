#include <stdio.h>
#include <math.h>

#define PI atan(1.0)*4.0

int main(int argc, char *argv[]){
	double r = 10;
	printf("%f\n%f\n", 4 / 3 * PI * r * r * r, 4.0f / 3.0f * PI * r * r * r);
	return 0;
}
