#include <tuple>
#include <SDLSetup.h>

#ifndef _TILE_H
#define _TILE_H

class Tile {
    public:
        Tile(int dots_, int value_);
        ~Tile(){};
        void setDots(int dots_);
        int getDots();
        void setValue(int value_);
        int getValue();
        void setLocation(int i, int j);
        std::tuple<int, int> getLocation();

    private:
        int dots;
        int value;
        std::tuple<int, int> location;
        SDLSetup* sdlSetup;
};

#endif