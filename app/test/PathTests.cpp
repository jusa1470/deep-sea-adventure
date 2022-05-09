#include <gtest/gtest.h>
#include <Tile.h>
#include <Path.h>
#include <vector>

class PathTests : public ::testing::Test {
    public:
        Path *path;
    void SetUp() {
        path = new Path();
    }
    void TearDown() {
        delete path;
    }
};

TEST_F(PathTests, constructorTest) {
    std::vector<Tile *> path_ = path->getPath();
    ASSERT_EQ(32, path_.size());
    for(int i = 0; i < 8; i++){
        EXPECT_EQ(1, path_[i]->getDots());
        EXPECT_GE(path_[i]->getValue(), 0);
        EXPECT_LE(path_[i]->getValue(), 3);
    }
    for(int i = 8; i < 16; i++){
        EXPECT_EQ(2, path_[i]->getDots());
        EXPECT_GE(path_[i]->getValue(), 4);
        EXPECT_LE(path_[i]->getValue(), 7);
    }
    for(int i = 16; i < 24; i++){
        EXPECT_EQ(3, path_[i]->getDots());
        EXPECT_GE(path_[i]->getValue(), 8);
        EXPECT_LE(path_[i]->getValue(), 11);
    }
    for(int i = 24; i < 32; i++){
        EXPECT_EQ(4, path_[i]->getDots());
        EXPECT_GE(path_[i]->getValue(), 12);
        EXPECT_LE(path_[i]->getValue(), 15);
    }

}

TEST_F(PathTests, getTileTest) {
    Tile *tile = path->getTile(4);
    EXPECT_EQ(1, tile->getDots());
    EXPECT_GE(tile->getValue(), 0);
    EXPECT_LE(tile->getValue(), 3);

    Tile *tile2 = path->getTile(28);
    EXPECT_EQ(4, tile2->getDots());
    EXPECT_GE(tile2->getValue(), 12);
    EXPECT_LE(tile2->getValue(), 15);
}

TEST_F(PathTests, replaceTileTest) {
    Tile *replaceTile = new Tile(4, 14);
    Tile *oldTile = path->replaceTile(3, replaceTile);
    Tile *pathTile = path->getTile(3);
    EXPECT_EQ(4, pathTile->getDots());
    EXPECT_EQ(14, pathTile->getValue());
    EXPECT_EQ(1, oldTile->getDots());
    EXPECT_GE(oldTile->getValue(), 0);
    EXPECT_LE(oldTile->getValue(), 3);
}