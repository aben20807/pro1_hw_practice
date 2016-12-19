#include "main.h"

int main()
{
    int i;
    int card[52];
    srand(time(NULL));
    shuffle(card);
    for(i = 0; i < SIZE; i++){
        printf("%d ", card[i]);
    }
    printf("\n");
    deal(card);
    for(i = 0; i < 20; i++){
        if(i%5 == 0){
            printf("Player %d:", i/5+1);
        }
        printf("%d ", card[i]);
        if(i%5 == 4){
            printf("\n");
        }
    }
    return 0;
}
