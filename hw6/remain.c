#include "remain.h"

void rangeAndSuitOfCard(const int indexOfCard, char *rank, char *suit){
    char suitSymb[4] = {'c', 'd', 'h', 's'};
    switch ((indexOfCard-1)%13 + 1) {
        case 13:
            *rank = 'a';
            break;
        case 12:
            *rank = 'k';
            break;
        case 11:
            *rank = 'q';
            break;
        case 10:
            *rank = 'j';
            break;
        case 9:
            *rank = 't';
            break;
        default:
            *rank = '0'+indexOfCard%13 + 1;
            break;
    }
    *suit = suitSymb[(indexOfCard-1)/13];
}

void printCardsOnHand(const int card[]){
    int i;
    for(i = 0; i < 20; i++){
        if(i%5 == 0){
            printf("P%d: ", i/5+1);
        }
        // printf("%d ", card[i]);//print card index
        char range, suit;
        rangeAndSuitOfCard(card[i], &range, &suit);
        printf("%c%c ", range, suit);
        if(i%5 == 4){
            printf("\n");
        }
    }
}

int scoreOfCardType(const int card[], int pScore[]){
    int i, j;
    int p[4][5];
    for(i = 0; i < 20; i++){
        if(i < 5){
            p[0][i] = card[i];
        }
        else if(i < 10){
            p[1][i-5] = card[i];
        }
        else if(i < 15){
            p[2][i-10] = card[i];
        }
        else{
            p[3][i-15] = card[i];
        }
    }
    int tmp[20];
    qsort(p[0], 5, sizeof(int), cmpfunc);
    qsort(p[1], 5, sizeof(int), cmpfunc);
    qsort(p[2], 5, sizeof(int), cmpfunc);
    qsort(p[3], 5, sizeof(int), cmpfunc);
    for(i = 0; i < 20; i++){
        if(i < 5){
            tmp[i] = p[0][i];
        }
        else if(i < 10){
            tmp[i] = p[1][i-5];
        }
        else if(i < 15){
            tmp[i] = p[2][i-10];
        }
        else{
            tmp[i] = p[3][i-15];
        }
    }
    // printCardsOnHand(tmp);//for debuging: print hand after sorting
    for(i = 0; i < 4; i++){
        if(isStraightFlush(p[i])){
            pScore[i] = getScore(9, getRank(p[i][isStraightFlush(p[i])-1]), getSuitN(p[i][isStraightFlush(p[i])-1]));
        }
        else if(isFourOfAKind(p[i])){
            pScore[i] = getScore(8, getRank(p[i][isFourOfAKind(p[i])-1]), getSuitN(p[i][isFourOfAKind(p[i])-1]));
        }
        else if(isFullHouse(p[i])){
            pScore[i] = getScore(7, getRank(p[i][isFullHouse(p[i])-1]), getSuitN(p[i][isFullHouse(p[i])-1]));
        }
        else if(isFlush(p[i])){
            pScore[i] = getScore(6, getRank(p[i][0]), getSuitN(p[i][0]));
        }
        else if(isStraight(p[i])){
            pScore[i] = getScore(5, getRank(p[i][0]), getSuitN(p[i][0]));
        }
        else if(isThreeOfAKind(p[i])){
            pScore[i] = getScore(4, getRank(p[i][isThreeOfAKind(p[i])-1]), getSuitN(p[i][isThreeOfAKind(p[i])-1]));
        }
        else if(isTwoPairs(p[i])){
            pScore[i] = getScore(3, getRank(p[i][isTwoPairs(p[i])-1]), getSuitN(p[i][isTwoPairs(p[i])-1]));
        }
        else if(isPair(p[i])){
            pScore[i] = getScore(2, getRank(p[i][isPair(p[i])-1]), getSuitN(p[i][isPair(p[i])-1]));
        }
        else{//high card
            int tmpMax = getRank(p[i][0]), k, maxIndex = 0;
            for(k = 1; k < 5; k++){
                if(getRank(p[i][k]) > tmpMax){
                    maxIndex = k;
                    tmpMax = getRank(p[i][k]);
                }
            }
            pScore[i] = getScore(1, getRank(p[i][maxIndex]), getSuitN(p[i][maxIndex]));
        }
    }
    // printf("\n");//for debuging: each score of 4 people
    // for(i = 0; i < 4; i++){
    //     printf("P%d: %d\n", i+1, pScore[i]);
    // }
}

void compareAndPrintResult(const int pScore[]){
    int tmpMax = 0, maxPerson = -1, i;
    for(i = 0; i < 4; i++){
        if(pScore[i] > tmpMax){
            maxPerson = i;
            tmpMax = pScore[i];
        }
    }
    printf("Winner : P%d — ", maxPerson+1);
    switch(pScore[maxPerson]/1000){
        case 9:
            printf("straight flush\n");
            break;
        case 8:
            printf("four-of-a-kind\n");
            break;
        case 7:
            printf("full house\n");
            break;
        case 6:
            printf("flush\n");
            break;
        case 5:
            printf("straight\n");
            break;
        case 4:
            printf("three-of-a-kind\n");
            break;
        case 3:
            printf("two pairs\n");
            break;
        case 2:
            printf("pair\n");
            break;
        case 1:
            printf("high card\n");
            break;
        default:
            break;
    }
}

int cmpfunc (const void * a, const void * b){//sort form big to small
   return ( *(int*)b - *(int*)a );
}

char getSuit(const int n){
    char suitSymb[4] = {'c', 'd', 'h', 's'};
    char suit = suitSymb[(n-1)/13];
    return suit;
}

int getSuitN(const int n){
    return (n-1)/13+1;
}

int getRank(const int n){
    return (n%13 != 0)? n%13: 13;//if A return 13
}

int getScore(const int t, const int h, const int s){
    return t*1000+h*10+s;
}

int isStraightFlush(const int p[]){
    int j;
    if(getSuit(p[0]) == getSuit(p[1]) &&
    getSuit(p[0]) == getSuit(p[2]) &&
    getSuit(p[0]) == getSuit(p[3]) &&
    getSuit(p[0]) == getSuit(p[4]))
    {
        if(getRank(p[0]) == 13 && getRank(p[1]) == 4 && getRank(p[2]) == 3 && getRank(p[3]) == 2 && getRank(p[4]) == 1){//straight flush a1234
            return 2;
        }
        for(j = 0; j < 4; j++){//straight flush
            if(p[j+1] != p[j]-1 ){//order and suit
                return 0;
            }
        }
        return 1;
    }
    else
        return 0;
}

int isFourOfAKind(const int p[]){
    if(getRank(p[0]) == getRank(p[1]) && getRank(p[0]) == getRank(p[2]) && getRank(p[0]) == getRank(p[3])){
        return 1;
    }
    else if(getRank(p[0]) == getRank(p[1]) && getRank(p[0]) == getRank(p[2]) && getRank(p[0]) == getRank(p[4])){//first 4 or last 4
        return 1;
    }
    else if(getRank(p[0]) == getRank(p[1]) && getRank(p[0]) == getRank(p[3]) && getRank(p[0]) == getRank(p[4])){//first 4 or last 4
        return 1;
    }
    else if(getRank(p[0]) == getRank(p[2]) && getRank(p[0]) == getRank(p[3]) && getRank(p[0]) == getRank(p[4])){//first 4 or last 4
        return 1;
    }
    else if(getRank(p[1]) == getRank(p[2]) && getRank(p[1]) == getRank(p[3]) && getRank(p[1]) == getRank(p[4])){//first 4 or last 4
        return 2;
    }
    else
        return 0;
}

int isFullHouse(const int p[]){
    if(getRank(p[0]) == getRank(p[1]) && getRank(p[0]) == getRank(p[2]) && getRank(p[3]) == getRank(p[4])){
        return 1;
    }
    else if(getRank(p[0]) == getRank(p[1]) && getRank(p[0]) == getRank(p[3]) && getRank(p[2]) == getRank(p[4])){
        return 1;
    }
    else if(getRank(p[0]) == getRank(p[1]) && getRank(p[0]) == getRank(p[4]) && getRank(p[2]) == getRank(p[3])){
        return 1;
    }
    else if(getRank(p[0]) == getRank(p[2]) && getRank(p[0]) == getRank(p[3]) && getRank(p[1]) == getRank(p[4])){
        return 1;
    }
    else if(getRank(p[0]) == getRank(p[2]) && getRank(p[0]) == getRank(p[4]) && getRank(p[1]) == getRank(p[3])){
        return 1;
    }
    else if(getRank(p[0]) == getRank(p[3]) && getRank(p[0]) == getRank(p[4]) && getRank(p[1]) == getRank(p[2])){
        return 1;
    }
    else if(getRank(p[1]) == getRank(p[2]) && getRank(p[1]) == getRank(p[3]) && getRank(p[0]) == getRank(p[4])){
        return 2;
    }
    else if(getRank(p[1]) == getRank(p[2]) && getRank(p[1]) == getRank(p[4]) && getRank(p[0]) == getRank(p[3])){
        return 2;
    }
    else if(getRank(p[1]) == getRank(p[3]) && getRank(p[1]) == getRank(p[4]) && getRank(p[0]) == getRank(p[2])){
        return 2;
    }
    else if(getRank(p[2]) == getRank(p[3]) && getRank(p[2]) == getRank(p[4]) && getRank(p[0]) == getRank(p[1])){
        return 3;
    }
    else
        return 0;
}

int isFlush(const int p[]){
    int j;
    for(j = 0; j < 4; j++){//straight flush
        if(((p[j+1]-1)/13) != ((p[j]-1)/13)){//order and suit
            return 0;
        }
    }
    return 1;
}

int isStraight(const int p[]){
    int j;
    if(getRank(p[0]) == 13 && getRank(p[1]) == 4 && getRank(p[2]) == 3 && getRank(p[3]) == 2 && getRank(p[4]) == 1){//a1234
        return 2;
    }
    for(j = 0; j < 4; j++){//straight flush
        if(p[j+1] != p[j]-1){//order and suit
            return 0;
        }
    }
    return 1;
}

int isThreeOfAKind(const int p[]){
    if(getRank(p[0]) == getRank(p[1]) && getRank(p[0]) == getRank(p[2])){
        return 1;
    }
    else if(getRank(p[0]) == getRank(p[1]) && getRank(p[0]) == getRank(p[3])){
        return 1;
    }
    else if(getRank(p[0]) == getRank(p[1]) && getRank(p[0]) == getRank(p[4])){
        return 1;
    }
    else if(getRank(p[0]) == getRank(p[2]) && getRank(p[0]) == getRank(p[3])){
        return 1;
    }
    else if(getRank(p[0]) == getRank(p[2]) && getRank(p[0]) == getRank(p[4])){
        return 1;
    }
    else if(getRank(p[0]) == getRank(p[3]) && getRank(p[0]) == getRank(p[4])){
        return 1;
    }
    else if(getRank(p[1]) == getRank(p[2]) && getRank(p[1]) == getRank(p[3])){
        return 2;
    }
    else if(getRank(p[1]) == getRank(p[2]) && getRank(p[1]) == getRank(p[4])){
        return 2;
    }
    else if(getRank(p[1]) == getRank(p[3]) && getRank(p[1]) == getRank(p[4])){
        return 2;
    }
    else if(getRank(p[2]) == getRank(p[3]) && getRank(p[2]) == getRank(p[4])){
        return 3;
    }
    else
        return 0;
}

int isTwoPairs(const int p[]){
    int i;
    //01
    if(getRank(p[0]) == getRank(p[1]) && getRank(p[2]) == getRank(p[3])){
        i = (getRank(p[0])>getRank(p[2]))? 1: 3;
        return i;
    }
    else if(getRank(p[0]) == getRank(p[1]) && getRank(p[2]) == getRank(p[4])){
        i = (getRank(p[0])>getRank(p[2]))? 1: 3;
        return i;
    }
    else if(getRank(p[0]) == getRank(p[1]) && getRank(p[3]) == getRank(p[4])){
        i = (getRank(p[0])>getRank(p[3]))? 1: 4;
        return i;
    }
    //02
    else if(getRank(p[0]) == getRank(p[2]) && getRank(p[1]) == getRank(p[3])){
        i = (getRank(p[0])>getRank(p[1]))? 1: 2;
        return i;
    }
    else if(getRank(p[0]) == getRank(p[2]) && getRank(p[1]) == getRank(p[4])){
        i = (getRank(p[0])>getRank(p[1]))? 1: 2;
        return i;
    }
    else if(getRank(p[0]) == getRank(p[2]) && getRank(p[3]) == getRank(p[4])){
        i = (getRank(p[0])>getRank(p[3]))? 1: 4;
        return i;
    }
    //03
    else if(getRank(p[0]) == getRank(p[3]) && getRank(p[1]) == getRank(p[2])){
        i = (getRank(p[0])>getRank(p[1]))? 1: 2;
        return i;
    }
    else if(getRank(p[0]) == getRank(p[3]) && getRank(p[1]) == getRank(p[4])){
        i = (getRank(p[0])>getRank(p[1]))? 1: 2;
        return i;
    }
    else if(getRank(p[0]) == getRank(p[3]) && getRank(p[2]) == getRank(p[4])){
        i = (getRank(p[0])>getRank(p[2]))? 1: 3;
        return i;
    }
    //04
    else if(getRank(p[0]) == getRank(p[4]) && getRank(p[1]) == getRank(p[2])){
        i = (getRank(p[0])>getRank(p[1]))? 1: 2;
        return i;
    }
    else if(getRank(p[0]) == getRank(p[4]) && getRank(p[1]) == getRank(p[3])){
        i = (getRank(p[0])>getRank(p[1]))? 1: 2;
        return i;
    }
    else if(getRank(p[0]) == getRank(p[4]) && getRank(p[2]) == getRank(p[3])){
        i = (getRank(p[0])>getRank(p[2]))? 1: 3;
        return i;
    }
    //12
    else if(getRank(p[1]) == getRank(p[2]) && getRank(p[3]) == getRank(p[4])){
        i = (getRank(p[1])>getRank(p[3]))? 2: 4;
        return i;
    }
    //13
    else if(getRank(p[1]) == getRank(p[3]) && getRank(p[2]) == getRank(p[4])){
        i = (getRank(p[1])>getRank(p[2]))? 2: 3;
        return i;
    }
    //14
    else if(getRank(p[1]) == getRank(p[4]) && getRank(p[2]) == getRank(p[3])){
        i = (getRank(p[1])>getRank(p[2]))? 2: 3;
        return i;
    }
    else
        return 0;
}

int isPair(const int p[]){
    if(getRank(p[0]) == getRank(p[1])){
        return 1;
    }
    else if(getRank(p[0]) == getRank(p[2])){
        return 1;
    }
    else if(getRank(p[0]) == getRank(p[3])){
        return 1;
    }
    else if(getRank(p[0]) == getRank(p[4])){
        return 1;
    }
    else if(getRank(p[1]) == getRank(p[2])){
        return 2;
    }
    else if(getRank(p[1]) == getRank(p[3])){
        return 2;
    }
    else if(getRank(p[1]) == getRank(p[4])){
        return 2;
    }
    else if(getRank(p[2]) == getRank(p[3])){
        return 3;
    }
    else if(getRank(p[2]) == getRank(p[4])){
        return 3;
    }
    else if(getRank(p[3]) == getRank(p[4])){
        return 4;
    }
    else
        return 0;
}
