#include <Path.h>
#include <iostream>

Path::Path(){
    this->path = generateNewPath();
}

Path::~Path(){}

void Path::updatePath(){

}

void Path::setPath(std::vector<Tile *> path_){
    this->path = path_;
}

std::vector<Tile *> Path::getPath(){
    return this->path;
}  

Tile* Path::getTile(int i){
    return this->path[i];
}

void Path::replaceTile(int i, Tile* tile){
    this->path[i] = tile;
}

void Path::removeInstance(){

}

std::vector<Tile*> Path::generateNewPath(){
    std::vector<Tile *> path; 
    for(int i = 0; i < 8; i++){
        path.push_back(new Tile(1, std::rand() % (3 + 1 - 0)));
    }
    for(int i = 0; i < 8; i++){
        path.push_back(new Tile(2, std::rand() % (7 + 1 - 4) + 4));
    }
    for(int i = 0; i < 8; i++){
        path.push_back(new Tile(3, std::rand() % (11 + 1 - 8) + 8));
    }
    for(int i = 0; i < 8; i++){
        path.push_back(new Tile(4, std::rand() % (15 + 1 - 12) + 12));
    }
    return path;
}   