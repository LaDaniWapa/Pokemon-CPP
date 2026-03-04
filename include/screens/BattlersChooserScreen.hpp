#ifndef BATTLERCHOOSERSCREEN_HPP
#define BATTLERCHOOSERSCREEN_HPP

#include <raylib.h>

#include "screenManager.hpp"
#include "utils.hpp"

class BattlersChooserScreen : public Screen {
   private:
    // Texturas de los pokemons
    Texture2D pokemonTexture{}, pokemonFoeTexture{};
    // Textura de los tipos
    Texture2D typesTexture{};
    // Texture de estrellita shiny
    Texture2D shinyStar{};
    // Fuente
    Font font{};
    // Estructura de los pokemons
    Pkm pokemon{}, pokemonFoe{};
    // Shadder
    Shader outlineShader{};
    // Rectangles para recortar la textura de tipos
    Rectangle type1{}, type2{}, type1Foe{}, type2Foe{};
    // Numeros de la pokedex
    int pkxn{}, pkxnF{};
    // Posicion del raton
    Vector2 mousePoint{.0f, .0f};
    // Usar outlineShader o no
    bool pokemonShader = false, pokemonFoeShader = false, hoverButton = false;
    // Cambiar pokemon a shiny
    bool pokemonShiny = false, pokemonFoeShiny = false;

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