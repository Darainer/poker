//
// Created by ryanj on 7/6/2019.
//

#ifndef POKER_POKER_H
#define POKER_POKER_H
#include <memory>
#include <string>
#endif //POKER_POKER_H

#include <iostream>
#include <vector>
#include <algorithm>    // std::shuffle
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock
#include <unordered_map>

namespace poker {

    enum struct cardSuit : int {
        HEART,
        SPADE,
        CLUB,
        DIAMOND
    };

    static std::unordered_map< int , std::string> CardDescription {
        {1,"ACE"},
        {2,"2"},
        {3,"3"},
        {4,"4"},
        {5,"5"},
        {6,"6"},
        {7,"7"},
        {8,"8"},
        {9,"9"},
        {10,"10"},
        {11,"JACK"},
        {12,"QUEEN"},
        {13, "KING"}
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
        std::string print_CardDescription(int key);
    private:
        cardSuit suit;
        pips v;
    };

    enum struct CombinationRank : int {
        HighCard,
        Pair,
        TwoPair,
        ThreeOfaKind,
        FourOfaKind,
        Straight,
        Flush,
        StraightFlush,
        RoyalFlush
    };

    struct Combination {
        Combination(CombinationRank rank, int mepips);
        CombinationRank combination;
        int combinationpipsvalue{0};
    };

    static std::unordered_map<const CombinationRank, const int> CombinationBaseScore{
            {CombinationRank::HighCard,      0},
            {CombinationRank::Pair,          15},
            {CombinationRank::TwoPair,       30},
            {CombinationRank::ThreeOfaKind,  45},
            {CombinationRank::FourOfaKind,   60},
            {CombinationRank::Straight,      75},
            {CombinationRank::Flush,         90},
            {CombinationRank::StraightFlush, 105},
            {CombinationRank::RoyalFlush,    120}
    };

    struct PlayerHandInfo {
        std::vector<Combination> HandCombinations;
        int score{0};
        bool hasPair{false};
        bool hasTwoPair{false};
        bool hasThreeOfaKind{false};
        bool hasFourOfaKind{false};
        bool hasFlush{false};
        bool hasStraight{false};
        bool hasStraightFlush{false};
        bool hasRoyalFlush{false};

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


    class playerHand {
    public:
        playerHand();
        void sortByPips();
        void sortBySuit();
        void calculate5CardPokerScore();
        int getPokerScore() const;

        void takeCard(card NewCard);
        void printHand();
        PlayerHandInfo const CheckHand();
        std::vector<card> showHand();
        

    private:
        PlayerHandInfo HandInfo;  // todo: this should be a return value rather than a state in the class
        std::vector<card> DealtCards;  
        int CalculateCombinationScore(PlayerHandInfo &Handinfo, CombinationRank Rank); // todo: seperate out all the scoring from the player hand
        void checkForStraight();
        void checkallMultiples();
        void checkForPair();
        void checkForFlush();
        void checkForStraightFlush();
        void checkForRoyalFlush();
        int getHighCard();
        void calculateScore();


    };

    class cardDeck {
    public:
        cardDeck();
        explicit cardDeck(int numberOfDecks);
        void shuffleDeck();
        int getDeckSize();
        void addOneFullDeck();
        card dealOneCard();

    private:
        std::vector<card> deck;
    };

    class heapDeck {
    public:
        heapDeck();
        explicit heapDeck(int numberOfDecks);
        ~heapDeck();
        void shuffleDeck();
        int getDeckSize();
        void addOneFullDeck();
        std::unique_ptr<card> dealOneCard();

    private:
        std::vector<std::unique_ptr<card>> deck;
    };


    //auto const sortHandByValue = [](playerHand const &Hand1, playerHand const &Hand2) -> bool ;  //todo should be const, find out why it gives error;

    class cardGame {
    public:
        cardGame();
        cardGame(int inputNumberOfPlayers, int inNumberOfCards);

        cardGame(std::vector<playerHand> inputhands);
        void calculatePokerScore();

        void printPokerScores() const;
        void SortHandsByScores();
        void PrintHands();
    private:
        void setup_new_game();
        cardDeck Deck;
        std::vector<card> board;
        std::vector<playerHand> PlayerHands;

        int numberOfPlayers;
        int numberOfCards;  //default for texas hold em poker
        int board_size;

        void PrintBoard();
    };



}