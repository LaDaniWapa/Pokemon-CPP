#include "BattlerListScreen.hpp"
#include "BattlersChooserScreen.hpp"
#include "ScreenManager.hpp"

void BattlersListScreen::Load() {
    box = 0;
    loadBoxTextures();
    boxBg = LoadTexture("assets/UI/boxbg.png");
}

void BattlersListScreen::Unload() {
    for (Texture2D texture : pokemonTextures) {
        UnloadTexture(texture);
    }
    UnloadTexture(boxBg);
}

void BattlersListScreen::Update() {
    mousePoint = GetMousePosition();

    // Check if mouse is avobe a pokemon
    if (CheckCollisionPointRec(mousePoint, Rectangle{126, 90, 768, 640})) {
        frame_counter++;

        // Update frame for animation
        if (frame_counter >= 15) {
            selectedPokemonTextureRect.x = 0;
        }

        if (frame_counter >= 30) {
            selectedPokemonTextureRect.x = 64;
            frame_counter = 0;
        }

        // mousePoint / 2 because of scaling
        x = (int)(mousePoint.x / 2 - 63) / 64;
        y = (int)(mousePoint.y / 2 - 45) / 64;

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            pokedexNumber = y * 6 + x + 494 + box * 30;

            // Check if valid pokemon
            if (pokedexNumber <= 649) {
                // Load next screen
                BattlersChooserScreen *battleChooserScreen =
                    dynamic_cast<BattlersChooserScreen *>(screenManager->getScreen("BattlersChooser"));

                // Check if screen was loaded
                if (battleChooserScreen) {
                    // Ste pokemon IDs
                    if (isFoe) {
                        battleChooserScreen->setPokemon(oldPokedexNumber);
                        battleChooserScreen->setFoePokemon(pokedexNumber);
                    } else {
                        battleChooserScreen->setPokemon(pokedexNumber);
                        battleChooserScreen->setFoePokemon(oldPokedexNumber);
                    }
                    screenManager->ChangeScreen("BattlersChooser");
                }
            }
        }
    }

    if (IsKeyPressed(KEY_RIGHT)) {
        box++;
        if (box > 5) box = 0;
        loadBoxTextures();
    }

    if (IsKeyPressed(KEY_LEFT)) {
        box--;
        if (box < 0) box = 5;
        loadBoxTextures();
    }
}

void BattlersListScreen::Draw() {
    DrawTextureEx(boxBg, Vector2{63, 45}, .0f, 2.f, WHITE);

    DrawText(TextFormat("Box %i", box), 256 - MeasureText("Box 0", 20) / 2, 10, 20, WHITE);

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 6; j++) {
            if (i == y && j == x)
                DrawTextureRec(pokemonTextures[i * 6 + j], selectedPokemonTextureRect, Vector2{j * 64.f + 63.5f, i * 64.f + 45.f}, WHITE);
            else
                DrawTextureRec(pokemonTextures[i * 6 + j], textureRect, Vector2{j * 64.f + 63.5f, i * 64.f + 45.f}, WHITE);
        }
    }

    // DrawRectangleLines(63, 45, 384, 320, BLUE);
}

void BattlersListScreen::setIsFoe(bool foe) {
    isFoe = foe;
}

void BattlersListScreen::loadBoxTextures() {
    for (int i = 0; i < 30; i++) {
        pokemonTextures[i] = LoadTexture(TextFormat("assets/pokemonIcons/icon%d.png", i + 494 + box * 30));
    }
}

void BattlersListScreen::setOldPokedexNumber(int pokedeNumber) {
    oldPokedexNumber = pokedeNumber;
}