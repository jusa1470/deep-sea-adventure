#include <gtest/gtest.h>
#include <Tile.h>

class TileTests : public ::testing::Test {
    protected:
        Tile* testTile;

        void SetUp() {
            testTile = new Tile(2, 8);
        }
        void TearDown() {
            delete testTile;
        }
};

TEST_F(TileTests, setLocationTest) {
    std::tuple<int, int> expected{-1, -1};
    EXPECT_EQ(expected, testTile->getLocation());
    
    testTile->setLocation(4, 6);
    expected = {4, 6};
    EXPECT_EQ(expected, testTile->getLocation());
}