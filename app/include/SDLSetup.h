#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>
#include <mutex>

#ifndef __SDLSetup__
#define __SDLSetup__
class SDLSetup {
    public:
        ~SDLSetup();
        static SDLSetup* getInstance();
        SDLSetup(SDLSetup const&) = delete;
        void operator=(SDLSetup const&) = delete;
        SDL_Texture* loadTexture(const std::string &file);
        void renderTexture(SDL_Texture* texture, SDL_Rect rect, SDL_Rect *clip=nullptr);
        void renderTexture(SDL_Texture* texture, int x, int y, SDL_Rect *clip=nullptr);
        void logSDLError(std::ostream &os, const std::string &msg);
        SDL_Window* getWindow();
        SDL_Renderer* getRenderer();
        void cleanup();

    private:
        SDLSetup();
        SDL_Window* window;
        SDL_Renderer* renderer;
        static SDLSetup* instance;
        static std::mutex mutex;
};

#endif