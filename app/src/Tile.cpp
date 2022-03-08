#include <Tile.h>

Tile::Tile(int dots_, int value_) {
    this->dots = dots_;
    this->value = value_;
    this->location = std::tuple<int, int>{-1, -1};
}

void Tile::setDots(int dots_) {
    this->dots = dots_;
}

int Tile::getDots() {
    return dots;
}

void Tile::setValue(int value_) {
    this->value = value_;
}

int Tile::getValue() {
    return value;
}

void Tile::setLocation(int i, int j) {
    this->location = std::tuple<int, int>{i, j};
}

std::tuple<int, int> Tile::getLocation() {
    return location;
}