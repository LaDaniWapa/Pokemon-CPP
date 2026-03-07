#ifndef POKEMON_CPP_SCREEN_HPP
#define POKEMON_CPP_SCREEN_HPP

#include <string>
#include <unordered_map>

class ScreenManager;

/**
 * @brief Abstract base class for all game screens.
 *
 * Each screen (Title, Battle, etc.) inherits from this class and implements
 * the four lifecycle methods: Load, Unload, Update, and Draw.
 * Screens can communicate with each other by passing data through SetData/GetData,
 * and can trigger screen transitions via the ScreenManager pointer.
 */
class Screen {
public:
    /**
     * @brief Called once when the screen becomes active.
     * Use this to load textures, initialize state, etc.
     */
    virtual void Load() = 0;

    /**
     * @brief Called once when the screen is deactivated.
     * Use this to free textures and clean up resources.
     */
    virtual void Unload() = 0;

    /**
     * @brief Called every frame to handle input and update logic.
     */
    virtual void Update() = 0;

    /**
     * @brief Called every frame to render the screen.
     */
    virtual void Draw() = 0;

    virtual ~Screen() = default;

    /**
     * @brief Assigns the ScreenManager to this screen.
     * Called automatically by ScreenManager::AddScreen().
     * @param manager Pointer to the ScreenManager instance.
     */
    void SetScreenManager(ScreenManager* manager);

    /**
     * @brief Stores a data pointer that can be read by another screen.
     * Useful for passing state between screen transitions (e.g. selected Pokémon).
     * @param key   Identifier for the data entry.
     * @param data  Pointer to the data to store. The caller is responsible for lifetime.
     */
    void SetData(const std::string& key, const void* data);

    /**
     * @brief Retrieves a previously stored data pointer by key.
     * @param key Identifier for the data entry.
     * @return Pointer to the data, or nullptr if the key does not exist.
     */
    const void* GetData(const std::string& key) const;

protected:
    /// Pointer to the ScreenManager, used to trigger screen transitions.
    ScreenManager* screenManager = nullptr;

    /// Key-value store for passing data between screens.
    std::unordered_map<std::string, const void*> screenData;
};

#endif //POKEMON_CPP_SCREEN_HPP