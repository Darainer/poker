#include "poker.h"
// this can be the card game
using namespace poker;
int main() {
    int number_of_players{4};
    int size_of_hand{5};
    cardGame mygame(number_of_players, size_of_hand);
    mygame.dealNewPokerGame();
    mygame.calculatePokerScore();
    mygame.PrintHands();


    playerHand TestFlush;
    for (int i = 0; i != size_of_hand; i++) {
        TestFlush.takeCardFromDeck(card(cardSuit::SPADE, pips(i)));
    }
    TestFlush.calculate5CardPokerScore();
    return 0;
}