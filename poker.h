//
// Created by ryanj on 7/6/2019.
//

#ifndef POKER_POKER_H
#define POKER_POKER_H

#endif //POKER_POKER_H

#include <iostream>
#include <vector>

enum class cardSuit: int {HEART, SPADE, CLUB, DIAMOND };

class pips{
public:
    pips(): v(0){}
    pips(int val):v(val){
    }
    friend std::ostream& operator<<(std::ostream& out, const pips& p);
    int get_pips(){return v;}
private:
    int v;
};

class card{
public:
    card() {
        suit = cardSuit::SPADE;
        v= 0;
    }
    card(cardSuit s, pips p){
        suit = s;
        v = p;
    };

    friend std::ostream& operator<<(std::ostream& out, const card& c);
    cardSuit get_suit() const {return suit;}
    pips get_pips() const {return v;}
    void set_pips(int vin){v= vin;}
private:
    cardSuit suit;
    pips v;
};

class cardDeck{
public:
    cardDeck(){
        deal();
    }
    std::vector<card> showdeck() const {
        return deck; }

private:
    std::vector<card> deck;
    void deal(){
        cardSuit suity = cardSuit::CLUB;
        for (int mesuit = 1; mesuit<=4; mesuit++){

            if (mesuit == 1){suity = cardSuit::DIAMOND;}
            else if(mesuit ==2){suity= cardSuit::CLUB;}
            else if(mesuit ==3){suity= cardSuit::HEART;}
            else if(mesuit ==4){suity= cardSuit::SPADE;}

            for (int i = 1;i<= 14;i++){
                deck.emplace_back(card(suity, i));
        }
        }
    }
};

std::ostream& operator<<(std::ostream& out, const pips& p){
    if (p.v== 1){std::cout << "ACE";}
    else if (p.v== 11){std::cout << "JACK";}
    else if (p.v== 12){std::cout << "QUEEN";}
    else if (p.v== 13){std::cout << "KING";}
    else{std::cout << p.v;}
    return out;
}

std::ostream& operator<<(std::ostream& out, const cardSuit& suit){

    if ( suit == cardSuit::DIAMOND){ std::cout << " DIAMONDS"; }
    else if ( suit == cardSuit::CLUB){ std::cout << " CLUBS"; }
    else if ( suit == cardSuit::HEART){ std::cout << " HEARTS"; }
    else if ( suit == cardSuit::SPADE){ std::cout << " SPADES"; }
    else{}
    return out;
}


std::ostream& operator<<(std::ostream& out, const card& c){
    std::cout << c.v << c.suit;
    return out;
}
