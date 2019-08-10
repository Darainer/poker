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
    auto SortCardsbypips = [](const card &Card1, const card &Card2) -> bool {
        return Card1.get_pips() < Card2.get_pips();};
    auto CardsEqualbypips = [](const card &Card1, const card &Card2) ->bool {
        return Card1.get_pips() == Card2.get_pips();};
    auto SortCardsbySuit = [](const card &Card1, const card &Card2) -> bool {
        return Card1.get_suit() < Card2.get_suit();};
    class cardDeck {
    public:
        cardDeck() {
            addOnefullDeck();
        }
        explicit cardDeck(int numberOfDecks) {
            for (int i = 0; i != numberOfDecks; i++) {
                addOnefullDeck();
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
        void addOnefullDeck() {
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
            card dealme = deck.back();   //todo: learn about move semantics and get rid of the temp copy
            destinationHand.emplace_back(dealme);
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

        void SortbyPips() {
            std::sort(DealtCards.begin(), DealtCards.end(), SortCardsbypips);
        }

        void SortbySuit() {
            std::sort(DealtCards.begin(), DealtCards.end(), SortCardsbySuit);
        }

        void Calculate5CardPokerScore() {
            CheckforStraight();
            CheckforPair();
            CheckforFlush();
            CheckforStraightFlush();
            CheckForRoyalFlush();
            CalculateScore();
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
        void CheckforStraight() {
            SortbyPips();
            hasStraight = true;
            for (auto i = DealtCards.begin(); i != DealtCards.end() - 1; i++) {
                if ((*i).get_pips()+ 1 != ((*(i + 1)).get_pips() )) {
                    hasStraight = false;
                }
            }
        }
        void CheckforPair() {
            SortbyPips();
            // for each unique pips, count the elements with the same
            // three of a kind, 4 of a kind
            hasPair = false;
            //int uniquepips = std::count (DealtCards.begin(),DealtCards.end(),CardsEqualbypips);
            for (auto i = DealtCards.begin(); i != DealtCards.end() ; i++) {
                if ((*i).get_pips() == ((*(i + 1)).get_pips())) {
                    hasPair = true;
                }
            }
        }
        void CheckforFlush() {
            hasFlush = true;
            for (auto i = DealtCards.begin(); i != DealtCards.end() - 1; i++) {
                if ((*i).get_suit() != ((*(i + 1)).get_suit() )) {
                    hasFlush = false;
                }
            }
        }
        void CheckforStraightFlush(){
            CheckforStraight();
            CheckforFlush();
            hasStraightFlush = hasStraight && hasFlush ? true : false;
        }
        void CheckForRoyalFlush(){
            int minpips = 9; //jack
            CheckforFlush();
            SortbyPips();
            if ((DealtCards.front().get_pips() >= minpips) && hasFlush){
                hasRoyalFlush= true;
            }
        }
        int GetHighCard(){
            std::vector<card>::iterator result;
            result = std::max_element(DealtCards.begin(), DealtCards.end(), SortCardsbypips);
            return (*result).get_pips();
        };
        void CalculateScore(){
            if(hasRoyalFlush){score= 17;}
            else if(hasStraightFlush){score = 16;}
            else if(hasStraight){score= 15;}
            else if(hasPair){score = 14;}
            else{
                SortbyPips();
                score = GetHighCard();  // score for the high card is the score
            }
        }
    };
    auto SorthandbyValue = [](const playerHand &Hand1, const playerHand &Hand2) -> bool {
        return Hand1.score < Hand2.score;};
    class cardGame {
    public:
        cardGame() {
            numberofPlayers = 4;
            numberofCards = 5;
            setup();
        }
        cardGame(int inputnumberofPlayers, int inNumberofCards) {
            numberofPlayers = inputnumberofPlayers;
            numberofCards = inNumberofCards;
            setup();
        }
        void dealNewPokerGame() {
            int numberofCardsNeeded = numberofCards * numberofPlayers;
            while (numberofCardsNeeded >= Deck.getDeckSize()) {
                std::cout << "need to size up the deck bro" << std::endl;
                Deck.addOnefullDeck();
            }
            Deck.shuffleDeck();

            for (int i = 0; i != numberofCards; i++) {
                for (int p = 0; p != numberofPlayers; p++) {
                    Deck.dealOneCard(PlayerHands[p].DealtCards);
                }
            }
            std::cout << "after dealing, deck size is " << Deck.getDeckSize() << std::endl;
        }
        void calculatePokerScore(){
            for(auto i= PlayerHands.begin();i!= PlayerHands.end();i++){
                (*i).Calculate5CardPokerScore();
            }

            for(auto i= PlayerHands.begin();i!= PlayerHands.end();i++){
                (*i).Calculate5CardPokerScore();
            }
        }
        void printPokerScores(){
            for(auto i= PlayerHands.begin(); i!= PlayerHands.end();i++){
                (*i).printHand();
                std::cout << "score "<<(*i).score<< std::endl;
            }
        }
        void SortHandsbyScores(){
            std::sort(PlayerHands.begin(), PlayerHands.end(),SorthandbyValue);
        }
        void PrintHands() {        //test function
            PlayerHands[0].printHand();
            PlayerHands[0].SortbyPips();
            PlayerHands[0].printHand();
            PlayerHands[0].SortbySuit();
            PlayerHands[0].printHand();
            PlayerHands[0].Calculate5CardPokerScore();
            SortHandsbyScores();
            printPokerScores();
        }
    private:
        void setup(){
            for (int n = 0; n != numberofPlayers; n++) {
                PlayerHands.emplace_back();
            }
        }
        cardDeck Deck;
        std::vector<playerHand> PlayerHands;
        int numberofPlayers;
        int numberofCards;  //default for poker
    };
}