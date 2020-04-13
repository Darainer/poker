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
    for (int suitIterator = 1; suitIterator <= 4; suitIterator++) {
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
    HandInfo.hasPair = false;
    HandInfo.hasFlush = false;
    HandInfo.hasRoyalFlush = false;
    HandInfo.hasStraight = false;
    HandInfo.hasStraightFlush = false;
    HandInfo.score = -1;
}
void playerHand::sortByPips() {
    std::sort(DealtCards.begin(), DealtCards.end(), SortCardsByPips);
}
void playerHand::sortBySuit() {
    std::sort(DealtCards.begin(), DealtCards.end(), sortCardsBySuit);
}

void playerHand::calculate5CardPokerScore() {
    //find_besthand();
    checkForRoyalFlush();
    checkForStraightFlush();
    checkForStraight();
    checkForFlush();
    checkForPair();



    calculateScore();
}

int playerHand::getPokerScore() const {
    //calculate5CardPokerScore();
    return HandInfo.score;
}

void printCards(const std::vector<card> &Cards) {
    for (auto i : Cards) {
        std::cout << i << std::endl;
    }
    std::cout << std::endl;
}
void playerHand::checkForStraight() {
    sortByPips();
    HandInfo.hasStraight = true;
    for (auto i = DealtCards.begin();
         i != DealtCards.end() - 1; i++) {   // todo: look for a way to remove the pointer arithmatic from this code?
        if ((*i).get_pips() + 1 != ((*(i + 1)).get_pips()))
            HandInfo.hasStraight = false;
        }
}
void playerHand::checkForPair() {
    sortByPips();
    // for each unique pips, count the elements with the same
    // three of a kind, 4 of a kind
    HandInfo.hasPair = false;
    //int uniquePips = std::count (DealtCards.begin(),DealtCards.end(),CardsEqualByPips);
    for (auto i = DealtCards.begin(); i != DealtCards.end() - 1; i++) {
        if ((*i).get_pips() == ((*(i + 1)).get_pips())) {
            HandInfo.hasPair = true;
        }
    }
}
void playerHand::checkForFlush() {
    HandInfo.hasFlush = true;
    for (auto i = DealtCards.begin(); i != DealtCards.end() - 1; i++) {
        if ((*i).get_suit() != ((*(i + 1)).get_suit() )) {
            HandInfo.hasFlush = false;
        }
    }
}
void playerHand::checkForStraightFlush(){
    checkForStraight();
    checkForFlush();
    HandInfo.hasStraightFlush = HandInfo.hasStraight && HandInfo.hasFlush;
}
void playerHand::checkForRoyalFlush(){
    int minPips = 9; //jack
    checkForFlush();
    sortByPips();
    if ((DealtCards.front().get_pips() >= minPips) && HandInfo.hasFlush){
        HandInfo.hasRoyalFlush= true;
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
void playerHand::calculateScore(){
    if(HandInfo.hasRoyalFlush){HandInfo.score= 17;}
    else if(HandInfo.hasStraightFlush){HandInfo.score = 16;}
    else if(HandInfo.hasStraight){HandInfo.score= 15;}
    else if(HandInfo.hasPair){HandInfo.score = 14;}
    else{
        sortByPips();
        HandInfo.score = getHighCard();  // score for the high card is the score
    }
}

auto const sortHandByValue = [](playerHand &Hand1,
                                playerHand &Hand2) -> bool {  //todo should be const, find out why it gives error
    return Hand1.getPokerScore() < Hand2.getPokerScore();
};

cardGame::cardGame() {
    setup();
}
cardGame::cardGame(int inputNumberOfPlayers, int inNumberOfCards) {
    numberOfPlayers = inputNumberOfPlayers;
    numberOfCards = inNumberOfCards;
    setup();
}
void cardGame::dealNewPokerGame() {
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

void cardGame::setup(){
    for (int n = 0; n != numberOfPlayers; n++) {
        PlayerHands.emplace_back();
    }
}

