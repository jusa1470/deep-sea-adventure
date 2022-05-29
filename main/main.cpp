#include <iostream>
#include <string>
#include <GameMechanics.h>
#include <SDLSetup.h>
#include <SDL.h>
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

int main(){
    GameMechanics *gameMechanics = new GameMechanics();
    SDLSetup *sdl = SDLSetup::getInstance();
    SDL_SetRenderDrawColor(sdl->getRenderer(), 40, 175, 176, 255);
    SDL_Texture *sub_texture = sdl->loadTexture("../app/resources/submarine.png");
    printf("AFTER SUB\n");
    SDL_Texture *tile_texture = sdl->loadTexture("../app/resources/tilesScaled.png");
    printf("MOVE TO DIE TEXTURES\n");
    SDL_Texture *die_one = sdl->loadTexture("../app/resources/dieOne.png");
    printf("AFTER ONE\n");
    SDL_Texture *die_two = sdl->loadTexture("../app/resources/dieTwo.png");
    SDL_Texture *die_three = sdl->loadTexture("../app/resources/dieThree.png");
    printf("TEXTURES LOADED\n");

    int iW = 64, iH = 64;
    SDL_Rect tile_clips[4];
    for(int i = 0; i < 4; ++i){
        tile_clips[i].x = i / 2 * iW;
        tile_clips[i].y = i % 2 * iH;
        tile_clips[i].w = iW;
        tile_clips[i].h = iH;
    }

    int map[8][7] = {{0, 0, 0, 1, 1, 1, 1}, 
                     {0, 0, 0, 0, 0, 0, 1},
                     {2, 2, 2, 2, 1, 1, 1}, 
                     {2, 0, 0, 0, 0, 0, 0},
                     {2, 2, 2, 3, 3, 3, 3}, 
                     {0, 0, 0, 0, 0, 0, 3},
                     {4, 4, 4, 4, 3, 3, 3},
                     {4, 4, 4, 4, 0, 0, 0}};

    SDL_Rect roll_btn;
    roll_btn.x = 500;
    roll_btn.y = 10;
    roll_btn.w = 200;
    roll_btn.h = 100;

    bool quit = false;                
    while(!quit){
        SDL_RenderClear(sdl->getRenderer());
        SDL_Event e;
        while(SDL_PollEvent(&e)){
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_MOUSEBUTTONDOWN){
                int m_x = e.motion.x;
                int m_y = e.motion.y;
                if(m_x > roll_btn.x && m_x < (roll_btn.x + roll_btn.w) && m_y > roll_btn.y && m_y < (roll_btn.y + roll_btn.h)) {
                    printf("CLICKED IN BOX\n");
                } else {
                    printf("clicked in...NOT in box..\n");
                }
            } else if (e.type == SDL_MOUSEBUTTONUP){
                int m_x = e.motion.x;
                int m_y = e.motion.y;
                if(m_x > roll_btn.x && m_x < (roll_btn.x + roll_btn.w) && m_y > roll_btn.y && m_y < (roll_btn.y + roll_btn.h)) {
                    printf("CLICKED OUT OF BOX\n");
                } else {
                    printf("clicked out...NOT in box..\n");
                }
            }
        }
        sdl->renderTexture(sub_texture, 0, 0, nullptr);
        int x = 32, y = 200;
        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 7; j++){
                if (map[i][j] == 1){
                    sdl->renderTexture(tile_texture, x, y, &tile_clips[0]);
                } else if (map[i][j] == 2){
                    sdl->renderTexture(tile_texture, x, y, &tile_clips[1]);
                } else if (map[i][j] == 3){
                    sdl->renderTexture(tile_texture, x, y, &tile_clips[2]);
                } else if (map[i][j] == 4){
                    sdl->renderTexture(tile_texture, x, y, &tile_clips[4]);
                }
                x = (x + iW) % SCREEN_WIDTH;
            }
            x = 64;
            y = (y + iH) % SCREEN_HEIGHT;
        }
        sdl->renderTexture(die_one, 750, 10, NULL);
        sdl->renderTexture(die_two, 750, 48, NULL);
        sdl->renderTexture(die_three, 750, 86, NULL);
        SDL_SetRenderDrawColor(sdl->getRenderer(), 65, 90, 119, 255);
        SDL_RenderFillRect(sdl->getRenderer(), &roll_btn);
        SDL_RenderPresent(sdl->getRenderer());
    }
    SDL_DestroyTexture(sub_texture);
    SDL_DestroyTexture(tile_texture);
    SDL_DestroyTexture(die_one);
    SDL_DestroyTexture(die_two);
    SDL_DestroyTexture(die_three);
    gameMechanics->~GameMechanics();
    sdl->~SDLSetup();
}