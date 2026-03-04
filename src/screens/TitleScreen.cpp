#include "screens/TitleScreen.hpp"
#include "screens/BattlersChooserScreen.hpp"

void TitleScreen::Load() {
    titleAnimatedImage = LoadImageAnim("assets/title.gif", &frames);
    background = LoadTextureFromImage(titleAnimatedImage);
}

void TitleScreen::Unload() { UnloadTexture(background); }

void TitleScreen::Update() {
    if (IsKeyPressed(KEY_ENTER)) {
        BattlersChooserScreen* battlerChooserScreen =
            dynamic_cast<BattlersChooserScreen*>(screenManager->getScreen("BattlersChooser"));

        if (battlerChooserScreen) {
            // Generar pokemons random
            battlerChooserScreen->setPokemon(randomNumber(494, 649));
            battlerChooserScreen->setFoePokemon(randomNumber(494, 649));
            screenManager->ChangeScreen("BattlersChooser");
        }
    }

    frameCounter++;
    if (frameCounter > frameDelay) {
        currentFrame++;
        if (currentFrame >= frames) currentFrame = 0;

        nextFrameDataOffset = titleAnimatedImage.width * titleAnimatedImage.height * 4 * currentFrame;

        UpdateTexture(background, static_cast<unsigned char*>(titleAnimatedImage.data) + nextFrameDataOffset);

        frameCounter = 0;
    }
}

void TitleScreen::Draw() {
    ClearBackground(BLACK);
    DrawTexture(background, 0, 0, WHITE);
}
