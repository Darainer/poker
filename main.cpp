#include "poker.h"
// this can be the card game
using namespace poker;
int main() {

    cardGame mygame(4, 5);
    mygame.dealNewPokerGame();
    mygame.calculatePokerScore();
    mygame.PrintHands();


    playerHand TestFlush;
    for (int i = 0; i != 5; i++) {
        TestFlush.takeCardFromDeck(card(cardSuit::SPADE, pips(i)));
    }
    TestFlush.calculate5CardPokerScore();
    return 0;
}