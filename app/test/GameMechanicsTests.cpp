#include <gtest/gtest.h>
#include <GameMechanics.h>
#include <Player.h>

class GameMechanicsTests : public ::testing::Test {
    public:
        GameMechanics *mechanics;

    void SetUp() {
        mechanics = new GameMechanics();
    }
    void TearDown() {
        delete mechanics;
    }
};

TEST_F(GameMechanicsTests, testAddPlayer) {

    // ** Adding the first 6 players that should
    // ** all be added succesfully
    mechanics->addPlayer("test1", "red");
    ASSERT_EQ(mechanics->getPlayers().size(), 1);
    mechanics->addPlayer("test2", "blue");
    ASSERT_EQ(mechanics->getPlayers().size(), 2);
    mechanics->addPlayer("test3", "green");
    ASSERT_EQ(mechanics->getPlayers().size(), 3);
    mechanics->addPlayer("test4", "yellow");
    ASSERT_EQ(mechanics->getPlayers().size(), 4);
    mechanics->addPlayer("test5", "pink");
    ASSERT_EQ(mechanics->getPlayers().size(), 5);
    mechanics->addPlayer("test6", "magenta");
    ASSERT_EQ(mechanics->getPlayers().size(), 6);
 
    // ! This player should not be added - 
    // ! that is why the size stays the same
    mechanics->addPlayer("test7", "orange");
    ASSERT_EQ(mechanics->getPlayers().size(), 6);
}

TEST_F(GameMechanicsTests, testMovePlayer){
    // ** vector of test distances to move
    std::vector<int> distances = {2, 2, 4, 6};

    // ** test1 --> Moving normally 2 spaces
    // ** starts on space 1
    mechanics->addPlayer("test1", "red");
    mechanics->getPlayers()[0]->setLocation(1);
    mechanics->movePlayer(distances[0]);
    ASSERT_EQ(mechanics->getPlayers()[0]->getLocation(), 3);

    // ** test2 --> Moving over the end of the path
    // ** starts on path.size() - 2 (second to last spot), moves forward 2
    mechanics->getPlayers()[0]->setLocation(mechanics->getPath()->getPathSize() - 2);
    mechanics->movePlayer(distances[1]);
    ASSERT_EQ(mechanics->getPlayers()[0]->getLocation(), mechanics->getPath()->getPathSize() - 1);

    // ** test3 --> Moving backwards 4 spaces
    // ** turnBack is set to true
    mechanics->getPlayers()[0]->setTurnBack(true);
    mechanics->getPlayers()[0]->setLocation(5);
    mechanics->movePlayer(distances[2]);
    ASSERT_EQ(mechanics->getPlayers()[0]->getLocation(), 1);

    // ** test4 --> Moving back into home
    // ** turnBack is set to true
    // ** will move back 6 spaces, starting on 5
    mechanics->getPlayers()[0]->setTurnBack(true);
    mechanics->getPlayers()[0]->setLocation(3);
    mechanics->movePlayer(distances[3]);
    ASSERT_EQ(mechanics->getPlayers()[0]->getLocation(), -1);
}

TEST_F(GameMechanicsTests, testRollRice){
    for(int i = 0; i < 50; i++){
        int roll = mechanics->rollDice();
        ASSERT_GE(roll, 2);
        ASSERT_LE(roll, 6);
    }
}

TEST_F(GameMechanicsTests, testEndTurn){
    mechanics->addPlayer("test1", "red");
    mechanics->addPlayer("test2", "blue");
    mechanics->addPlayer("test3", "green");
    mechanics->addPlayer("test4", "yellow");
    mechanics->addPlayer("test5", "pink");
    mechanics->addPlayer("test6", "magenta"); 
    // ** make sure that when a game starts, currPlayerIndex = 0
    int start_value = mechanics->getCurrPlayerIndex();
    ASSERT_EQ(start_value, 0);
    // ** run through the six possible players
    // ** adding one extra to make sure it circles
    // ** around to the beginning
    mechanics->endTurn();
    int test1 = mechanics->getCurrPlayerIndex();
    ASSERT_EQ(test1, 1);
    mechanics->endTurn();
    int test2 = mechanics->getCurrPlayerIndex();
    ASSERT_EQ(test2, 2);
    mechanics->endTurn();
    int test3 = mechanics->getCurrPlayerIndex();
    ASSERT_EQ(test3, 3);
    mechanics->endTurn();
    int test4 = mechanics->getCurrPlayerIndex();
    ASSERT_EQ(test4, 4);
    mechanics->endTurn();
    int test5 = mechanics->getCurrPlayerIndex();
    ASSERT_EQ(test5, 5);
    // ** Extra turn to make sure circle back
    mechanics->endTurn();
    int test6 = mechanics->getCurrPlayerIndex();
    ASSERT_EQ(test6, 0);
}

TEST_F (GameMechanicsTests, tesetReplaceTile){
    // ! Replace True
    mechanics->addPlayer("test1", "red");
    Tile *treasureTile = new Tile(1, 3);
    mechanics->getPlayers()[0]->setLocation(3);
    mechanics->getPlayers()[0]->addTreasure(treasureTile);
    ASSERT_EQ(mechanics->getPlayers()[0]->getNumTreasure(), 1);
    mechanics->replaceTile(true);
    ASSERT_EQ(mechanics->getPlayers()[0]->getNumTreasure(), 0);
    ASSERT_EQ(mechanics->getPath()->getPath()[3], treasureTile);


    // ! Replace False
    mechanics->replaceTile(false);
    ASSERT_EQ(mechanics->getPlayers()[0]->getNumTreasure(), 1);
    ASSERT_EQ(mechanics->getPlayers()[0]->getTreasures()[0], treasureTile);
    ASSERT_EQ(mechanics->getPath()->getPath()[3], nullptr);
}