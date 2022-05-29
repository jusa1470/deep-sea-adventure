#include <vector>
#include <string>
#include <Player.h>
#include <Path.h>
#include <SDLSetup.h>

#ifndef _GAMEMECHANICS_H
#define _GAMEMECHANICS_H

class GameMechanics {
    public:
        GameMechanics();
        ~GameMechanics();
        int movePlayer(int distance);
        int rollDice();
        void replaceTile(bool replace); 
        int endTurn();
        void addPlayer(std::string name, std::string color);
        std::vector<Player*> getPlayers();
        void setPlayers(std::vector<Player*> players_);
        int getCurrPlayerIndex();
        void setCurrPlayerIndex(int currPlayerIndex_);
        Path* getPath();
        void setPath(Path* path_);

    private:
        std::vector<Player*> players;
        int currPlayerIndex;
        Path *path;
};

#endif