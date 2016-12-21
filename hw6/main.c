#include "main.h"

int main()
{
    int card[52];
    srand(time(NULL));
    shuffle(card);
    // int card[52] = {4,26,39,52,
    //     26,25,38,51,
    //     39,24,37,50,
    //     52,23,36,49,
    //     13,22,35,48,
    //     8,21,34,47,
    //     7,20,33,46,
    //     6,19,32,45,
    //     5,18,31,44,
    //     4,17,30,43,
    //     3,16,29,42,
    //     2,15,28,41,
    //     1,14,27,40};
    deal(card);
    // printCardsOnHand(card);
    scoreOfCardType(card);
    return 0;
}
