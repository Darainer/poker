//
// Created by ryanj on 7/21/2019.
//
#include "poker.h"
#include "googletest/googletest/include/gtest/gtest.h"

TEST(PlayerHand_StraightTest, HandlesZeroInput) {
    poker::playerHand TestStraight;
    for(int i = 0; i!= 5; i++) {
        TestStraight.DealtCards.emplace_back(poker::card(poker::cardSuit::SPADE, poker::pips(i)));
    }
    TestStraight.calculate5CardPokerScore();
    EXPECT_EQ(TestStraight.hasStraight, true);
}
TEST(PlayerHand_PairTest, HandlesZeroInput) {
    poker::playerHand TestPair;
    int value;
    int max_pips = 13; //king
    TestPair.DealtCards.emplace_back(poker::card(poker::cardSuit::SPADE, poker::pips(0)));
    TestPair.DealtCards.emplace_back(poker::card(poker::cardSuit::HEART, poker::pips(0)));
    TestPair.DealtCards.emplace_back(poker::card(poker::cardSuit::CLUB, poker::pips(3)));
    TestPair.DealtCards.emplace_back(poker::card(poker::cardSuit::DIAMOND, poker::pips(1)));
    TestPair.DealtCards.emplace_back(poker::card(poker::cardSuit::SPADE, poker::pips(2)));
    TestPair.calculate5CardPokerScore();
    EXPECT_EQ(TestPair.hasPair, true);
}

TEST(PlayerHand_SimplePairTest, HandlesZeroInput) {
    poker::playerHand TestPair;
    int value;
    int max_pips = 13; //king
    for (value = 0; value != max_pips+1;value++ ) {
        TestPair.DealtCards.emplace_back(poker::card(poker::cardSuit::SPADE, poker::pips(value)));
        TestPair.DealtCards.emplace_back(poker::card(poker::cardSuit::SPADE, poker::pips(value)));
        TestPair.calculate5CardPokerScore();
        EXPECT_EQ(TestPair.hasPair, true);
    }
}

TEST(PlayerHand_FlushTest, HandlesZeroInput) {
    poker::playerHand testHand;
    testHand.DealtCards.emplace_back(poker::card(poker::cardSuit::SPADE, poker::pips(0)));
    testHand.DealtCards.emplace_back(poker::card(poker::cardSuit::SPADE, poker::pips(2)));
    testHand.DealtCards.emplace_back(poker::card(poker::cardSuit::SPADE, poker::pips(4)));
    testHand.DealtCards.emplace_back(poker::card(poker::cardSuit::SPADE, poker::pips(7)));
    testHand.DealtCards.emplace_back(poker::card(poker::cardSuit::SPADE, poker::pips(10)));
    testHand.calculate5CardPokerScore();
    EXPECT_EQ(testHand.hasFlush, true);
    EXPECT_EQ(testHand.hasPair, false);
    EXPECT_EQ(testHand.hasStraight, false);
}

TEST(PlayerHand_Straight_NoFlushTest, HandlesZeroInput) {
    poker::playerHand testHand;
    testHand.DealtCards.emplace_back(poker::card(poker::cardSuit::SPADE, poker::pips(2)));
    testHand.DealtCards.emplace_back(poker::card(poker::cardSuit::SPADE, poker::pips(3)));
    testHand.DealtCards.emplace_back(poker::card(poker::cardSuit::HEART, poker::pips(4)));
    testHand.DealtCards.emplace_back(poker::card(poker::cardSuit::SPADE, poker::pips(5)));
    testHand.DealtCards.emplace_back(poker::card(poker::cardSuit::DIAMOND, poker::pips(6)));
    testHand.calculate5CardPokerScore();
    EXPECT_EQ(testHand.hasFlush, false);
    EXPECT_EQ(testHand.hasPair, false);
    EXPECT_EQ(testHand.hasStraight, true);
    EXPECT_EQ(testHand.hasRoyalFlush,false);
}

TEST(PlayerHand_RoyalFlushTest, HandlesZeroInput) {
    poker::playerHand testHand;
    testHand.DealtCards.emplace_back(poker::card(poker::cardSuit::SPADE, poker::pips(9)));
    testHand.DealtCards.emplace_back(poker::card(poker::cardSuit::SPADE, poker::pips(10)));
    testHand.DealtCards.emplace_back(poker::card(poker::cardSuit::SPADE, poker::pips(11)));
    testHand.DealtCards.emplace_back(poker::card(poker::cardSuit::SPADE, poker::pips(12)));
    testHand.DealtCards.emplace_back(poker::card(poker::cardSuit::SPADE, poker::pips(13)));
    testHand.calculate5CardPokerScore();
    EXPECT_EQ(testHand.hasFlush, true);
    EXPECT_EQ(testHand.hasPair, false);
    EXPECT_EQ(testHand.hasStraight, true);
    EXPECT_EQ(testHand.hasRoyalFlush,true);
}

// tests for the game

TEST(Game_ScoreTest, HandlesZeroInput) {
    poker::cardGame TestGame(5,5);


    TestGame.calculatePokerScore();
    TestGame.PrintHands();

    //EXPECT_EQ(TestGame.PrintHands(), true);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
