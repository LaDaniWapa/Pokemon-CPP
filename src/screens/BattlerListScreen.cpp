#include "screens/BattlerListScreen.hpp"
#include "screens/BattlersChooserScreen.hpp"

void BattlersListScreen::Load() {
    box = 0;
    loadBoxTextures();
    boxBg = LoadTexture("assets/boxbg.png");
}

void BattlersListScreen::Unload() {
    // Unload todas las texturas
    for (Texture2D texture : pokemonTextures) {
        UnloadTexture(texture);
    }
    UnloadTexture(boxBg);
}

void BattlersListScreen::Update() {
    // Actualizar la posicion del raton
    mousePoint = GetMousePosition();

    // Si el mouse esta dentro del cuadrado imaginario de los pokemons (este multiplicado x2 por el escalado)
    if (CheckCollisionPointRec(mousePoint, Rectangle{126, 90, 768, 640})) {
        // Contar frames
        framecounter++;

        // Cambiar rect 2 veces por segundo
        if (framecounter >= 15) {
            selectedPokemonTextureRect.x = 0;
        }

        if (framecounter >= 30) {
            selectedPokemonTextureRect.x = 64;
            framecounter = 0;
        }

        // Dividir mousePoint / 2 por el escalado
        x = (int)(mousePoint.x / 2 - 63) / 64;
        y = (int)(mousePoint.y / 2 - 45) / 64;

        // Si se da click
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {

            pokedexNumber = y * 6 + x + 494 + box * 30;

            // Si el pokemon es valido
            if (pokedexNumber <= 649) {
                // Cargar pantalla de eleccion de pokemons
                BattlersChooserScreen *battleChooserScreen =
                    dynamic_cast<BattlersChooserScreen *>(screenManager->getScreen("BattlersChooser"));

                // Si se ha cargado bien la pantalla
                if (battleChooserScreen) {
                    // Poner el ID de los pokemons
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