#include "screenManager.hpp"

void Screen::SetScreenManager(ScreenManager* manager) {
    screenManager = manager;
}

void Screen::SetData(const std::string& key, const void* data) {
    screenData[key] = data;
}

const void* Screen::GetData(const std::string& key) const {
    auto it = screenData.find(key);
    return (it != screenData.end()) ? it->second : nullptr;
}

void ScreenManager::AddScreen(const std::string& name, Screen* screen) {
    screens[name] = screen;
}

void ScreenManager::ChangeScreen(const std::string& name) {
    if (currentScreen) {
        currentScreen->Unload();
    }

    auto it = screens.find(name);
    if (it != screens.end()) {
        currentScreen = it->second;
        currentScreen->Load();
    }
}

void ScreenManager::Update() {
    if (currentScreen) {
        currentScreen->Update();
    }
}

void ScreenManager::Draw() {
    if (currentScreen) {
        currentScreen->Draw();
    }
}

Screen* ScreenManager::getScreen(const std::string& name) {
    auto it = screens.find(name);
    return (it != screens.end()) ? it->second : nullptr;
}