#ifndef BATTLERCHOOSERSCREEN_HPP
#define BATTLERCHOOSERSCREEN_HPP

#include <raylib.h>

#include "Screen.hpp"
#include "Utils.hpp"

class BattlersChooserScreen : public Screen {
    Texture2D pokemonTexture{}, pokemonFoeTexture{};
    Texture2D typesTexture{};
    Texture2D shinyStar{};
    Font font{};

    Pkm pokemon{}, pokemonFoe{};
    Shader outlineShader{};
    Rectangle type1{}, type2{}, type1Foe{}, type2Foe{};
    // Pokedex numbers
    int pkxn{}, pkxnF{};
    Vector2 mousePoint{.0f, .0f};
    // Use outlineShader
    bool usePokemonShader = false, useFoePokemonShader = false, hoverButton = false;
    // Toggle shiny
    bool isPokemonShiny = false, isFoePokemonShiny = false;

   public:
    void Load() override;
    void Unload() override;
    void Update() override;
    void Draw() override;

    void setPokemon(int pokedexnumber);
    void setFoePokemon(int pokedexnumber);

    void toggleShiny(bool foe);
};

#endif  // BATTLERCHOOSERSCREEN_HPP