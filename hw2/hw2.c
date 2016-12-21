#include <stdio.h>
#include <stdlib.h>

int checkArgument(int const, int const, int const);
int solveWeek(int, int);
void printYear(int const);
void printMonth(int const, int const);
int isLeapYear(int const);

char *monthName[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
int monthDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int main(int argc, char *argv[]){
	int year, month, week;
	if(argc == 2){
		year = atoi(argv[1]);
		checkArgument(2, year, 1);
		printYear(year);
	}
	else if(argc == 3){
		year = atoi(argv[1]);
		month = atoi(argv[2]);
		checkArgument(3, year, month);
		printMonth(year, month);
	}
	return 0;
}

int checkArgument(int const argc, int const year, int const month){
	int error = 0;
	switch(argc){
		case 2:
			if(year < 1900)error = 1;
			break;
		case 3:
			if(year < 1900 || month < 0 || month > 12)error = 1;
			break;
		default:
			error = 1;
			break;
	}
	if(error){
		printf("Argument error\n");
		exit(1);
	}
}

int solveWeek(int year, int month){
	int weekDay = -1, day = 1; 
	if(month == 1 || month == 2){
		month += 12;
		year--;
	}
	weekDay = (day + 1 + 2 * month + 3 * (month + 1) / 5 + year + year / 4 - year / 100 + year / 400) % 7;
	return weekDay;
}

void printYear(int const year){//call printMont to print all months
	for(int i = 1; i <= 12; i++){
		printMonth(year, i);
	}
}

void printMonth(int const year, int const month){
	int initWeekDay = solveWeek(year, month);
	int firstSat = (1 + (6 - initWeekDay)) % 7;
	printf("%s\n\n%s\n", monthName[month - 1], "Sun  Mon  Tue  Wed  Thu  Fri  Sat");//print title
	for(int i = 0; i < (3+2)*initWeekDay; i++){
		printf(" ");
	}
	if(isLeapYear(year))//check leap year
		monthDays[2-1] = 29;
	else
		monthDays[2-1] = 28;
	for(int i = 1; i <= monthDays[month - 1]; i++){//print all days
		printf("%3d%s", i, (((i - firstSat) % 7 == 0)?"\n":"  "));
	}
	printf("\n\n");
}

int isLeapYear(int const year){
	if((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
		return 1;
	else
		return 0;
}
