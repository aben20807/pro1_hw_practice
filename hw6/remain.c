#include "remain.h"

typedef enum{
    Spades,
    Hearts,
    Clubs,
    Diamonds
}suit;

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
