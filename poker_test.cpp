//
// Created by ryanj on 7/21/2019.
//
#include "poker.h"
#include "googletest/googletest/include/gtest/gtest.h"

using namespace ::poker;

//fixture straight flush
void Fixture_straightFlush(playerHand &hand, cardSuit suit) {
    hand.DealtCards.emplace_back(card(suit, pips(9)));
    hand.DealtCards.emplace_back(card(suit, pips(10)));
    hand.DealtCards.emplace_back(card(suit, pips(11)));
    hand.DealtCards.emplace_back(card(suit, pips(12)));
    hand.DealtCards.emplace_back(card(suit, pips(13)));
}


TEST(PlayerHand_StraightTest, HandlesZeroInput) {
    playerHand TestStraight;
    for(int i = 0; i!= 5; i++) {
        TestStraight.DealtCards.emplace_back(card(cardSuit::SPADE, pips(i)));
    }
    TestStraight.calculate5CardPokerScore();
    PlayerHandInfo HandInfo = TestStraight.CheckHand();
    EXPECT_EQ(HandInfo.hasStraight, true);
}
TEST(PlayerHand_PairTest, HandlesZeroInput) {
    playerHand TestPair;
    TestPair.DealtCards.emplace_back(card(cardSuit::SPADE, pips(0)));
    TestPair.DealtCards.emplace_back(card(cardSuit::HEART, pips(0)));
    TestPair.DealtCards.emplace_back(card(cardSuit::CLUB, pips(3)));
    TestPair.DealtCards.emplace_back(card(cardSuit::DIAMOND, pips(1)));
    TestPair.DealtCards.emplace_back(card(cardSuit::SPADE, pips(2)));
    TestPair.calculate5CardPokerScore();
    PlayerHandInfo HandInfo = TestPair.CheckHand();
    EXPECT_EQ(HandInfo.hasPair, true);
}

TEST(PlayerHand_SimplePairTest, HandlesZeroInput) {
    playerHand TestPair;
    int value;
    int max_pips = 13; //king
    for (value = 0; value != max_pips+1;value++ ) {
        TestPair.DealtCards.emplace_back(card(cardSuit::SPADE, pips(value)));
        TestPair.DealtCards.emplace_back(card(cardSuit::SPADE, pips(value)));
        TestPair.calculate5CardPokerScore();
        PlayerHandInfo HandInfo = TestPair.CheckHand();
        EXPECT_EQ(HandInfo.hasPair, true);
    }
}

TEST(PlayerHand_FlushTest, HandlesZeroInput) {
    playerHand testHand;
    testHand.DealtCards.emplace_back(card(cardSuit::SPADE, pips(0)));
    testHand.DealtCards.emplace_back(card(cardSuit::SPADE, pips(2)));
    testHand.DealtCards.emplace_back(card(cardSuit::SPADE, pips(4)));
    testHand.DealtCards.emplace_back(card(cardSuit::SPADE, pips(7)));
    testHand.DealtCards.emplace_back(card(cardSuit::SPADE, pips(10)));
    testHand.calculate5CardPokerScore();
    PlayerHandInfo HandInfo = testHand.CheckHand();
    EXPECT_EQ(HandInfo.hasFlush, true);
    EXPECT_EQ(HandInfo.hasPair, false);
    EXPECT_EQ(HandInfo.hasStraight, false);
}

TEST(PlayerHand_Straight_NoFlushTest, HandlesZeroInput) {
    playerHand testHand;
    testHand.DealtCards.emplace_back(card(cardSuit::SPADE, pips(2)));
    testHand.DealtCards.emplace_back(card(cardSuit::SPADE, pips(3)));
    testHand.DealtCards.emplace_back(card(cardSuit::HEART, pips(4)));
    testHand.DealtCards.emplace_back(card(cardSuit::SPADE, pips(5)));
    testHand.DealtCards.emplace_back(card(cardSuit::DIAMOND, pips(6)));
    testHand.calculate5CardPokerScore();
    PlayerHandInfo HandInfo = testHand.CheckHand();
    EXPECT_EQ(HandInfo.hasFlush, false);
    EXPECT_EQ(HandInfo.hasPair, false);
    EXPECT_EQ(HandInfo.hasStraight, true);
    EXPECT_EQ(HandInfo.hasRoyalFlush,false);
}

TEST(PlayerHand_RoyalFlushTest, HandlesZeroInput) {
    playerHand testHand;
    Fixture_straightFlush(testHand, cardSuit::CLUB);
    testHand.calculate5CardPokerScore();
    PlayerHandInfo HandInfo = testHand.CheckHand();
    EXPECT_EQ(HandInfo.hasFlush, true);
    EXPECT_EQ(HandInfo.hasPair, false);
    EXPECT_EQ(HandInfo.hasStraight, true);
    EXPECT_EQ(HandInfo.hasRoyalFlush,true);
}

// tests for the game

TEST(Game_ScoreTest, HandlesZeroInput) {


    int number_of_players{4};
    int size_of_hand{2};
    //int size_of_deck{5};
    cardGame mygame(number_of_players, size_of_hand);
    mygame.dealNewPokerGame();
    mygame.calculatePokerScore();

}

//EXPECT_EQ(TestGame.PrintHands(), true);}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
