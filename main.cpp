#include "poker.h"
// this can be the card game

int main() {

    poker::cardGame mygame(15, 7);
    mygame.dealnewPokerGame();
    mygame.PrintHands();



    return 0;
}