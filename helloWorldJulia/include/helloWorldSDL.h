#include <SDL.h>
#include <SDL_image.h>
#include <lTexture.h>

#ifndef _HELLOWORLDSDL_H
#define _HELLOWORLDSDL_H

/********** Global variables **********/

// Key press surfaces constants
enum KeyPressSurfaces {
    KEY_PRESS_SURFACE_DEFAULT = 0,
    KEY_PRESS_SURFACE_UP = 1,
    KEY_PRESS_SURFACE_DOWN = 2,
    KEY_PRESS_SURFACE_LEFT = 3,
    KEY_PRESS_SURFACE_RIGHT = 4,
    KEY_PRESS_SURFACE_TOTAL = 5
};

// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

// The window renderer
SDL_Renderer * gRenderer = NULL;

// Current displayed texture
SDL_Texture * gTexture = NULL;
    
//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* gHelloWorld = NULL;

//The images that correspond to a keypress
SDL_Surface* gKeyPressSurfaces[ KEY_PRESS_SURFACE_TOTAL ];

//Current displayed image
SDL_Surface* gCurrentSurface = NULL;

// Scene sprites
SDL_Rect gSpriteClips[4];
LTexture gSpriteSheetTexture;

#endif