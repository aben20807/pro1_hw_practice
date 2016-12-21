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

int scoreOfCardType(const int card[]){
    int i, j;
    int p[4][5];
    int pScore[4] = {0};
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
    printCardsOnHand(tmp);
    for(i = 0; i < 4; i++){
        // printf("%d ", isStraightFlush(p[i]));
        // printf("%d ", isFourOfAKind(p[i]));
        // printf("%d ", isFullHouse(p[i]));
        // printf("%d ", isFlush(p[i]));
        // printf("%d ", isStraight(p[i]));
        // printf("%d ", isThreeOfAKind(p[i]));
        // printf("%d ", isTwoPairs(p[i]));
        // printf("%d\n", isPair(p[i]));
        if(isStraightFlush(p[i])){
            pScore[i] = getScore(9, getRank(p[i][0]), getSuitN(p[i][0]));
            printf("P%d:straight flush\n",i+1);
        }
        else if(isFourOfAKind(p[i])){
            pScore[i] = getScore(8, getRank(p[i][isFourOfAKind(p[i])-1]), getSuitN(p[i][isFourOfAKind(p[i])-1]));
            // printf("P%d:four-of-a-kind\n",i+1);
        }
        else if(isFullHouse(p[i])){
            pScore[i] = getScore(7, getRank(p[i][isFullHouse(p[i])-1]), getSuitN(p[i][isFullHouse(p[i])-1]));
            // printf("P%d:full house\n",i+1);
        }
        else if(isFlush(p[i])){
            pScore[i] = getScore(6, getRank(p[i][0]), getSuitN(p[i][0]));
            // printf("P%d:flush\n",i+1);
        }
        else if(isStraight(p[i])){
            pScore[i] = getScore(5, getRank(p[i][0]), getSuitN(p[i][0]));
            // printf("P%d:straight\n",i+1);
        }
        else if(isThreeOfAKind(p[i])){
            pScore[i] = getScore(4, getRank(p[i][isThreeOfAKind(p[i])-1]), getSuitN(p[i][isThreeOfAKind(p[i])-1]));
            // printf("P%d:three-of-a-kind\n",i+1);
        }
        else if(isTwoPairs(p[i])){
            pScore[i] = getScore(3, getRank(p[i][isTwoPairs(p[i])-1]), getSuitN(p[i][isTwoPairs(p[i])-1]));
            // printf("P%d:two pairs\n",i+1);
        }
        else if(isPair(p[i])){
            pScore[i] = getScore(2, getRank(p[i][isPair(p[i])-1]), getSuitN(p[i][isPair(p[i])-1]));
            // printf("P%d:pair\n",i+1);
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
            // printf("P%d:high card\n",i+1);
        }
    }
    for(i = 0; i < 4; i++){
        printf("P%d: %d\n", i+1, pScore[i]);
    }
    // int maxPerson = -1;
    // int tmpScore = -1;
    // for(i = 0; i < 4; i++){
    //     if(pScore[i] > tmpScore){
    //         maxPerson = i;//highest person
    //         tmpScore = pScore[i];//highest type score
    //     }
    // }
    // int numOfHightType = 0;
    // int highPeople[4] = {0};
    // for(i = 0; i < 4; i++){//count if more than one is higher
    //     if(pScore[i] == tmpScore){
    //         numOfHightType++;
    //         highPeople[i] = 1;
    //     }
    // }
    // if(numOfHightType == 1){
    //     printf("Winner : P%d — ", maxPerson+1);
    //     if(isStraightFlush(p[maxPerson])){
    //         printf("straight flush\n");
    //     }
    //     else if(isFourOfAKind(p[maxPerson])){
    //         printf("four-of-a-kind\n");
    //     }
    //     else if(isFullHouse(p[maxPerson])){
    //         printf("full house\n");
    //     }
    //     else if(isFlush(p[maxPerson])){
    //         printf("flush\n");
    //     }
    //     else if(isStraight(p[maxPerson])){
    //         printf("straight\n");
    //     }
    //     else if(isThreeOfAKind(p[maxPerson])){
    //         printf("three-of-a-kind\n");
    //     }
    //     else if(isTwoPairs(p[maxPerson])){
    //         printf("two pairs\n");
    //     }
    //     else if(isPair(p[maxPerson])){
    //         printf("pair\n");
    //     }
    //     else{//high card
    //         printf("high card\n");
    //     }
    // }
    // else if(numOfHightType > 1){
    //     tmpScore = -1;
    //     if(isStraightFlush(p[maxPerson])){
    //         for(i = 0; i < numOfHightType; i++){
    //             if(highPeople[i] == 1 && p[i][0] > tmpScore){
    //                 maxPerson = i;
    //                 tmpScore = p[i][0];
    //             }
    //         }
    //         printf("Winner : P%d — ", maxPerson+1);
    //         printf("straight flush\n");
    //     }
    //     else if(isFourOfAKind(p[maxPerson])){
    //         for(i = 0; i < numOfHightType; i++){
    //             if(highPeople[i] == 1 && p[i][0] == p[i][1] && p[i][0] > tmpScore){
    //                 maxPerson = i;
    //                 tmpScore = p[i][0];
    //             }
    //             else if(highPeople[i] == 1 && p[i][0] == p[i][1] && p[i][0] > tmpScore){//TODO 不只從頭算
    //                 maxPerson = i;
    //                 tmpScore = p[i][0];
    //             }
    //         }
    //         printf("Winner : P%d — ", maxPerson+1);
    //         printf("four-of-a-kind\n");
    //     }
    //     else if(isFullHouse(p[maxPerson])){
    //         printf("full house\n");
    //     }
    //     else if(isFlush(p[maxPerson])){
    //         printf("flush\n");
    //     }
    //     else if(isStraight(p[maxPerson])){
    //         printf("straight\n");
    //     }
    //     else if(isThreeOfAKind(p[maxPerson])){
    //         printf("three-of-a-kind\n");
    //     }
    //     else if(isTwoPairs(p[maxPerson])){
    //         printf("two pairs\n");
    //     }
    //     else if(isPair(p[maxPerson])){
    //         printf("pair\n");
    //     }
    //     else{//high card
    //         printf("high card\n");
    //     }
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

int getSuitN(const int n){
    return (n-1)/13+1;
}

int getRank(const int n){
    return n%13+1;
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
        // if((p[0] == 13 && p[1] == 4 && p[2] == 3 && p[3] == 2 && p[4] == 1) ||
        //    (p[0] == 26 && p[1] == 17 && p[2] == 16 && p[3] == 15 && p[4] == 14) ||
        //    (p[0] == 39 && p[1] == 30 && p[2] == 29 && p[3] == 28 && p[4] == 27) ||
        //    (p[0] == 52 && p[1] == 43 && p[2] == 42 && p[3] == 41 && p[4] == 40))
        if(getRank(p[0]) == 13 && getRank(p[1]) == 4 && getRank(p[2]) == 3 && getRank(p[3]) == 2 && getRank(p[4]) == 1){//straight flush a1234
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
    if(getRank(p[0]) == 0 && getRank(p[1]) == 4 && getRank(p[2]) == 3 && getRank(p[3]) == 2 && getRank(p[4]) == 1){//a1234
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
    else if(getRank(p[3]) == getRank(p[4])){//first 3 or mid 3 or last 3
        return 4;
    }
    else
        return 0;
}

// void analyze_hand(void)
// {
//     int num_consec = 0;
//     int rank, suit;
//     straight = false;
//     flush = false;
//     four = false;
//     three = false;
//     pairs = 0;
//     /* check for flush */
//     for (suit = 0; suit < NUM_SUITS; suit++)
//         if (num_in_suit[suit] == NUM_CARDS)
//             flush = true;
//     /* check for straight */
//     rank = 0;
//     while (num_in_rank[rank] == 0) rank++;
//     for (; rank < NUM_RANKS && num_in_rank[rank] > 0; rank++)
//         num_consec++;
//     if (num_consec == NUM_CARDS) {
//         straight = true;
//         return;
//     }
//     /* check for 4-of-a-kind, 3-of-a-kind, and pairs */
//     for (rank = 0; rank < NUM_RANKS; rank++) {
//         if (num_in_rank[rank] == 4) four = true;
//         if (num_in_rank[rank] == 3) three = true;
//         if (num_in_rank[rank] == 2) pairs++;
//     }
// }
