#include <string>
#include <SDL.h>
#include <SDL_image.h>

#ifndef _LTEXTURE_H
#define _LTEXTURE_H

// Texture wrapper class
class LTexture {
public:
    // Initalizes variables
    LTexture(){};

    // Deallocates memory
    ~LTexture(){};

    // Loads image at specified path
    // bool loadFromFile(std::string path);

    // Deallocates texture
    // void free();

    // Renders texture at given point
    void render(SDL_Renderer * gRenderer, int x, int y, SDL_Rect * clip = nullptr);

    // Gets image dimensions
    int getWidth(){return mWidth;};
    int getHeight(){return mHeight;};

private:
    // The actual hardware texture
    SDL_Texture * mTexture;

    // Image dimensions
    int mWidth;
    int mHeight;
};

#endif