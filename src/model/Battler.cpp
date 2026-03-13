#include "Battler.hpp"

Battler::Battler(int pokedexNumber, int level, bool shiny, bool foe, Font& font, Font& fontB) {
    this->foe = foe;
    this->font = font;
    this->fontB = fontB;
    this->level = level;

    if (readPokemonFromFile(pokedexNumber, basePkm)) {
        printBattler(basePkm);
        maxPS = ((basePkm.ps * 2 + IV + EV / 4) * level / 100) + 10 + level;
        currentPS = maxPS;
        updateHealthRect();
        attack = getStat(basePkm.attack);
        defense = getStat(basePkm.defense);
        specialAttack = getStat(basePkm.specialAttack);
        specialDefense = getStat(basePkm.specialDefense);
        speed = getStat(basePkm.speed);
        male = randomNumber(0, 1) == 0;

        battlerTexture = getPokemonTexture(pokedexNumber, shiny, !foe);
        health = LoadTexture("assets/UI/overlay_hp.png");

        if (foe) {
            databox = LoadTexture("assets/UI/databox_normal_foe.png");
            base = LoadTexture("assets/BattleBacks/grass_base1.png");
        } else {
            databox = LoadTexture("assets/UI/databox_normal.png");
            base = LoadTexture("assets/BattleBacks/grass_base0.png");
        }
    }
}

Battler::~Battler() {
    UnloadTexture(battlerTexture);
    UnloadTexture(databox);
    UnloadTexture(base);
    UnloadFont(font);
    UnloadFont(fontB);
}

void Battler::draw() const {
    if (this->foe) {
        DrawTexture(base, 256, 100, WHITE);
        DrawTexture(databox, 0, 37, WHITE);
        DrawTextEx(font, basePkm.name, Vector2{7, 50}, 20, 1, PKGREY);
        DrawTextureRec(health, healthRect, Vector2{118, 77}, WHITE);
        DrawTextEx(fontB, TextFormat("Lv.%i", level), Vector2{170, 52}, 11, 1, PKGREY);
        DrawTexture(battlerTexture, 285, 15, WHITE);
    } else {
        DrawTexture(base, -145, 240, WHITE);
        DrawTexture(databox, 252, 192, WHITE);
        DrawTextEx(font, basePkm.name, Vector2{295, 205}, 20, 1, PKGREY);
        DrawTextureRec(health, healthRect, Vector2{388, 232}, WHITE);
        DrawTextEx(fontB, TextFormat("%i/%i", currentPS, maxPS), Vector2{400, 245}, 11, 1, PKGREY);
        DrawTextEx(fontB, TextFormat("Lv.%i", level), Vector2{440, 207}, 11, 1, PKGREY);
        DrawTextureEx(battlerTexture, Vector2{20, 90}, 0, 1.25f, WHITE);
    }
}

void Battler::updateHealthRect() {
    const float percent = (float) currentPS * 100 / maxPS;

    // 0 green 1 orange 2 red
    uint8_t color;

    if (currentPS < maxPS / 3)
        color = 2;
    else if (currentPS < maxPS * 2 / 3)
        color = 1;
    else
        color = 0;

    this->healthRect = {0, 6.f * color, 96 * percent / 100, 6};
}