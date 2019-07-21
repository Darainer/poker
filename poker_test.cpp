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
    TestStraight.Calculate5CardPokerScore();
    EXPECT_EQ(TestStraight.hasStraight, true);
}

TEST(PlayerHand_SimplePairTest, HandlesZeroInput) {
    poker::playerHand TestPair;
    int value;
    int max_pips = 13; //king
    for (value = 0; value != max_pips+1;value++ ) {
        TestPair.DealtCards.emplace_back(poker::card(poker::cardSuit::SPADE, poker::pips(value)));
        TestPair.DealtCards.emplace_back(poker::card(poker::cardSuit::SPADE, poker::pips(value)));
        TestPair.Calculate5CardPokerScore();
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

    testHand.Calculate5CardPokerScore();
    EXPECT_EQ(testHand.hasFlush, true);
    EXPECT_EQ(testHand.hasPair, false);
    EXPECT_EQ(testHand.hasStraight, false);

}

TEST(PlayerHand_RoyalFlushTest, HandlesZeroInput) {
    poker::playerHand testHand;

    testHand.DealtCards.emplace_back(poker::card(poker::cardSuit::SPADE, poker::pips(9)));
    testHand.DealtCards.emplace_back(poker::card(poker::cardSuit::SPADE, poker::pips(10)));
    testHand.DealtCards.emplace_back(poker::card(poker::cardSuit::SPADE, poker::pips(11)));
    testHand.DealtCards.emplace_back(poker::card(poker::cardSuit::SPADE, poker::pips(12)));
    testHand.DealtCards.emplace_back(poker::card(poker::cardSuit::SPADE, poker::pips(13)));

    testHand.Calculate5CardPokerScore();
    EXPECT_EQ(testHand.hasFlush, true);
    EXPECT_EQ(testHand.hasPair, false);
    EXPECT_EQ(testHand.hasStraight, true);
    EXPECT_EQ(testHand.hasRoyalFlush,true);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
