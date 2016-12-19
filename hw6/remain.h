#ifndef REMAIN_H
#define REMAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 52
void rangeAndSuitOfCard(const int, char *, char *);
void printCardsOnHand(const int []);
int scoreOfCardType(const int[]);
int cmpfunc (const void * a, const void * b);
char getSuit(const int);
int isStraightFlush(const int []);
int isFourOfAKind(const int []);
int isFullHouse(const int []);
int isFlush(const int []);
int isStraight(const int []);
int isThreeOfAKind(const int []);
int isTwoPairs(const int []);
int isPair(const int []);
#endif
