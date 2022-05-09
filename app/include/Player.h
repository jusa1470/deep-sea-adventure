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
        Tile* getLowestTreasure();
        void setLocation(int i);
        int getLocation();
        void setTurnBack(bool turnback_);
        bool getTurnBack();
        void setIsSafe(bool isSafe_);
        bool getIsSafe();
    
    private:
        std::string name;
        std::string color;
        std::vector<Tile *> treasure;
        std::vector<Tile *> vault;
        int location;
        bool turnback;
        bool isSafe;
        SDLSetup *sdlSetup;
};

#endif