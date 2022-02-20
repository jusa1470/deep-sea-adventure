#include <helloWorldSDL.h>
#include <stdio.h>
#include <unistd.h>

// Starts up SDL and creates window
bool init() {

}

// Loads media
bool loadMedia() {

}

// Frees media and shuts down SDL
void close() {
    
}

int main(int argc, char* args[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    // Create the window we'll be rendering to
    SDL_Window* window = SDL_CreateWindow("SDL Tutorial", 
                                          SDL_WINDOWPOS_CENTERED, 
                                          SDL_WINDOWPOS_CENTERED,
                                          SCREEN_WIDTH,
                                          SCREEN_HEIGHT,
                                          SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    // The surface contained by the window
    SDL_Surface* screenSurface = SDL_GetWindowSurface(window);  
    // Fill the surface white
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
    // Update the surface
    SDL_UpdateWindowSurface(window);
    // Wait two seconds
    // SDL_Delay(20000);

    bool is_running = true;
    SDL_Event event;
    while (is_running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT){
                is_running = false;
            }
        }
        SDL_Delay(16);
    }

    // Destroy window
    SDL_DestroyWindow(window);
    // Quit SDL subsystems
    SDL_Quit();

    return 0;
}