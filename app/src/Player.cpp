#include <Player.h>
#include <algorithm>

Player::Player(std::string name_, std::string color_){
    this->name = name_;
    this->color = color_;
    this->isSafe = false;
    this->turnback = false;
    this->sdlSetup = SDLSetup::getInstance();
}

Player::~Player(){}

void Player::setName(std::string name_){
    this->name = name_;
}

std::string Player::getName(){
    return name;
}

void Player::setColor(std::string color_){
    this->color = color_;
}

std::string Player::getColor(){
    return color;
}

int Player::getNumTreasure(){
    return treasure.size();
}

void Player::addTreasure(Tile* tile){
    treasure.push_back(tile);
}

void Player::addTreasureToVault(std::vector<Tile*> tiles){
    vault.insert(vault.end(), tiles.begin(), tiles.end());
}

std::vector<Tile*> Player::getTreasures(){
    return treasure;
}

std::vector<Tile*> Player::getVaultTreasures(){
    return vault;
}

void Player::removeTreasure(Tile* tile){
    treasure.erase(std::remove(treasure.begin(), treasure.end(), tile), treasure.end());
}

void Player::removeAllTreasure(){
    for(auto item: this->treasure){
        delete item;
    }
    treasure.clear();
}

void Player::setLocation(int i){
    location = i;
}

int Player::getLocation(){
    return location;
}

void Player::setTurnBack(bool turnback_){
    this->turnback = turnback_;
}

bool Player::getTurnBack(){
    return this->turnback;
}

void Player::setIsSafe(bool isSafe_){
    this->isSafe = isSafe_;
}

bool Player::getIsSafe(){
    return this->isSafe;
}

Tile* Player::getLowestTreasure(){
    Tile* minValueTile;
    int minValue = 5;
    for(auto tile : treasure) {
        if(tile->getDots() < minValue) {
            minValuie = tile->getDots();
            minValueTile = tile;
        }
    }
    return minValueTile;
}