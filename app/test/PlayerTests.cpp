#include <gtest/gtest.h>
#include <Player.h>

class PlayerTests : public ::testing::Test {
    protected:
        Player *testPlayer;
        Tile *tile;
        Tile *tile2;
        void SetUp() {
            testPlayer = new Player("testDummy", "red");
            tile = new Tile(2, 8);
            tile2 = new Tile(3, 14);
        }
        void TearDown() {
            delete testPlayer;
        }
};

TEST_F(PlayerTests, addTreasureANDgetNumTreasureTest) {
    EXPECT_EQ(0, testPlayer->getNumTreasure());
    testPlayer->addTreasure(tile);
    EXPECT_EQ(1, testPlayer->getNumTreasure());
}

TEST_F(PlayerTests, addTreasuresToVaultTest) {
    EXPECT_EQ(0, testPlayer->getVaultTreasures().size());
    std::vector<Tile *> tmp = testPlayer->getVaultTreasures();
    tmp.push_back(tile);
    testPlayer->addTreasureToVault(tmp);
    EXPECT_EQ(1, testPlayer->getVaultTreasures().size());
}

TEST_F(PlayerTests, removeTreasureTest) {
    EXPECT_EQ(0, testPlayer->getNumTreasure());
    testPlayer->addTreasure(tile);
    EXPECT_EQ(1, testPlayer->getNumTreasure());
    testPlayer->addTreasure(tile2);
    EXPECT_EQ(2, testPlayer->getNumTreasure());
    testPlayer->removeTreasure(tile);
    EXPECT_EQ(1, testPlayer->getNumTreasure());
    EXPECT_EQ(tile2, testPlayer->getTreasures()[0]);
}

TEST_F(PlayerTests, removeAllTreasureTest) {
    EXPECT_EQ(0, testPlayer->getNumTreasure());
    testPlayer->addTreasure(tile);
    EXPECT_EQ(1, testPlayer->getNumTreasure());
    testPlayer->addTreasure(tile2);
    EXPECT_EQ(2, testPlayer->getNumTreasure());
    testPlayer->removeAllTreasure();
    EXPECT_EQ(0, testPlayer->getNumTreasure());
}