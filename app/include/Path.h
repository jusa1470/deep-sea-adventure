#include <Tile.h>
#include <SDLSetup.h>
#include <vector>
#include <cstdlib>

#ifndef _PATH_H
#define _PATH_H

class Path {
    public:
        static Path* getInstance(){
            static Path* instance;
            return instance;
        }
        Path();
        ~Path();
        void updatePath();
        void setPath(std::vector<Tile *> path_);
        std::vector<Tile *> getPath();
        Tile* getTile(int i);
        void replaceTile(int i, Tile* tile);
        void removeInstance();

    private:
        std::vector<Tile *> path;
        SDLSetup* sdlSetup;
        std::vector<Tile *> generateNewPath();

};

#endif