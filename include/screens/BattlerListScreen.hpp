#ifndef BATTLERLISTSCREEN_HPP
#define BATTLERLISTSCREEN_HPP

#include <raylib.h>

#include "screenManager.hpp"

class BattlersListScreen : public Screen {
   private:
    // Primer frame de la textura
    Rectangle textureRect{0, 0, 64, 64};
    // Frame actualizable
    Rectangle selectedPokemonTextureRect{0, 0, 64, 64};
    // Contador de frames
    int framecounter = 0;
    // Array de las texturas de una caja
    Texture2D pokemonTextures[30]{};
    // Fondo de la caja pokemon
    Texture2D boxBg{};
    // Coordenadas del raton
    Vector2 mousePoint{};
    // Variables para calcular el numero de pokemon basandonos en la posicion del raton
    int x{}, y{}, pokedexNumber{};
    // Pokemon que no queremos cambiar
    int oldPokedexNumber{};
    // Numero de la caja pokemon
    int box{};
    // Cambiar el pokemon contrario o el tuyo
    bool isFoe{};

    // Cargar texturas de la caja
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