#include <lTexture.h>
// #include <helloWorldSDL.h>

void LTexture::render(SDL_Renderer * gRenderer, int x, int y, SDL_Rect * clip) {
    // Set rendering space and render to screen
    SDL_Rect renderQuad = {x, y, mWidth, mHeight};

    // Set clip rendering dimensions
    if (clip != nullptr) {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    // Render to screen
    SDL_RenderCopy(gRenderer, mTexture, clip, &renderQuad);
}