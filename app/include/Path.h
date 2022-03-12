#include <Tile.h>
#include <SDLSetup.h>
#include <vector>
#include <cstdlib>
#include <mutex>

#ifndef _PATH_H
#define _PATH_H

class Path {
    public:
        ~Path();
        static Path *getInstance();
        Path(Path const&) = delete;
        void operator=(const Path &) = delete;
        void setPath(std::vector<Tile *> path_);
        std::vector<Tile *> getPath();
        Tile* getTile(int i);
        Tile* replaceTile(int i, Tile* tile);

    private:
        Path();
        static Path* instance;
        static std::mutex mutex;
        std::vector<Tile *> path;
        SDLSetup* sdlSetup;
        std::vector<Tile *> generateNewPath();

};

#endif