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
            printf("P%d:", i/5+1);
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

int scoreOfCardType(const int card[]){
    int i, j;
    // int p1Score = 9, p2Score = 9, p3Score = 9, p4Score = 9;
    // int p1[5], p2[5], p3[5], p4[5];
    int p[4][5];
    int pScore[4] = {9, 9, 9, 9};
    for(i = 0; i < 20; i++){
        if(i < 5){
            // p1[i] = card[i];
            p[0][i] = card[i];
        }
        else if(i < 10){
            // p2[i-5] = card[i];
            p[1][i-5] = card[i];
        }
        else if(i < 15){
            // p3[i-10] = card[i];
            p[2][i-10] = card[i];
        }
        else{
            // p4[i-15] = card[i];
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
    printCardsOnHand(tmp);

    for(i = 0; i < 4; i++){
        // for(j = 0; j < 4; j++){//straight flush
        //     if(p[i][j+1] != p[i][j]-1 || ((p[i][j+1]-1)/13) != ((p[i][j]-1)/13)){//order and suit
        //         pScore[i]--;
        //         break;
        //     }
        // }
        // if((p[i][0] == 13 && p[i][1] == 4 && p[i][2] == 3 && p[i][3] == 2 && p[i][4] == 1) ||
        //    (p[i][0] == 26 && p[i][1] == 17 && p[i][2] == 16 && p[i][3] == 15 && p[i][4] == 14) ||
        //    (p[i][0] == 39 && p[i][1] == 30 && p[i][2] == 29 && p[i][3] == 28 && p[i][4] == 27) ||
        //    (p[i][0] == 52 && p[i][1] == 43 && p[i][2] == 42 && p[i][3] == 41 && p[i][4] == 40)){//straight flush a1234
        //     pScore[i]++;
        //     // printf("a1234\n");
        // }
        printf("%d ", isStraightFlush(p[i]));
        printf("%d ", isFourOfAKind(p[i]));
        printf("%d ", isFullHouse(p[i]));
        printf("%d ", isFlush(p[i]));
        printf("%d ", isStraight(p[i]));
        printf("%d ", isThreeOfAKind(p[i]));
        printf("%d ", isThreeOfAKind(p[i]));
        printf("%d ", isTwoPairs(p[i]));
        printf("%d\n", isPair(p[i]));
    }
    // for(i = 0; i < 4; i++){
    //     printf("%d\n", pScore[i]);
    // }

}

int cmpfunc (const void * a, const void * b){
   return ( *(int*)b - *(int*)a );
}

char getSuit(const int n){
    char suitSymb[4] = {'c', 'd', 'h', 's'};
    char suit = suitSymb[(n-1)/13];
    return suit;
}

int isStraightFlush(const int p[]){
    int j;
    if((p[0]-1)/13 == (p[1]-1)/13 && (p[0]-1)/13 == (p[2]-1)/13 && (p[0]-1)/13 == (p[3]-1)/13 && (p[0]-1)/13 == (p[4]-1)/13)
    {
        if((p[0] == 13 && p[1] == 4 && p[2] == 3 && p[3] == 2 && p[4] == 1) ||
           (p[0] == 26 && p[1] == 17 && p[2] == 16 && p[3] == 15 && p[4] == 14) ||
           (p[0] == 39 && p[1] == 30 && p[2] == 29 && p[3] == 28 && p[4] == 27) ||
           (p[0] == 52 && p[1] == 43 && p[2] == 42 && p[3] == 41 && p[4] == 40)){//straight flush a1234
            return 1;
            // printf("a1234\n");
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
    if((p[0]%13 == p[1]%13 && p[0]%13 == p[2]%13 && p[0]%13 == p[3]%13) ||
       (p[1]%13 == p[2]%13 && p[1]%13 == p[3]%13 && p[1]%13 == p[4]%13)){//first 4 or last 4
           return 1;
       }
    else
        return 0;
}

int isFullHouse(const int p[]){
    if((p[0]%13 == p[1]%13 && p[0]%13 == p[2]%13 && p[3]%13 == p[4]%13) ||
       (p[2]%13 == p[3]%13 && p[2]%13 == p[4]%13 && p[0]%13 == p[1]%13)){//first 3 or last 3
           return 1;
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
    if((p[0]%13 == 0 && p[1]%13 == 4 && p[2]%13 == 3 && p[3]%13 == 2 && p[4]%13 == 1)){//a1234
        return 1;
        // printf("a1234\n");
    }
    for(j = 0; j < 4; j++){//straight flush
        if(p[j+1] != p[j]-1){//order and suit
            return 0;
        }
    }
    return 1;
}

int isThreeOfAKind(const int p[]){
    if((p[0]%13 == p[1]%13 && p[0]%13 == p[2]%13) ||
       (p[1]%13 == p[2]%13 && p[1]%13 == p[3]%13) ||
       (p[2]%13 == p[3]%13 && p[2]%13 == p[4]%13)){//first 3 or mid 3 or last 3
           return 1;
       }
    else
        return 0;
}

int isTwoPairs(const int p[]){
    if((p[0]%13 == p[1]%13 && p[2]%13 == p[3]%13) ||
       (p[0]%13 == p[1]%13 && p[3]%13 == p[4]%13) ||
       (p[1]%13 == p[2]%13 && p[3]%13 == p[4]%13)){//first 3 or mid 3 or last 3
           return 1;
       }
    else
        return 0;
}

int isPair(const int p[]){
    if((p[0]%13 == p[1]%13 || p[1]%13 == p[2]%13) ||
       (p[2]%13 == p[3]%13 || p[3]%13 == p[4]%13)){//first 3 or mid 3 or last 3
           return 1;
       }
    else
        return 0;
}
