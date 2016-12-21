#include "main.h"

int main()
{
    int card[52];
    srand(time(NULL));
    shuffle(card);
    deal(card);
    printCardsOnHand(card);
    int playersScore[4];
    scoreOfCardType(card, playersScore);
    compareAndPrintResult(playersScore);
    return 0;
}
