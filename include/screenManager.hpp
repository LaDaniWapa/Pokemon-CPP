#ifndef SCREEN_MANAGER_HPP
#define SCREEN_MANAGER_HPP

#include <string>
#include <unordered_map>

class ScreenManager;

class Screen {
public:
    // Funciones virtuales que deben ser implementadas por las clases derivadas
    virtual void Load() = 0;
    virtual void Unload() = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;
    virtual ~Screen() = default;

    // Establecer el administrador de pantallas para la clase derivada
    void SetScreenManager(ScreenManager* manager);

    // Establecer datos para ser pasados entre pantallas
    void SetData(const std::string& key, const void* data);

    // Recuperar datos pasados entre pantallas
    const void* GetData(const std::string& key) const;

protected:
    ScreenManager* screenManager = nullptr;                   // Puntero al administrador de pantallas
    std::unordered_map<std::string, const void*> screenData;  // Datos pasados entre pantallas
};

class ScreenManager {
public:
    // Añadir una pantalla al administrador
    void AddScreen(const std::string& name, Screen* screen);

    // Cambiar a una pantalla específica
    void ChangeScreen(const std::string& name);

    // Actualizar la pantalla actual
    void Update();

    // Dibujar la pantalla actual
    void Draw();

    // Obtener un puntero a una pantalla específica por su nombre
    Screen* getScreen(const std::string& name);

private:
    std::unordered_map<std::string, Screen*> screens;  // Mapa de pantallas
    Screen* currentScreen = nullptr;                   // Puntero a la pantalla actual
};

#endif  // SCREEN_MANAGER_HPP
