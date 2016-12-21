#ifndef REMAIN_H
#define REMAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>//for true false
#define SIZE 52
// #define NUM_RANKS 13
// #define NUM_SUITS 4
// #define NUM_CARDS 5

void rangeAndSuitOfCard(const int, char *, char *);
void printCardsOnHand(const int []);
int scoreOfCardType(const int[]);
int cmpfunc (const void * a, const void * b);
char getSuit(const int);
int getSuitN(const int n);
int getRank(const int);
int getScore(const int, const int, const int);
int isStraightFlush(const int []);
int isFourOfAKind(const int []);
int isFullHouse(const int []);
int isFlush(const int []);
int isStraight(const int []);
int isThreeOfAKind(const int []);
int isTwoPairs(const int []);
int isPair(const int []);
#endif
