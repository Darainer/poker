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

    struct PlayerHandInfo{
        bool score;
        bool hasFlush;
        bool hasStraight;
        bool hasPair;
        bool hasStraightFlush;
        bool hasRoyalFlush;
    };

    enum class cardSuit : int {
        HEART, SPADE, CLUB, DIAMOND
    };
    class pips {
    public:
        explicit pips();// : v(0) {}
        explicit pips(int val);//  : v(val) {}
        //friend std::ostream &operator<<(std::ostream &out, const pips &p);
        int get_pips_value() const;
        int set_pips_value(int val);

    private:
        int v;
    };
    class card {
    public:
        card(cardSuit s, pips p);
        card(cardSuit s, int pips);
        //friend std::ostream &operator<<(std::ostream &out, const card &c);
        cardSuit get_suit() const;
        int get_pips() const;
        pips get_pips_literal() const;
        void set_pips(int vin);

    private:
        cardSuit suit;
        pips v;
    };
//    std::ostream &operator<<(std::ostream &out, const pips &p);
//    std::ostream &operator<<(std::ostream &out, const cardSuit &suit) ;
//    std::ostream &operator<<(std::ostream &out, const card &c);
    auto SortCardsByPips = [](const card &Card1, const card &Card2) -> bool {
        return Card1.get_pips() < Card2.get_pips();};
    auto CardsEqualByPips = [](const card &Card1, const card &Card2) ->bool {
        return Card1.get_pips() == Card2.get_pips();};
    auto sortCardsBySuit = [](const card &Card1, const card &Card2) -> bool {
        return Card1.get_suit() < Card2.get_suit();};
    class cardDeck {
    public:
        cardDeck();
        explicit cardDeck(int numberOfDecks);
        void shuffleDeck();
        void printDeck();

        int getDeckSize();
        void addOneFullDeck();

        card dealOneCard(std::vector<card> &destinationHand);

    private:
        std::vector<card> deck;
    };

    class playerHand {
    public:
        playerHand();

        void sortByPips();

        void sortBySuit();

        void calculate5CardPokerScore();

        int const getPokerScore();

        void takeCardFromDeck(card NewCard);

        void printHand();
        PlayerHandInfo const CheckHand();
        std::vector<card> DealtCards;  //todo make private

    private:
        PlayerHandInfo HandInfo;
        void checkForStraight();
        void checkForPair();
        void checkForFlush();
        void checkForStraightFlush();
        void checkForRoyalFlush();
        int getHighCard();
        void calculateScore();
    };

    auto sortHandByValue = []( playerHand &Hand1, playerHand &Hand2) -> bool {  //todo should be const, find out why it gives error
        return Hand1.getPokerScore() < Hand2.getPokerScore();};

    class cardGame {
    public:
        cardGame();
        cardGame(int inputNumberOfPlayers, int inNumberOfCards);
        void dealNewPokerGame();
        void calculatePokerScore();
        void printPokerScores();
        void SortHandsByScores();
        void PrintHands();
    private:
        void setup();
        cardDeck Deck;
        std::vector<playerHand> PlayerHands;
        int numberOfPlayers;
        int numberOfCards;  //default for poker
    };
}