// Created by ryanj on 7/6/2019.
//

#include <iostream>
#include <memory>
#include <ostream>
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
std::string card::print_CardDescription(int key) {
        return CardDescription[key];
        }

Combination::Combination(poker::CombinationRank rank, int mepips) {
    combination = rank;
    if (mepips == 1) {
        combinationpipsvalue = 14;   // Ace in the hole
    } else {
        combinationpipsvalue = mepips;
    }
}


std::ostream &operator<<(std::ostream &out, const pips &p) {
    std::cout << CardDescription[p.get_pips_value()];
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
    std::cout << " of";
    std::cout << c.get_suit();
    return out;
}

std::ostream &operator<<(std::ostream &out, const CombinationRank &combinationRank) {

    if (combinationRank == CombinationRank::Straight) { std::cout << " Straight "; }
    else if (combinationRank == CombinationRank::StraightFlush) { std::cout << " StraightFlush "; }
    else if (combinationRank == CombinationRank::RoyalFlush) { std::cout << " RoyalFlush "; }
    else if (combinationRank == CombinationRank::Pair) { std::cout << " Pair "; }
    else if (combinationRank == CombinationRank::Flush) { std::cout << " Flush "; }
    else if (combinationRank == CombinationRank::HighCard) { std::cout << " HighCard "; }
    else {}
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
card cardDeck::dealOneCard() {
    card dealtCardFromDeck = deck.back();   //todo: learn about move semantics and get rid of the temp copy
    deck.pop_back();
    return dealtCardFromDeck;
}

heapDeck::heapDeck(){
    cardSuit currentSuit{cardSuit::CLUB};
    for (int suitIterator = 0; suitIterator <= 3; suitIterator++) {
        currentSuit = static_cast<cardSuit>(suitIterator);
        for (int i = 1; i <= 13; i++) {
            deck.emplace_back(std::make_unique<card>(currentSuit, i));
        }
    }
}

void heapDeck::shuffleDeck(){
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::shuffle(deck.begin(), deck.end(), std::default_random_engine(seed));
        }

std::unique_ptr<card> heapDeck::dealOneCard() {
    std::unique_ptr<card> dealtCardFromDeck  = std::move(deck.back());   //todo: learn about move semantics and get rid of the temp copy
    deck.pop_back();
    return dealtCardFromDeck;
}

void playerHand::takeCard(card NewCard) {
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
    sortByPips();
    checkallMultiples();
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
std::vector<card> playerHand::showHand(){
     return DealtCards;
 }

void playerHand::checkallMultiples() {

    // four of a kind
    if (DealtCards.at(0).get_pips() == DealtCards.at(3).get_pips()
        || DealtCards.at(1).get_pips() == DealtCards.at(4).get_pips()) {
        HandInfo.hasFourOfaKind == true;
        HandInfo.hasThreeOfaKind == false;
        HandInfo.hasTwoPair == false;
        Combination foursome(CombinationRank::FourOfaKind, DealtCards.at(1).get_pips());
        HandInfo.HandCombinations.emplace_back(foursome);
    }

        // three of a kind
    else if (DealtCards.at(0).get_pips() == DealtCards.at(2).get_pips()
             || DealtCards.at(1).get_pips() == DealtCards.at(3).get_pips()
             || DealtCards.at(2).get_pips() == DealtCards.at(4).get_pips()) {
        HandInfo.hasFourOfaKind == false;
        HandInfo.hasThreeOfaKind == true;
        HandInfo.hasTwoPair == false;
        Combination three(CombinationRank::ThreeOfaKind, DealtCards.at(2).get_pips());
        HandInfo.HandCombinations.emplace_back(three);

        // two pair
    } else if (((DealtCards.at(0).get_pips() == DealtCards.at(1).get_pips()) &&
                (DealtCards.at(2).get_pips() == DealtCards.at(3).get_pips()))
               || ((DealtCards.at(1).get_pips() == DealtCards.at(2).get_pips()) &&
                   (DealtCards.at(3).get_pips() == DealtCards.at(4).get_pips()))
               || ((DealtCards.at(0).get_pips() == DealtCards.at(1).get_pips()) &&
                   (DealtCards.at(3).get_pips() == DealtCards.at(4).get_pips()))
            ) {
        HandInfo.hasFourOfaKind == false;
        HandInfo.hasThreeOfaKind == false;
        HandInfo.hasTwoPair == true;

        Combination twopair(CombinationRank::TwoPair, DealtCards.at(4).get_pips());
        HandInfo.HandCombinations.emplace_back(twopair);
    }

    //single pair
    if (HandInfo.hasTwoPair || HandInfo.hasFourOfaKind) {
        HandInfo.hasPair == false;
    } else {
        checkForPair();
    }
}

void playerHand::checkForPair() {
    for (auto i = DealtCards.begin(); i != DealtCards.end() - 1; i++) {
        if ((*i).get_pips() == ((*(i + 1)).get_pips())) {
            HandInfo.hasPair = true;
            Combination pair{CombinationRank::Pair, (*i).get_pips()};
            HandInfo.HandCombinations.emplace_back(pair);
            return;
        }
    }
}

void playerHand::checkForFlush() {

//    cardSuit  first_suit = DealtCards.front().get_suit();
//    if ( std::all_of(DealtCards.begin(), DealtCards.end(), []( card a_card, cardSuit first_suit){return a_card.get_suit() == first_suit;}) )
//    {
//        HandInfo.hasFlush = true;
//    }

    for (auto i = DealtCards.begin();
         i != DealtCards.end() - 1; i++) {   // todo: look for a way to remove the pointer arithmatic from this code?
        if ((*i).get_suit() != ((*(i + 1)).get_suit())) {
            HandInfo.hasFlush = false;
            return;
        }
    }
    HandInfo.hasFlush = true;
    Combination flush(CombinationRank::Flush, DealtCards.at(DealtCards.size() - 1).get_pips());  //high card
    HandInfo.HandCombinations.emplace_back(flush);
}

void playerHand::checkForStraight() {
    HandInfo.hasStraight = true;
    if (DealtCards.front().get_pips() == 1 && DealtCards.back().get_pips() == 13) {    //only ace high straight possible
        for (auto i = DealtCards.begin() + 1; i != DealtCards.end() - 1; i++) {
            if ((*i).get_pips() + 1 != ((*(i + 1)).get_pips())) {
                HandInfo.hasStraight = false;
                break;
            }
        }
        Combination straight(CombinationRank::Straight, 13);
        HandInfo.HandCombinations.emplace_back(straight);
    } else {
        for (auto i = DealtCards.begin(); i != DealtCards.end() - 1; i++) {               //standard straight
            if ((*i).get_pips() + 1 != ((*(i + 1)).get_pips())) {
                HandInfo.hasStraight = false;
                break;
            }
            Combination straight(CombinationRank::Straight, DealtCards.back().get_pips());
            HandInfo.HandCombinations.emplace_back(straight);
        }
    }
}

void playerHand::checkForStraightFlush(){
    if (HandInfo.hasStraightFlush = HandInfo.hasStraight && HandInfo.hasFlush) {
        Combination straightflush(CombinationRank::StraightFlush, DealtCards.back().get_pips());  //high card
        HandInfo.HandCombinations.emplace_back(straightflush);
    }
}
void playerHand::checkForRoyalFlush(){
    int minPips = 10;
    sortByPips();
    if ((DealtCards.front().get_pips() == 1)  // is ace
        && (DealtCards.at(1).get_pips() == minPips)
        && HandInfo.hasFlush) {
        HandInfo.hasRoyalFlush = true;
        Combination royalflush(CombinationRank::RoyalFlush, DealtCards.back().get_pips());
        HandInfo.HandCombinations.emplace_back(royalflush);
    } else {
        HandInfo.hasRoyalFlush = false;
    }
}
int playerHand::getHighCard(){
    std::vector<card>::iterator result = std::max_element(DealtCards.begin(), DealtCards.end(), SortCardsByPips);
    return (*result).get_pips();  // todo Null Ptr check
}
PlayerHandInfo const playerHand::CheckHand(){
    return HandInfo;
}

int playerHand::CalculateCombinationScore(PlayerHandInfo &Handinfo, const CombinationRank Rank) {

    for (auto i : Handinfo.HandCombinations) {
        Handinfo.score = CombinationBaseScore[Rank];
        Handinfo.score += i.combinationpipsvalue;
        std::cout << "score" << Handinfo.score << "" << i.combination << i.combinationpipsvalue << std::endl;
        return Handinfo.score;
        }
}

void playerHand::calculateScore() {
    if (HandInfo.HandCombinations.size() != 0) {
        if (HandInfo.hasRoyalFlush) {
            CalculateCombinationScore(HandInfo, CombinationRank::RoyalFlush);
        } else if (HandInfo.hasStraightFlush) {
            CalculateCombinationScore(HandInfo, CombinationRank::StraightFlush);
        } else if (HandInfo.hasStraight) {
            CalculateCombinationScore(HandInfo, CombinationRank::Straight);
        } else if (HandInfo.hasThreeOfaKind) {
            CalculateCombinationScore(HandInfo, CombinationRank::ThreeOfaKind);
        } else if (HandInfo.hasTwoPair) {
            CalculateCombinationScore(HandInfo, CombinationRank::TwoPair);
        } else if (HandInfo.hasPair) {
            CalculateCombinationScore(HandInfo, CombinationRank::Pair);
        }
    } else {
        HandInfo.score = getHighCard();  // score for the high card is the score
    }
}


auto const sortHandByValue = [](playerHand &Hand1,
                                playerHand &Hand2) -> bool {  //todo should be const, find out why it gives error
    return Hand1.getPokerScore() > Hand2.getPokerScore();
};

cardGame::cardGame() : numberOfPlayers(2), numberOfCards(5), board_size(5) {
    //default is poker with 4 players
    setup_new_game();
}

cardGame::cardGame(int inputNumberOfPlayers, int inNumberOfCards) : board_size(5) {
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
    for ( auto PlayerHand : PlayerHands) {
        printCards(PlayerHand.showHand());                //todo refactor to not reach inside of playerhand
        std::cout << "score " << PlayerHand.getPokerScore() << std::endl;
    }
}


void cardGame::SortHandsByScores(){
    std::sort(PlayerHands.begin(), PlayerHands.end(),sortHandByValue);
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
            PlayerHands[p].takeCard(Deck.dealOneCard());
        }
    }
    for (int it = 0; it != board_size; it++) {
        board.emplace_back(Deck.dealOneCard());
    }
    std::cout << "after dealing, deck size is " << Deck.getDeckSize() << std::endl;
}

//save game takes all cards on table and saves them to a common structure
// make the deck and the players hands point to the Deck. move the deck?
