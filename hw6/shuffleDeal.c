#include "shuffleDeal.h"
void shuffle(int card[]){
    int i, j;
    for(i = 0; i < SIZE; i++){
        card[i] = rand()%52+1;
        for(j = 0; j < i; j++){
            if(card[i] == card[j]){
                i--;
                continue;
            }
        }
    }
}
void deal(int card[]){
    int i, j = 0;
    int deal[20];
    for(i = 0; i < 4*5; i+=4, j++){
        deal[j] = card[i];
        deal[j+5] = card[i+1];
        deal[j+10] = card[i+2];
        deal[j+15] = card[i+3];
    }
    for(i = 0; i < 20; i++){
        card[i] = deal[i];
    }
}
