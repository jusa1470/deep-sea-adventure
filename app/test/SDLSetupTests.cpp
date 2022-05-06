#include <gtest/gtest.h>
#include <SDLSetup.h>

class SDLSetupsTests : public ::testing::Test {
    protected:
        SDLSetup *sdlSetup;
        void SetUp() { 
            sdlSetup = SDLSetup::getInstance();
        }
        void TearDown() {
        }
};

TEST_F(SDLSetupsTests, loadTextureTest) {
    std::string testPath = "../app/resources/marker.png";
    SDL_Texture *tex = sdlSetup->loadTexture(testPath);
    EXPECT_NE(nullptr, tex);
    SDL_DestroyTexture(tex);
}