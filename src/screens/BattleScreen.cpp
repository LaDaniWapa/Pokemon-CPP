#include "screens/BattleScreen.hpp"

void BattleScreen::Load() {
    font = LoadFontEx("assets/fonts/pokemon-b-w.ttf", 60, nullptr, 0);
    fontB = LoadFontEx("assets/fonts/pkmndpb.ttf", 30, nullptr, 0);

    background = LoadTexture("assets/BattleBacks/field_bg.png");
    message = LoadTexture("assets/BattleBacks/field_message.png");

    pokemon = new Battler(pokemonPokedexNumber, 100, pokemonShiny, false, font, fontB);
    pokemonFoe = new Battler(pokemonFoePokedexNumber, 100, pokemonFoeShiny, true, font, fontB);
}

void BattleScreen::Unload() {
    UnloadTexture(background);
    UnloadTexture(message);
    UnloadFont(font);
    UnloadFont(fontB);
}

void BattleScreen::Update() {
    if (IsKeyPressed(KEY_ENTER)) {
        screenManager->ChangeScreen("Title");
    }
}

void BattleScreen::Draw() {
    DrawTexture(background, 0, 0, WHITE);
    pokemon->draw();
    pokemonFoe->draw();
    DrawTexture(message, 0, 288, WHITE);
}

void BattleScreen::setPokemon(int pokedexNumber, bool shiny) {
    pokemonPokedexNumber = pokedexNumber;
    pokemonShiny = shiny;
}

void BattleScreen::setPokemonFoe(int pokedexNumber, bool shiny) {
    pokemonFoePokedexNumber = pokedexNumber;
    pokemonFoeShiny = shiny;
}