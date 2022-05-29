#include <SDLSetup.h>

SDLSetup* SDLSetup::instance{nullptr};
std::mutex SDLSetup::mutex;

SDLSetup::SDLSetup(){
    	
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        logSDLError(std::cout, "SDL_Init");
        return;
    }
    if((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG){
        logSDLError(std::cout, "IMG_Init");
        return;
    }
    this->window = SDL_CreateWindow("DSA", 100, 100, 800, 800, SDL_WINDOW_SHOWN);
    if (this->window == nullptr){
        logSDLError(std::cout, "CreateWindow");
        return;
    }
    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (this->renderer == nullptr){
        logSDLError(std::cout, "CreateRenderer");
        return;
    }
}

SDLSetup::~SDLSetup(){
    cleanup();
}

SDLSetup* SDLSetup::getInstance(){
    mutex.lock();
    if(instance == nullptr){
        instance = new SDLSetup();
    }
    mutex.unlock();
    return instance;
}

SDL_Texture* SDLSetup::loadTexture(const std::string &file){
    SDL_Texture *texture = NULL;
    SDL_Surface *surface = IMG_Load(file.c_str());
    if(surface){
        texture = SDL_CreateTextureFromSurface(this->renderer, surface);
        surface->pixels = NULL;
        SDL_FreeSurface(surface);
    }

    if(!texture) {
        logSDLError(std::cout, "LoadTexture: ");
    }
    return texture;
}

void SDLSetup::renderTexture(SDL_Texture* texture, SDL_Rect rect, SDL_Rect *clip){
    SDL_RenderCopy(this->renderer, texture, clip, &rect);
}

void SDLSetup::renderTexture(SDL_Texture* texture, int x, int y, SDL_Rect *clip){
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    if(clip != nullptr){
        rect.w = clip->w;
        rect.h = clip->h;
    } else {
        SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
    }
    renderTexture(texture, rect, clip);
}

void SDLSetup::logSDLError(std::ostream &os, const std::string &msg){
    os << msg << " error: " << SDL_GetError() << std::endl;
}

SDL_Window* SDLSetup::getWindow(){
    return this->window;
}

SDL_Renderer* SDLSetup::getRenderer(){
    return this->renderer;
}

void SDLSetup::cleanup(){
    SDL_DestroyWindow(this->window);
    SDL_DestroyRenderer(this->renderer);
    IMG_Quit();
    SDL_Quit();
}