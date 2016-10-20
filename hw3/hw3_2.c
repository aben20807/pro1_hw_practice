#include <stdio.h>
#include <stdlib.h>

void checkArgument(int);

int main(int argc, char *argv[]){
	checkArgument(argc);
	unsigned u = 0x00000000U;
	unsigned mask = 0x80000000U;
	int i;
	for(i = 0; i < 32; i++)
	{
		//將接收到的 bit 順序印給u，使u內容 = 接收到字串的 32bit 排列
		if(argv[1][i] - '0')u ^= mask;
		mask>>=1;
	}
	float f = *(float*)&u;//利用指標轉換
	printf("%.23e\n", f);//輸出轉換出的float
	return 0;
}

void checkArgument(int argc){
	if(argc != 2){
		printf("Argument error\n");
		exit(1);
	}
}
