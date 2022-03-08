#include <string>
#include <Tile.h>
#include <SDLSetup.h>
#include <tuple>
#include <vector>

#ifndef _PLAYER_H
#define _PLAYER_H

class Player {
    public:
        Player(std::string name_, std::string color_);
        ~Player();
        void setName(std::string name_);
        std::string getName();
        void setColor(std::string color_);
        std::string getColor();
        int getNumTreasure();
        void addTreasure(Tile* tile);
        void addTreasureToVault(std::vector<Tile*> tiles);
        std::vector<Tile*> getTreasures();
        std::vector<Tile*> getVaultTreasures();
        void removeTreasure(Tile* tile);
        void removeAllTreasure();
        void setLocation(int i, int j);
        std::tuple<int, int> getLocation();
        void setTurnBack(bool turnback_);
    
    private:
        std::string name;
        std::string color;
        std::vector<Tile *> treasure;
        std::vector<Tile *> vault;
        std::tuple<int, int> location;
        bool turnback;
        bool isSafe;
        SDLSetup *sdlSetup;
};

#endif