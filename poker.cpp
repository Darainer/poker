//
// Created by ryanj on 8/14/2019.
//
//
// Created by ryanj on 7/6/2019.
//

#include <iostream>
#include <vector>
#include <algorithm>    // std::shuffle
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock

#include "poker.h"

using namespace poker;

pips::pips() : v(0) {}
pips::pips(int val)  {v = val; }
int pips::get_pips_value() const { return v; }
int pips::set_pips_value(int val) { v = val;}

card::card(cardSuit s, pips p) {
    suit = s;
    v = p;
}
card::card(cardSuit s, int pips){
    suit = s;
    v.set_pips_value(pips);
}
cardSuit card::get_suit() const { return suit; }
pips card::get_pips_literal() const {return v;}
int card::get_pips() const { return v.get_pips_value(); }
void card::set_pips(int vin) { v.set_pips_value(vin); }

Combination::Combination(poker::CombinationRank rank, int mepips) {
    combination = rank;
    combinationpipsvalue = mepips;
}

std::ostream &operator<<(std::ostream &out, const pips &p) {
    if (p.get_pips_value() == 1) { std::cout << "ACE"; }
    else if (p.get_pips_value() == 11) { std::cout << "JACK"; }
    else if (p.get_pips_value() == 12) { std::cout << "QUEEN"; }
    else if (p.get_pips_value() == 13) { std::cout << "KING"; }
    else { std::cout << p.get_pips_value(); }
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
    std::cout << c.get_pips_literal();
    std::cout << c.get_suit();
    return out;
}
auto SortCardsByPips = [](const card &Card1, const card &Card2) -> bool {
    return Card1.get_pips() < Card2.get_pips();};
auto CardsEqualByPips = [](const card &Card1, const card &Card2) ->bool {
    return Card1.get_pips() == Card2.get_pips();};
auto sortCardsBySuit = [](const card &Card1, const card &Card2) -> bool {
    return Card1.get_suit() < Card2.get_suit();};

cardDeck::cardDeck() {
    addOneFullDeck();
}
cardDeck::cardDeck(int numberOfDecks) {
    for (int i = 0; i != numberOfDecks; i++) {
        addOneFullDeck();
    }
}
void cardDeck::shuffleDeck() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(deck.begin(), deck.end(), std::default_random_engine(seed));
}

int cardDeck::getDeckSize() {
    return deck.size();
}
void cardDeck::addOneFullDeck() {
    cardSuit currentSuit{cardSuit::CLUB};
    for (int suitIterator = 0; suitIterator <= 3; suitIterator++) {
        currentSuit = static_cast<cardSuit>(suitIterator);
        for (int i = 1; i <= 13; i++) {
            deck.emplace_back(card(currentSuit, i));
        }
    }
}
card cardDeck::dealOneCard(std::vector<card> &destinationHand) {
    card dealtCardFromDeck = deck.back();   //todo: learn about move semantics and get rid of the temp copy
    destinationHand.emplace_back(dealtCardFromDeck);
    deck.pop_back();
}

void playerHand::takeCardFromDeck(card NewCard) {
    DealtCards.emplace_back(NewCard);
}

playerHand::playerHand() {

}
void playerHand::sortByPips() {
    std::sort(DealtCards.begin(), DealtCards.end(), SortCardsByPips);
}
void playerHand::sortBySuit() {
    std::sort(DealtCards.begin(), DealtCards.end(), sortCardsBySuit);
}

void playerHand::calculate5CardPokerScore() {
    //find_besthand();
    checkForPair();
    checkForFlush();
    checkForStraight();
    checkForStraightFlush();
    checkForRoyalFlush();
    calculateScore();
}

int playerHand::getPokerScore() const {
    return HandInfo.score;
}

void printCards(const std::vector<card> &Cards) {
    for (auto i : Cards) {
        std::cout << i << std::endl;
    }
    std::cout << std::endl;
}

void playerHand::checkForPair() {
    sortByPips();
    // for each unique pips, count the elements with the same
    // three of a kind, 4 of a kind
    // todo deal with two pairs
    HandInfo.hasPair = false;
    //int uniquePips = std::count (DealtCards.begin(),DealtCards.end(),CardsEqualByPips);
    for (auto i = DealtCards.begin(); i != DealtCards.end() - 1; i++) {
        if ((*i).get_pips() == ((*(i + 1)).get_pips())) {
            HandInfo.hasPair = true;
            Combination pair(CombinationRank::Pair, (*i).get_pips());
            HandInfo.HandCombinations.push_back(pair);
        }
    }
}
void playerHand::checkForFlush() {
    sortByPips();
    for (auto i = DealtCards.begin();
         i != DealtCards.end() - 1; i++) {   // todo: look for a way to remove the pointer arithmatic from this code?
        if ((*i).get_suit() != ((*(i + 1)).get_suit()))
            HandInfo.hasFlush = false;
        return;
    }
    HandInfo.hasFlush = true;
    Combination flush(CombinationRank::Flush, DealtCards.at(DealtCards.size() - 1).get_pips());  //high card
    HandInfo.HandCombinations.push_back(flush);
}

void playerHand::checkForStraight() {
    sortByPips();       //todo deal with ace high and low in searching for straight
    for (auto i = DealtCards.begin();
         i != DealtCards.end() - 1; i++) {   // todo: look for a way to remove the pointer arithmatic from this code?
        if ((*i).get_pips() + 1 != ((*(i + 1)).get_pips()))
            HandInfo.hasStraight = false;
        return;
    }


    HandInfo.hasStraight = true;
    Combination straight(CombinationRank::Straight, DealtCards.at(DealtCards.size() - 1).get_pips());
    HandInfo.HandCombinations.push_back(straight);
}

void playerHand::checkForStraightFlush(){
    checkForStraight();
    checkForFlush();
    HandInfo.hasStraightFlush = HandInfo.hasStraight && HandInfo.hasFlush;
    Combination straightflush(CombinationRank::StraightFlush,
                              DealtCards.at(DealtCards.size() - 1).get_pips());  //high card
    HandInfo.HandCombinations.push_back(straightflush);
}
void playerHand::checkForRoyalFlush(){
    int minPips = 10; //jack
    checkForFlush();
    sortByPips();
    if ((DealtCards.front().get_pips() == 0)  // is ace
        && (DealtCards.at(1).get_pips() >= minPips)
        && HandInfo.hasFlush) {
        HandInfo.hasRoyalFlush = true;
        Combination royalflush(CombinationRank::RoyalFlush,
                               DealtCards.at(DealtCards.size() - 1).get_pips());  //high card
        HandInfo.HandCombinations.push_back(royalflush);
    } else {
        HandInfo.hasRoyalFlush = false;
    }
}
int playerHand::getHighCard(){
    std::vector<card>::iterator result;
    result = std::max_element(DealtCards.begin(), DealtCards.end(), SortCardsByPips);
    return (*result).get_pips();
}
PlayerHandInfo const playerHand::CheckHand(){
    return HandInfo;
}

int CalculateCombinationScore(PlayerHandInfo &Handinfo, CombinationRank Rank, int basescore) {

    for (auto i : Handinfo.HandCombinations) {
        Handinfo.score = basescore;
        if (i.combination == CombinationRank::RoyalFlush) {
            Handinfo.score += i.combinationpipsvalue;
        }
    }
}

void playerHand::calculateScore() {
    if (HandInfo.HandCombinations.size() != 0) {
        if (HandInfo.hasRoyalFlush) {
            CalculateCombinationScore(HandInfo, CombinationRank::RoyalFlush, 63);
        } else if (HandInfo.hasStraightFlush) {
            CalculateCombinationScore(HandInfo, CombinationRank::StraightFlush, 44);
        } else if (HandInfo.hasStraight) {
            CalculateCombinationScore(HandInfo, CombinationRank::Straight, 27);
        } else if (HandInfo.hasPair) {
            CalculateCombinationScore(HandInfo, CombinationRank::Pair, 13);
        }
    } else {
        sortByPips();
        HandInfo.score = getHighCard();  // score for the high card is the score
    }
}

auto const sortHandByValue = [](playerHand &Hand1,
                                playerHand &Hand2) -> bool {  //todo should be const, find out why it gives error
    return Hand1.getPokerScore() > Hand2.getPokerScore();
};

cardGame::cardGame() {
    //default is poker with 4 players
    numberOfPlayers = 4;
    numberOfCards = 5;
    setup_new_game();
}

cardGame::cardGame(int inputNumberOfPlayers, int inNumberOfCards) {
    numberOfPlayers = inputNumberOfPlayers;
    numberOfCards = inNumberOfCards;
    setup_new_game();
}

cardGame::cardGame(std::vector<playerHand> inputhands) {
    PlayerHands = inputhands;
    setup_new_game();
}


void cardGame::calculatePokerScore(){
    for(auto i= PlayerHands.begin();i!= PlayerHands.end();i++){
        i->calculate5CardPokerScore();
    }

    for(auto i= PlayerHands.begin();i!= PlayerHands.end();i++){
        i->calculate5CardPokerScore();
    }
}

void cardGame::printPokerScores() const {
    for (auto i = PlayerHands.begin(); i != PlayerHands.end(); i++) {
        printCards((*i).DealtCards);                //todo refactor to not reach inside of playerhand
        std::cout << "score " << i->getPokerScore() << std::endl;
    }
}


void cardGame::SortHandsByScores(){
    std::sort(PlayerHands.begin(), PlayerHands.end(),sortHandByValue);
}
void cardGame::PrintHands() {        //test function
    printCards(PlayerHands[0].DealtCards);
    PlayerHands[0].sortByPips();
    printCards(PlayerHands[0].DealtCards);
    PlayerHands[0].sortBySuit();
    printCards(PlayerHands[0].DealtCards);
    PlayerHands[0].calculate5CardPokerScore();
    SortHandsByScores();
    printPokerScores();
}

void cardGame::PrintBoard() {        //test function
    printCards(board);
}

void cardGame::setup_new_game() {
    for (int n = 0; n != numberOfPlayers; n++) {
        PlayerHands.emplace_back();
    }
    int numberOfCardsNeeded = numberOfCards * numberOfPlayers + board_size;  //todo without throw away for now
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
    for (int it = 0; it != board_size; it++) {
        Deck.dealOneCard(board);
    }
    std::cout << "after dealing, deck size is " << Deck.getDeckSize() << std::endl;
}

//save game takes all cards on table and saves them to a common structure
// make the deck and the players hands point to the Deck. move the deck?
