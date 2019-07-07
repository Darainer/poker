#include "poker.h"


int main() {

    cardDeck mydeck;
    std::vector<card> itsabigdeck = mydeck.showdeck();

    for (auto i = itsabigdeck.begin(); i!= itsabigdeck.end(); i++ ){
        std::cout<< *i << std::endl;
        cardSuit s = (*i).get_suit();
        //a static_cast<string> s
        //std::cout<< s << std::endl;
    }

    return 0;
}