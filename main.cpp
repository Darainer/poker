#include "poker.h"


int main() {

    cardDeck mydeck;
    std::vector<card> itsabigdeck = mydeck.showdeck();

    for (auto i = itsabigdeck.begin(); i!= itsabigdeck.end(); i++ ){
        std::cout<< *i << std::endl;
    }

    mydeck.shuffleDeck();
    std::cout<< "gave it a shuffle"<< std::endl;
    mydeck.printDeck();
    return 0;
}