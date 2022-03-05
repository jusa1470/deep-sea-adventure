#include <helloWorldSDL.h>
#include <stdio.h>
#include <unistd.h>
#include <string>

// Starts up SDL and creates window
bool init() {
    // Init flag
    bool success = true;

    // Init SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    else {
        // Create window
        gWindow = SDL_CreateWindow("SDL Tutorial", 
                                    SDL_WINDOWPOS_CENTERED, 
                                    SDL_WINDOWPOS_CENTERED,
                                    SCREEN_WIDTH,
                                    SCREEN_HEIGHT,
                                    SDL_WINDOW_SHOWN);
        if (gWindow == nullptr) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        }
        else {
            // Create renderer for window
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if (gRenderer == nullptr) {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else {
                // Initialize renderer color
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                // Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags)) {
                    printf("SDL_image could nto initialize! SDL_image Error: %s\n", IMG_GetError());
                    success = false;
                }
            }
        }
    }
    return success;
}

//Loads individual image
SDL_Surface * loadSurface( std::string path ) {
    // Load image at specified path
    SDL_Surface * loadedSurface = SDL_LoadBMP(path.c_str());

    if (loadedSurface == nullptr) {
        printf("Unable to laod image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
    }

    return loadedSurface;
}

// Loads individual image as texture
SDL_Texture * loadTexture(std::string path) {
    // The final texture
    SDL_Texture * newTexture = nullptr;

    // Load image at specified path
    SDL_Surface * loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else {
        // Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if (newTexture == nullptr) {
            printf("unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }

        // Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}

// Loads media
bool loadMedia() {
    // Loading success flag
    bool success = true;

    //Load sprite sheet texture
    if( !gSpriteSheetTexture.loadFromFile( "../resources/dots.png" ) )
    {
        printf( "Failed to load sprite sheet texture!\n" );
        success = false;
    }
    else
    {
        //Set top left sprite
        gSpriteClips[ 0 ].x =   0;
        gSpriteClips[ 0 ].y =   0;
        gSpriteClips[ 0 ].w = 100;
        gSpriteClips[ 0 ].h = 100;

        //Set top right sprite
        gSpriteClips[ 1 ].x = 100;
        gSpriteClips[ 1 ].y =   0;
        gSpriteClips[ 1 ].w = 100;
        gSpriteClips[ 1 ].h = 100;
        
        //Set bottom left sprite
        gSpriteClips[ 2 ].x =   0;
        gSpriteClips[ 2 ].y = 100;
        gSpriteClips[ 2 ].w = 100;
        gSpriteClips[ 2 ].h = 100;

        //Set bottom right sprite
        gSpriteClips[ 3 ].x = 100;
        gSpriteClips[ 3 ].y = 100;
        gSpriteClips[ 3 ].w = 100;
        gSpriteClips[ 3 ].h = 100;
    }


    // //Load PNG texture
    // gTexture = loadTexture( "../resources/texture.png" );
    // if (gTexture == nullptr) {
    //     printf( "Failed to load texture image!\n" );
    //     success = false;
    // }

    // // Load default surface
    // gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("../resources/press.bmp");
    // if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == nullptr) {
    //     printf("Unable to load image %s! SDL Error: %s\n", "press.bmp", SDL_GetError());
    //     success = false;
    // }

    // // Load up surface
    // gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("../resources/up.bmp");
    // if (gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] == nullptr) {
    //     printf("Unable to load image %s! SDL Error: %s\n", "up.bmp", SDL_GetError());
    //     success = false;
    // }

    // // Load down surface
    // gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("../resources/down.bmp");
    // if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == nullptr) {
    //     printf("Unable to load image %s! SDL Error: %s\n", "down.bmp", SDL_GetError());
    //     success = false;
    // }
    // // Load left surface
    // gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("../resources/left.bmp");
    // if (gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == nullptr) {
    //     printf("Unable to load image %s! SDL Error: %s\n", "left.bmp", SDL_GetError());
    //     success = false;
    // }
    // // Load right surface
    // gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("../resources/right.bmp");
    // if (gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == nullptr) {
    //     printf("Unable to load image %s! SDL Error: %s\n", "right.bmp", SDL_GetError());
    //     success = false;
    // }
    return success;
}

// Frees media and shuts down SDL
void close() {
    // Free loaded image
    SDL_DestroyTexture(gTexture);
    gTexture = nullptr;

    // Deallocate surface
    // SDL_FreeSurface(gHelloWorld);
    // gHelloWorld = nullptr;

    // Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;
    gRenderer = nullptr;

    // Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* args[]) {
    // Start up SDL and create window
    if (!init()) {
        printf("Failed to initialize!\n");
        return -1;
    }

    // Load media
    if (!loadMedia()) {
        printf("Failed to load media!\n");
    }

    bool is_running = true;
    SDL_Event event;
    // Set default current surface
    gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];

    while (is_running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT){
                is_running = false;
            }
            // User presses a key
            // else if (event.type == SDL_KEYDOWN) {
            //     // Select surfaces based on key press
            //     switch (event.key.keysym.sym) {
            //         case SDLK_UP:
            //             gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
            //             break;
            //         case SDLK_DOWN:
            //             gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
            //             break;
            //         case SDLK_LEFT:
            //             gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
            //             break;
            //         case SDLK_RIGHT:
            //             gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
            //             break;
            //         default:
            //             gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
            //             break;
            //     }
            // }
        }

        //Clear screen
        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( gRenderer );

        //Render top left sprite
        gSpriteSheetTexture.render( 0, 0, &gSpriteClips[ 0 ] );

        //Render top right sprite
        gSpriteSheetTexture.render( SCREEN_WIDTH - gSpriteClips[ 1 ].w, 0, &gSpriteClips[ 1 ] );

        //Render bottom left sprite
        gSpriteSheetTexture.render( 0, SCREEN_HEIGHT - gSpriteClips[ 2 ].h, &gSpriteClips[ 2 ] );

        //Render bottom right sprite
        gSpriteSheetTexture.render( SCREEN_WIDTH - gSpriteClips[ 3 ].w, SCREEN_HEIGHT - gSpriteClips[ 3 ].h, &gSpriteClips[ 3 ] );

        //Update screen
        SDL_RenderPresent( gRenderer );

        // // Clear screen
        // SDL_RenderClear(gRenderer);

        // // Render texture to screen
        // SDL_RenderCopy(gRenderer, gTexture, nullptr, nullptr);

        // // Update screen
        // SDL_RenderPresent(gRenderer);

        // // Apply the image
        // SDL_BlitSurface(gCurrentSurface, nullptr, gScreenSurface, nullptr);

        // // Update the surface
        // SDL_UpdateWindowSurface(gWindow);

        SDL_Delay(64);
    }

    // Free resources and close SDL
    close();

    return 0;
}
