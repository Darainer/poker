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

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
