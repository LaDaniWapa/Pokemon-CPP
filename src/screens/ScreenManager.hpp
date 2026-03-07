#ifndef SCREEN_MANAGER_HPP
#define SCREEN_MANAGER_HPP

#include <string>
#include <unordered_map>
#include "screens/Screen.hpp"

/**
 * @brief Manages all game screens and controls which one is currently active.
 *
 * Screens are registered by name with AddScreen(), and transitions are triggered
 * with ChangeScreen(). Only one screen is active at a time — the manager calls
 * Unload() on the outgoing screen and Load() on the incoming one automatically.
 */
class ScreenManager {
public:
    /**
     * @brief Registers a screen under a given name.
     * Also injects the ScreenManager pointer into the screen via SetScreenManager().
     * @param name   Unique identifier for the screen (e.g. "battle", "title").
     * @param screen Pointer to the Screen instance. The caller owns the memory.
     */
    void AddScreen(const std::string& name, Screen* screen);

    /**
     * @brief Transitions to the screen with the given name.
     * Calls Unload() on the current screen and Load() on the new one.
     * Does nothing if the name is not found.
     * @param name Identifier of the screen to switch to.
     */
    void ChangeScreen(const std::string& name);

    /**
     * @brief Forwards the Update() call to the currently active screen.
     * Should be called once per frame in the main game loop.
     */
    void Update() const;

    /**
     * @brief Forwards the Draw() call to the currently active screen.
     * Should be called once per frame inside BeginDrawing()/EndDrawing().
     */
    void Draw() const;

    /**
     * @brief Returns a pointer to a registered screen by name.
     * Useful for preloading data into a screen before transitioning to it.
     * @param name Identifier of the screen to retrieve.
     * @return Pointer to the Screen, or nullptr if not found.
     */
    Screen* getScreen(const std::string& name);

private:
    /// Map of all registered screens, keyed by name.
    std::unordered_map<std::string, Screen*> screens;

    /// Pointer to the currently active screen.
    Screen* currentScreen = nullptr;
};

#endif // SCREEN_MANAGER_HPP
