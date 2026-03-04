#include "screens/BattlersChooserScreen.hpp"

#include "screens/BattlerListScreen.hpp"
#include "screens/BattleScreen.hpp"

void BattlersChooserScreen::Load() {
    // Cargar fuente necesaria
    font = LoadFontEx("assets/fonts/pokemon-b-w.ttf", 60, nullptr, 0);

    // Cargar shader
    outlineShader = LoadShader(nullptr, "assets/shaders/outline.fs");

    // Get shader variables locations
    int outlineSizeLoc = GetShaderLocation(outlineShader, "outlineSize");
    int outlineColorLoc = GetShaderLocation(outlineShader, "outlineColor");
    int textureSizeLoc = GetShaderLocation(outlineShader, "textureSize");

    // Set shaders variables
    float outlineSize = 2.f;
    float outlineColor[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    float textureSize[2] = {192.f, 192.f};

    // Send shader variables values
    SetShaderValue(outlineShader, outlineSizeLoc, &outlineSize, SHADER_UNIFORM_FLOAT);
    SetShaderValue(outlineShader, outlineColorLoc, &outlineColor, SHADER_UNIFORM_VEC4);
    SetShaderValue(outlineShader, textureSizeLoc, &textureSize, SHADER_ATTRIB_VEC2);

    // Cargar texturas de pokemons y tipos
    typesTexture = LoadTexture("assets/types.png");
    pokemonTexture = getPokemonTexture(pkxn, pokemonShiny, false);
    pokemonFoeTexture = getPokemonTexture(pkxnF, pokemonFoeShiny, false);

    // Cargar datos de los pokemons generados aleatoriamente
    readPokemonFromFile(pkxn, pokemon);
    readPokemonFromFile(pkxnF, pokemonFoe);

    // Actualizar textura de los tipos
    type1 = Rectangle{0, ((float)pokemon.type1 - 1) * 28, 64, 28};
    type2 = Rectangle{0, ((float)pokemon.type2 - 1) * 28, 64, 28};
    type1Foe = Rectangle{0, ((float)pokemonFoe.type1 - 1) * 28, 64, 28};
    type2Foe = Rectangle{0, ((float)pokemonFoe.type2 - 1) * 28, 64, 28};

    // Cargar estrellita shiny
    shinyStar = LoadTexture("assets/shiny_star.png");
}

void BattlersChooserScreen::Unload() {
    UnloadTexture(pokemonTexture);
    UnloadTexture(pokemonFoeTexture);
    UnloadTexture(typesTexture);
    UnloadFont(font);
}

void BattlersChooserScreen::Update() {
    // Actualizar la posicion del raton
    mousePoint = GetMousePosition();
    // Actualizar los shaders
    pokemonShader = false;
    pokemonFoeShader = false;
    hoverButton = false;

    // Mirar si se hace clic en el boton
    if (CheckCollisionPointRec(mousePoint, Rectangle{322, 618, 400, 100})) {
        hoverButton = true;

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            BattleScreen* battleScreen = dynamic_cast<BattleScreen*>(screenManager->getScreen("Battle"));

            if (battleScreen) {
                battleScreen->setPokemon(pokemon.ID, pokemonShiny);
                battleScreen->setPokemonFoe(pokemonFoe.ID, pokemonFoeShiny);
                screenManager->ChangeScreen("Battle");
            }
        }
    }

    // Mirar si se hace clic en el pokemon
    // La funcion usa la resolucion final de la pantalla (x2)
    if (CheckCollisionPointCircle(mousePoint, Vector2{256, 282}, 192)) {
        pokemonShader = true;

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            BattlersListScreen* battlersListscreen =
                dynamic_cast<BattlersListScreen*>(screenManager->getScreen("BattlersList"));

            if (battlersListscreen) {
                battlersListscreen->setOldPokedexNumber(pokemonFoe.ID);
                battlersListscreen->setIsFoe(false);
                screenManager->ChangeScreen("BattlersList");
            }
        }

        if (IsKeyReleased(KEY_S)) {
            toggleShiny(false);
        }
    }

    // Mirar si se hace clic en el pokemon
    // La funcion usa la resolucion final de la pantalla (x2)
    if (CheckCollisionPointCircle(mousePoint, Vector2{768, 282}, 192)) {
        pokemonFoeShader = true;

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            BattlersListScreen* battlersListscreen =
                dynamic_cast<BattlersListScreen*>(screenManager->getScreen("BattlersList"));

            if (battlersListscreen != nullptr) {
                battlersListscreen->setOldPokedexNumber(pokemon.ID);
                battlersListscreen->setIsFoe(true);
                screenManager->ChangeScreen("BattlersList");
            }
        }

        if (IsKeyReleased(KEY_S)) {
            toggleShiny(true);
        }
    }
}

void BattlersChooserScreen::Draw() {
    // Imprimir los nombres de los pokemons
    DrawText(pokemon.name, 128 - (MeasureText(pokemon.name, 20) / 2), 15, 20, RED);
    DrawText(pokemonFoe.name, 385 - (MeasureText(pokemonFoe.name, 20) / 2), 15, 20, RED);

    // Dibujar background de los pokemons
    DrawCircleGradient(128, 141, 96, GRAY, DARKGRAY);
    DrawCircleGradient(384, 141, 96, GRAY, DARKGRAY);

    // Dibujar pokémon con o sin outlineShader
    if (pokemonShader) {
        BeginShaderMode(outlineShader);
        DrawTexture(pokemonTexture, 32, 45, WHITE);
        EndShaderMode();
    } else
        DrawTexture(pokemonTexture, 32, 45, WHITE);

    if (pokemonFoeShader) {
        BeginShaderMode(outlineShader);
        DrawTexture(pokemonFoeTexture, 288, 45, WHITE);
        EndShaderMode();
    } else
        DrawTexture(pokemonFoeTexture, 288, 45, WHITE);

    // Dibujar estrella shiny
    if (pokemonShiny) DrawTexture(shinyStar, 184, 197, WHITE);
    if (pokemonFoeShiny) DrawTexture(shinyStar, 440, 197, WHITE);

    // Dibujar tipos de los pokemons
    if (pokemon.type2) {
        DrawTextureRec(typesTexture, type1, Vector2{55, 232}, WHITE);
        DrawTextureRec(typesTexture, type2, Vector2{130, 232}, WHITE);
    } else
        DrawTextureRec(typesTexture, type1, Vector2{92.5f, 232}, WHITE);

    if (pokemonFoe.type2) {
        DrawTextureRec(typesTexture, type1Foe, Vector2{315, 232}, WHITE);
        DrawTextureRec(typesTexture, type2Foe, Vector2{390, 232}, WHITE);
    } else
        DrawTextureRec(typesTexture, type1Foe, Vector2{352.5f, 232}, WHITE);

    // Dibujar boton para empezar
    if (hoverButton) {
        DrawRectangle(161, 309, 200, 50, Color{70, 70, 70, 255});
        DrawText("START BATTLE", 178, 325, 20, Color{160, 0, 0, 255});
    } else {
        DrawRectangle(161, 309, 200, 50, Color{40, 40, 40, 255});
        DrawText("START BATTLE", 178, 325, 20, Color{230, 41, 55, 255});
    }
}

void BattlersChooserScreen::setPokemon(int pokedexnumber) {
    pkxn = pokedexnumber;
}

void BattlersChooserScreen::setFoePokemon(int pokedexnumber) {
    pkxnF = pokedexnumber;
}

void BattlersChooserScreen::toggleShiny(const bool foe) {
    if (foe) {
        pokemonFoeShiny = !pokemonFoeShiny;
        pokemonFoeTexture = getPokemonTexture(pkxnF, pokemonFoeShiny, false);
    } else {
        pokemonShiny = !pokemonShiny;
        pokemonTexture = getPokemonTexture(pkxn, pokemonShiny, false);
    }
}