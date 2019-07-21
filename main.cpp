#include "poker.h"
// this can be the card game

int main() {

    poker::cardGame mygame(4, 5);
    mygame.dealnewPokerGame();
    mygame.PrintHands();


    poker::playerHand TestFlush;
    for(int i = 0; i!= 5; i++) {
        TestFlush.DealtCards.emplace_back(poker::card(poker::cardSuit::SPADE, poker::pips(i)));
    }
    TestFlush.Calculate5CardPokerScore();
    return 0;
}