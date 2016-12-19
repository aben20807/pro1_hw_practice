#include "main.h"

int main()
{
    int i;
    int card[52];
    srand(time(NULL));
    shuffle(card);
    
    deal(card);
    printCardsOnHand(card);
    return 0;
}
