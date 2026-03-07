#ifndef BATTLERLISTSCREEN_HPP
#define BATTLERLISTSCREEN_HPP

#include <raylib.h>

#include "Screen.hpp"

class BattlersListScreen : public Screen {
    // Rectangle for first texture frame
    Rectangle textureRect{0, 0, 64, 64};
    // Frame for animated texture
    Rectangle selectedPokemonTextureRect{0, 0, 64, 64};
    int frame_counter = 0;
    Texture2D pokemonTextures[30]{};
    Texture2D boxBg{};
    Vector2 mousePoint{};
    // Used to get clicked pokemon
    int x{}, y{}, pokedexNumber{};
    // Pokemon that ramins the same
    int oldPokedexNumber{};
    // Pokemon box index
    int box{};
    // Is it the foe pokemon that we are selecting
    bool isFoe{};

    void loadBoxTextures();

   public:
    void Load() override;
    void Unload() override;
    void Update() override;
    void Draw() override;

    void setIsFoe(bool foe);
    void setOldPokedexNumber(int pokedexnumber);
};

#endif  // BATTLERLISTSCREEN_HPP