#include <iostream>
#include "../include/cleanup.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#define SDL_MAIN_HANDLED
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 1000
#define TILE_SIZE 40

void logSDLError(std::ostream &os, const std::string &msg){
    os << msg << " error: " << SDL_GetError() << std::endl;
}

SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren){
    SDL_Texture *texture = NULL;
    SDL_Surface *surface = IMG_Load(file.c_str());
    if (surface){
        texture = SDL_CreateTextureFromSurface(ren, surface);
        SDL_FreeSurface(surface);
    }
    return texture;
}

// SDL_Texture* renderText(const std::string &message, const std::string &fontFile,
//                         SDL_Color color, int fontSize, SDL_Renderer *ren){
//     TTF_Font *font = TTF_OpenFont(fontFile.c_str(), fontSize);
//     if (font == nullptr){
//         logSDLError(std::cout, "TTF_OpenFont");
//         return nullptr;
//     }
//     SDL_Surface *surf = TTF_RenderText_Blended(font, message.c_str(), color);
//     if (surf == nullptr){
//         TTF_CloseFont(font);
//         logSDLError(std::cout, "TTF_RenderText_Blended");
//         return nullptr;
//     }
//     SDL_Texture *texture = SDL_CreateTextureFromSurface(ren, surf);
//     if (texture == nullptr){
//         logSDLError(std::cout, "CreateTextureFromSurface");
//     }
//     SDL_FreeSurface(surf);
//     TTF_CloseFont(font);
//     return texture;
// }

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h){
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    dst.w = w;
    dst.h = h;
    SDL_RenderCopy(ren, tex, NULL, &dst);
}

// void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y){
//     int w, h;
//     SDL_QueryTexture(tex, NULL, NULL, &w, &h);
//     renderTexture(tex, ren, x, y, w, h);
// }

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, SDL_Rect dst, SDL_Rect *clip = nullptr){
    SDL_RenderCopy(ren, tex, clip, &dst);
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, SDL_Rect *clip = nullptr){
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    if(clip != nullptr){
        dst.w = clip->w;
        dst.h = clip->h;
    } else {
        SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
    }
    renderTexture(tex, ren, dst, clip);
}

int main(int argc, char* argv[]){
    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        logSDLError(std::cout, "SDL_Init");
        return 1;
    }
    if((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG){
        logSDLError(std::cout, "IMG_Init");
        SDL_Quit();
        return 1;
    }
    if(TTF_Init() != 0){
        logSDLError(std::cout, "TTF_Iinit");
        SDL_Quit();
        return 1;
    }
    SDL_Window *win = SDL_CreateWindow("Hello World", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (win == nullptr){
        logSDLError(std::cout, "CreateWindow");
        SDL_Quit();
        return 1;
    }
    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == nullptr){
        logSDLError(std::cout, "CreateRenderer");
        cleanup(win);
        SDL_Quit();
        return 1;
    }

    const std::string spritesPath = "../resources/Sprites_Scaled.png";
    SDL_Texture *sprites = loadTexture(spritesPath, ren);
    if(sprites == nullptr){
        cleanup(sprites, ren, win);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    const std::string playersPath = "../resources/player_sprites.png";
    SDL_Texture *players = loadTexture(playersPath, ren);
    if(players == nullptr){
        cleanup(sprites, players, ren, win);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    int iW = 64, iH = 64;
    SDL_Rect place_clips[4];
    for(int i = 0; i < 4; ++i){
        place_clips[i].x = i / 2 * iW;
        place_clips[i].y = i % 2 * iH;
        place_clips[i].w = iW;
        place_clips[i].h = iH;
    }
    
    int pW = 64, pH = 64;
    SDL_Rect player_clips[6];
    for(int i = 0; i < 6; ++i){
        player_clips[i].x = i / 2 * pW;
        player_clips[i].y = i % 2 * pH;
        player_clips[i].w = pW;
        player_clips[i].h = pH;
    }

    SDL_Event e;
    bool quit = false;
    SDL_SetRenderDrawColor(ren, 137, 207, 240, 255);
    int map[6][5] = {{0, 1, 0, 0, 0}, 
                     {0, 1, 0, 0, 0},
                     {0, 1, 2, 2, 0},
                     {0, 2, 2, 2, 0},
                     {0, 3, 0, 0, 0},
                     {0, 3, 4, 4, 4}};
    while (!quit){
        SDL_RenderClear(ren);
        int x = 0; 
        int y = 0;
        for(int i = 0; i < 6; i++){
            for(int j = 0; j < 5; j++){
                std::cout<< x << " , " << y << std::endl;
                if (map[i][j] == 1){
                    renderTexture(sprites, ren, x, y, &place_clips[0]);
                    renderTexture(players, ren, x, y, &player_clips[0]);
                } else if (map[i][j] == 2){
                    renderTexture(sprites, ren, x, y, &place_clips[2]);
                } else if (map[i][j] == 3){
                    renderTexture(sprites, ren, x, y, &place_clips[1]);
                    renderTexture(players, ren, x, y, &player_clips[3]);
                } else if (map[i][j] == 4){
                    renderTexture(sprites, ren, x, y, &place_clips[3]);
                }
                x = (x + iW) % SCREEN_WIDTH;
            }
            x = 0;
            y = (y + iH) % SCREEN_HEIGHT;
        }
        SDL_RenderPresent(ren);
        while(SDL_PollEvent(&e)){
            if (e.type == SDL_QUIT)
                quit = true;
        }
        // quit = true;
    }
    cleanup(sprites, players, ren, win);
    IMG_Quit();
    SDL_Quit();

}
