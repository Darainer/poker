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

namespace poker {
    enum class cardSuit : int {
        HEART, SPADE, CLUB, DIAMOND
    };
    class pips {
    public:
        pips() : v(0) {}
        explicit pips(int val)  : v(val) {}
        friend std::ostream &operator<<(std::ostream &out, const pips &p);
        int get_pips_value() const { return v; }
        int set_pips_value(int val) { v = val;}

    private:
        int v;
    };
    class card {
    public:
        card() {
            suit = cardSuit::SPADE;
            v = pips(1);
        }

        card(cardSuit s, pips p) {
            suit = s;
            v = p;
        };
        card(cardSuit s, int pips){
            suit = s;
            v.set_pips_value(pips);
        }

        friend std::ostream &operator<<(std::ostream &out, const card &c);
        cardSuit get_suit() const { return suit; }
        int get_pips() const { return v.get_pips_value(); }
        void set_pips(int vin) { v.set_pips_value(vin); }

    private:
        cardSuit suit;
        pips v;
        //std::string Name;
    };
    std::ostream &operator<<(std::ostream &out, const pips &p) {
        if (p.v == 1) { std::cout << "ACE"; }
        else if (p.v == 11) { std::cout << "JACK"; }
        else if (p.v == 12) { std::cout << "QUEEN"; }
        else if (p.v == 13) { std::cout << "KING"; }
        else { std::cout << p.v; }
        return out;
    }
    std::ostream &operator<<(std::ostream &out, const cardSuit &suit) {

        if (suit == cardSuit::DIAMOND) { std::cout << " DIAMONDS"; }
        else if (suit == cardSuit::CLUB) { std::cout << " CLUBS"; }
        else if (suit == cardSuit::HEART) { std::cout << " HEARTS"; }
        else if (suit == cardSuit::SPADE) { std::cout << " SPADES"; }
        else {}
        return out;
    }
    std::ostream &operator<<(std::ostream &out, const card &c) {
        std::cout << c.v << c.suit;
        return out;
    }
    auto SortCardsByPips = [](const card &Card1, const card &Card2) -> bool {
        return Card1.get_pips() < Card2.get_pips();};
    auto CardsEqualByPips = [](const card &Card1, const card &Card2) ->bool {
        return Card1.get_pips() == Card2.get_pips();};
    auto sortCardsBySuit = [](const card &Card1, const card &Card2) -> bool {
        return Card1.get_suit() < Card2.get_suit();};
    class cardDeck {
    public:
        cardDeck() {
            addOneFullDeck();
        }
        explicit cardDeck(int numberOfDecks) {
            for (int i = 0; i != numberOfDecks; i++) {
                addOneFullDeck();
            }
        }
        void shuffleDeck() {
            unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
            std::shuffle(deck.begin(), deck.end(), std::default_random_engine(seed));
        }
        void printDeck() {
            for (auto i: deck){ //deck.begin(); i != deck.end(); i++) {
                std::cout << i << std::endl;
            }
        }

        int getDeckSize() {
            return deck.size();
        }
        void addOneFullDeck() {
            cardSuit currentSuit = cardSuit::CLUB;
            for (int suitIterator = 1; suitIterator <= 4; suitIterator++) {
                if (suitIterator == 1) { currentSuit = cardSuit::DIAMOND; }
                else if (suitIterator == 2) { currentSuit = cardSuit::CLUB; }
                else if (suitIterator == 3) { currentSuit = cardSuit::HEART; }
                else if (suitIterator == 4) { currentSuit = cardSuit::SPADE; }
                for (int i = 1; i <= 13; i++) {
                    deck.emplace_back(card(currentSuit, i));
                }
            }
        }

        card dealOneCard(std::vector<card> &destinationHand) {
            card dealtCardFromDeck = deck.back();   //todo: learn about move semantics and get rid of the temp copy
            destinationHand.emplace_back(dealtCardFromDeck);
            deck.pop_back();
        }

    private:
        std::vector<card> deck;

    };
    class playerHand {
    public:
        playerHand() {
            hasPair = false;
            hasFlush = false;
            hasRoyalFlush = false;
            hasStraight = false;
            hasStraightFlush = false;
            score = -1;
        }

        void sortByPips() {
            std::sort(DealtCards.begin(), DealtCards.end(), SortCardsByPips);
        }

        void sortBySuit() {
            std::sort(DealtCards.begin(), DealtCards.end(), sortCardsBySuit);
        }

        void calculate5CardPokerScore() {
            checkForStraight();
            checkForPair();
            checkForFlush();
            checkForStraightFlush();
            checkForRoyalFlush();
            calculateScore();
        }

        void printHand() {
            for (auto i : DealtCards){          //(auto i = DealtCards.begin(); i != DealtCards.end(); i++) {
                std::cout << i << std::endl;
            }
            std::cout << std::endl;
        }


        std::vector<card> DealtCards;
        int score;
        bool hasFlush;
        bool hasStraight;
        bool hasPair;
        bool hasStraightFlush;
        bool hasRoyalFlush;

    private:
        void checkForStraight() {
            sortByPips();
            hasStraight = true;
            for (auto i = DealtCards.begin(); i != DealtCards.end() - 1; i++) {
                if ((*i).get_pips()+ 1 != ((*(i + 1)).get_pips() )) {
                    hasStraight = false;
                }
            }
        }
        void checkForPair() {
            sortByPips();
            // for each unique pips, count the elements with the same
            // three of a kind, 4 of a kind
            hasPair = false;
            //int uniquePips = std::count (DealtCards.begin(),DealtCards.end(),CardsEqualByPips);
            for (auto i = DealtCards.begin(); i != DealtCards.end() ; i++) {
                if ((*i).get_pips() == ((*(i + 1)).get_pips())) {
                    hasPair = true;
                }
            }
        }
        void checkForFlush() {
            hasFlush = true;
            for (auto i = DealtCards.begin(); i != DealtCards.end() - 1; i++) {
                if ((*i).get_suit() != ((*(i + 1)).get_suit() )) {
                    hasFlush = false;
                }
            }
        }
        void checkForStraightFlush(){
            checkForStraight();
            checkForFlush();
            hasStraightFlush = hasStraight && hasFlush;
        }
        void checkForRoyalFlush(){
            int minPips = 9; //jack
            checkForFlush();
            sortByPips();
            if ((DealtCards.front().get_pips() >= minPips) && hasFlush){
                hasRoyalFlush= true;
            }
        }
        int getHighCard(){
            std::vector<card>::iterator result;
            result = std::max_element(DealtCards.begin(), DealtCards.end(), SortCardsByPips);
            return (*result).get_pips();
        };
        void calculateScore(){
            if(hasRoyalFlush){score= 17;}
            else if(hasStraightFlush){score = 16;}
            else if(hasStraight){score= 15;}
            else if(hasPair){score = 14;}
            else{
                sortByPips();
                score = getHighCard();  // score for the high card is the score
            }
        }
    };
    auto sortHandByValue = [](const playerHand &Hand1, const playerHand &Hand2) -> bool {
        return Hand1.score < Hand2.score;};
    class cardGame {
    public:
        cardGame() {
            numberOfPlayers = 4;
            numberOfCards = 5;
            setup();
        }
        cardGame(int inputNumberOfPlayers, int inNumberOfCards) {
            numberOfPlayers = inputNumberOfPlayers;
            numberOfCards = inNumberOfCards;
            setup();
        }
        void dealNewPokerGame() {
            int numberOfCardsNeeded = numberOfCards * numberOfPlayers;
            while (numberOfCardsNeeded >= Deck.getDeckSize()) {
                std::cout << "need to size up the deck bro" << std::endl;
                Deck.addOneFullDeck();
            }
            Deck.shuffleDeck();

            for (int i = 0; i != numberOfCards; i++) {
                for (int p = 0; p != numberOfPlayers; p++) {
                    Deck.dealOneCard(PlayerHands[p].DealtCards);
                }
            }
            std::cout << "after dealing, deck size is " << Deck.getDeckSize() << std::endl;
        }
        void calculatePokerScore(){
            for(auto i= PlayerHands.begin();i!= PlayerHands.end();i++){
                (*i).calculate5CardPokerScore();
            }

            for(auto i= PlayerHands.begin();i!= PlayerHands.end();i++){
                (*i).calculate5CardPokerScore();
            }
        }
        void printPokerScores(){
            for(auto i= PlayerHands.begin(); i!= PlayerHands.end();i++){
                (*i).printHand();
                std::cout << "score "<<(*i).score<< std::endl;
            }
        }
        void SortHandsByScores(){
            std::sort(PlayerHands.begin(), PlayerHands.end(),sortHandByValue);
        }
        void PrintHands() {        //test function
            PlayerHands[0].printHand();
            PlayerHands[0].sortByPips();
            PlayerHands[0].printHand();
            PlayerHands[0].sortBySuit();
            PlayerHands[0].printHand();
            PlayerHands[0].calculate5CardPokerScore();
            SortHandsByScores();
            printPokerScores();
        }
    private:
        void setup(){
            for (int n = 0; n != numberOfPlayers; n++) {
                PlayerHands.emplace_back();
            }
        }
        cardDeck Deck;
        std::vector<playerHand> PlayerHands;
        int numberOfPlayers;
        int numberOfCards;  //default for poker
    };
}