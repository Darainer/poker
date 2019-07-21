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

        pips(int val)  : v(val) {}

        friend std::ostream &operator<<(std::ostream &out, const pips &p);

        int get_pips_value() const { return v; }

    private:
        int v;
    };
    class card {
    public:
        card() {
            suit = cardSuit::SPADE;
            v = 1;
        }

        card(cardSuit s, pips p) {
            suit = s;
            v = p;
        };

        friend std::ostream &operator<<(std::ostream &out, const card &c);

        cardSuit get_suit() const { return suit; }

        int get_pips() const { return v.get_pips_value(); }

        void set_pips(int vin) { v = vin; }

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
        cardDeck(int numberOfDecks) {
            for (int i = 0; i != numberOfDecks; i++) {
                addOnefullDeck();
            }
        }
        void shuffleDeck() {
            unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
            std::shuffle(deck.begin(), deck.end(), std::default_random_engine(seed));
        }
        void printDeck() {
            for (auto i: deck){ //.begin(); i != deck.end(); i++) {
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
        }

        void printHand() {
            for (auto i : DealtCards){          //(auto i = DealtCards.begin(); i != DealtCards.end(); i++) {
                std::cout << i << std::endl;
            }
            std::cout << std::endl;
        }

        std::vector<card> DealtCards;
        std::vector<int> Score;
        bool hasFlush;
        bool hasStraight;
        bool hasPair;
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
        void CheckforFlush() {}

    };

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
        void dealnewPokerGame() {
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
        }
        void PrintHands() {        //test function
            PlayerHands[0].printHand();
            PlayerHands[0].SortbyPips();
            PlayerHands[0].printHand();
            PlayerHands[0].SortbySuit();
            PlayerHands[0].printHand();
            PlayerHands[0].Calculate5CardPokerScore();
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