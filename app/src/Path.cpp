#include <Path.h>
#include <iostream>

Path* Path::instance{nullptr};
std::mutex Path::mutex;

Path::Path(){
    this->path = generateNewPath();
}

Path::~Path(){
    for(int i = 0; i < this->path.size(); i++){
        delete this->path[i];
        this->path[i] = nullptr;
    }
    this->path.clear();
}

Path* Path::getInstance(){
    mutex.lock();
    if(instance == nullptr){
        instance = new Path();
    }
    mutex.unlock();
    return instance;
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

Tile* Path::replaceTile(int i, Tile* tile){
    Tile *old = this->path[i];
    this->path[i] = tile;
    return old;
}

std::vector<Tile*> Path::generateNewPath(){
    std::vector<Tile *> path; 
    for(int i = 0; i < 8; i++){
        //random number is: num % (max + 1 - min) + min
        //this sets the correct bounds for each of the dotted tiles
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