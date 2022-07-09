//
// Created by ryanj on 7/21/2019.
//
#include "poker.h"
#include "gtest/gtest.h"
using namespace ::poker;

void Fixture_create_hand(playerHand &hand, cardSuit  &suit, std::vector<int> pips_values ){
    for(int pips : pips_values) 
    hand.takeCard(card(suit, pips ));
}

//fixture straight flush
void Fixture_straightFlush(playerHand &hand, cardSuit &suit) {
    Fixture_create_hand(hand, suit, {9,10,11,12,13});
}

void Fixture_royalFlush(playerHand &hand, cardSuit suit) {
    Fixture_create_hand(hand, suit, {1,10,11,12,13});
}


TEST(PlayerHand_StraightFlushTest, HandlesZeroInput) {
    playerHand TestStraight;
    for (int i = 1; i != 6; i++) {
        TestStraight.takeCard(card(cardSuit::SPADE, pips(i)));
    }
    TestStraight.calculate5CardPokerScore();
    PlayerHandInfo HandInfo = TestStraight.CheckHand();
    EXPECT_EQ(HandInfo.hasStraight, true);
    EXPECT_EQ(HandInfo.hasStraightFlush, true);
    EXPECT_EQ(HandInfo.hasFlush, true);
}
TEST(PlayerHand_PairTest, HandlesZeroInput) {
    playerHand TestPair;
    TestPair.takeCard(card(cardSuit::SPADE, 1));
    TestPair.takeCard(card(cardSuit::HEART, 1));
    TestPair.takeCard(card(cardSuit::CLUB, 5));
    TestPair.takeCard(card(cardSuit::DIAMOND, 9));
    TestPair.takeCard(card(cardSuit::SPADE, 7));
    TestPair.calculate5CardPokerScore();
    PlayerHandInfo HandInfo = TestPair.CheckHand();
    EXPECT_EQ(HandInfo.hasPair, true);
    EXPECT_EQ(HandInfo.score, poker::CombinationBaseScore[poker::CombinationRank::Pair] + 14);
}

TEST(PlayerHand_FlushTest, HandlesZeroInput) {
    playerHand testHand;
    testHand.takeCard(card(cardSuit::SPADE, 0));
    testHand.takeCard(card(cardSuit::SPADE, 2));
    testHand.takeCard(card(cardSuit::SPADE, 4));
    testHand.takeCard(card(cardSuit::SPADE, 7));
    testHand.takeCard(card(cardSuit::SPADE, 10));
    testHand.calculate5CardPokerScore();
    PlayerHandInfo HandInfo = testHand.CheckHand();
    EXPECT_EQ(HandInfo.hasFlush, true);
    EXPECT_EQ(HandInfo.hasPair, false);
    EXPECT_EQ(HandInfo.hasStraight, false);
}

TEST(PlayerHand_Straight_NoFlushTest, HandlesZeroInput) {
    playerHand testHand;
    testHand.takeCard(card(cardSuit::SPADE, 2));
    testHand.takeCard(card(cardSuit::SPADE, 3));
    testHand.takeCard(card(cardSuit::HEART, 4));
    testHand.takeCard(card(cardSuit::SPADE, 5));
    testHand.takeCard(card(cardSuit::DIAMOND, 6));
    testHand.calculate5CardPokerScore();
    PlayerHandInfo HandInfo = testHand.CheckHand();
    EXPECT_EQ(HandInfo.hasFlush, false);
    EXPECT_EQ(HandInfo.hasPair, false);
    EXPECT_EQ(HandInfo.hasStraight, true);
    EXPECT_EQ(HandInfo.hasRoyalFlush,false);
}

TEST(PlayerHand_RoyalFlushTest, HandlesZeroInput) {
    playerHand testHand;
    Fixture_royalFlush(testHand, cardSuit::CLUB);
    testHand.calculate5CardPokerScore();
    PlayerHandInfo HandInfo = testHand.CheckHand();
    EXPECT_EQ(HandInfo.hasFlush, true);
    EXPECT_EQ(HandInfo.hasPair, false);
    EXPECT_EQ(HandInfo.hasStraight, true);
    EXPECT_EQ(HandInfo.hasRoyalFlush,true);
    //EXPECT_EQ(testHand.getPokerScore(), (63 + 13));
}

// tests for the game

TEST(Game_ScoreTest, HandlesZeroInput) {

    int number_of_players{4};
    int size_of_hand{5};
    //int size_of_deck{5};
    cardGame mygame(number_of_players, size_of_hand);
    mygame.calculatePokerScore();
    mygame.SortHandsByScores();
    mygame.printPokerScores();
}

//EXPECT_EQ(TestGame.PrintHands(), true);}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
