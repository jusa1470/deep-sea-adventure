#include <GameMechanics.h>
#include <math.h>
#include <vector>

GameMechanics::GameMechanics(){
    this->sdlSetup = SDLSetup::getInstance();
    this->path = Path::getInstance();
    this->currPlayerIndex = 0;
}

GameMechanics::~GameMechanics(){
    delete this->path;
}

int GameMechanics::movePlayer(int distance){
    if(players[currPlayerIndex]->getTurnBack()){
        distance *= -1;
    }
    int new_position = players[currPlayerIndex]->getLocation() + distance;
    if(new_position > 0 && new_position < this->path->getPath().size()){
        players[currPlayerIndex]->setLocation(new_position);
    } else if(new_position >= this->path->getPath().size()){
        players[currPlayerIndex]->setLocation(this->path->getPath().size() - 1);
    } else {
        players[currPlayerIndex]->setLocation(-1);
        players[currPlayerIndex]->setIsSafe(true);
    }
    return new_position;
}

int GameMechanics::rollDice(){
    return (rand() % 4) + 2;
}

void GameMechanics::replaceTile(bool replace){
    if(replace) { // ** replace blank tile with player's lowest treasure
        Tile* replaceTile = players[currPlayerIndex]->getLowestTreasure();
        players[currPlayerIndex]->removeTreasure(replaceTile);
        path->replaceTile(players[currPlayerIndex]->getLocation(), replaceTile);
    } else { // ** take the tile and replace with a blank
        Tile* takenTile = path->replaceTile(players[currPlayerIndex]->getLocation(), nullptr);
        players[currPlayerIndex]->addTreasure(takenTile);
    }
}

int GameMechanics::endTurn(){
    this->currPlayerIndex = (this->currPlayerIndex + 1) % players.size();
    return this->currPlayerIndex;
}

void GameMechanics::addPlayer(std::string name, std::string color){
    if(players.size() < 6){
        Player *new_player = new Player(name, color);
        players.vector::push_back(new_player);
    }
}

std::vector<Player*> GameMechanics::getPlayers(){
    return this->players;
}

void GameMechanics::setPlayers(std::vector<Player*> players_){
    this->players = players_;
}

int GameMechanics::getCurrPlayerIndex(){
    return this->currPlayerIndex;
}

void GameMechanics::setCurrPlayerIndex(int currPlayerIndex_){
    this->currPlayerIndex = currPlayerIndex_;
}

Path* GameMechanics::getPath(){
    return this->path;
}

void GameMechanics::setPath(Path* path_){
    this->path = path_;
}