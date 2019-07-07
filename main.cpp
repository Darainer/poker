#include "poker.h"

// this can be the card game
int main() {

    cardDeck mydeck;
    mydeck.printDeck();
    mydeck.dealnewGame(4,5);
    mydeck.printDeck();
    /*    mydeck.printDeck();
    mydeck.shuffleDeck();
    std::cout<< "gave it a shuffle"<< std::endl;
    mydeck.printDeck();
*/
    return 0;
}