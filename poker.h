//
// Created by ryanj on 7/6/2019.
//

#ifndef POKER_POKER_H
#define POKER_POKER_H
#endif //POKER_POKER_H

#include <iostream>
#include <vector>
#include <algorithm>    // std::shuffle
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock

enum class cardSuit: int {HEART, SPADE, CLUB, DIAMOND };

class pips{
public:
    pips(): v(0){}
    pips(int val):v(val){}
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
        newDeck();
        //PlayerHands{0};

    }
    void shuffleDeck(){
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::shuffle(deck.begin(),deck.end(),std::default_random_engine(seed));
    }
    void dealnewGame(int numberofPlayers, int numberofCardsInHand){
        if(numberofCardsInHand*numberofPlayers<= 52){
            std::cout<< "need a bigger deck bro"<< std::endl; // todo: maybe use two decks in this case?
            return;
        }

        newDeck();
        shuffleDeck();

        for (int i = 1; i!= numberofCardsInHand; i++){
            for(int p = 1; i!= numberofPlayers; p++){

                card& currentcard = deck.back();

            }
        }
        deck.pop_back();
    }
    std::vector<card> showdeck() const {
        return deck; }
    void printDeck(){
        for (auto i = deck.begin(); i!= deck.end(); i++ ){
            std::cout<< *i << std::endl;
        }
    }
private:
    std::vector<card> deck;
    std::vector<std::vector<card>> PlayerHands;
    void newDeck(){
        cardSuit currentSuit = cardSuit::CLUB;
        for (int suitIterator = 1; suitIterator<=4; suitIterator++){
            if (suitIterator == 1){currentSuit = cardSuit::DIAMOND;}
            else if(suitIterator ==2){currentSuit= cardSuit::CLUB;}
            else if(suitIterator ==3){currentSuit= cardSuit::HEART;}
            else if(suitIterator ==4){currentSuit= cardSuit::SPADE;}
            for (int i = 1;i<= 13;i++){
                deck.emplace_back(card(currentSuit, i));
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
