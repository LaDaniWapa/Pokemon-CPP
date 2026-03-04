#ifndef TITLESCREEN_HPP
#define TITLESCREEN_HPP

#include <raylib.h>
#include "screenManager.hpp"

class TitleScreen : public Screen {
    Texture2D background{};
    Image titleAnimatedImage{};
    int frames{0};
    unsigned int nextFrameDataOffset{0};
    int currentFrame{0}, frameDelay{8}, frameCounter{0};

public:
    void Load() override;
    void Unload() override;
    void Update() override;
    void Draw() override;
};

#endif  // TITLESCREEN_HPP
