#pragma once

#include "Scene.h"
#include <memory>
#include <unordered_map>
#include <string>
#include <functional>

// Gestor global de escenas (singleton).
// Permite registrar fábricas de escenas por nombre, solicitar cambios de
// escena de forma diferida y delegar llamadas de actualización y teclado.
class SceneManager {
public:
    // Acceso a la instancia única.
    static SceneManager& instance() {
        static SceneManager inst;
        return inst;
    }

    // Registra una escena concreta T con un identificador de nombre.
    // T debe derivar de Scene y exponer un constructor T(const std::string&).
    template <typename T>
    void registerScene(const std::string& name) {
        m_factories[name] = [name]() { return std::make_unique<T>(name); };
    }

    // Solicita el cambio de escena. El cambio se aplicará de forma diferida
    // durante la próxima llamada a update() para evitar modificar la escena
    // actual mientras se itera sobre ella.
    void changeScene(const std::string& name);

    // Actualiza la escena actual (y aplica cambios pendientes antes de ello).
    // dt es el tiempo en segundos desde la última actualización.
    void update(double dt);

    // Reenvía eventos de teclado a la escena actual.
    void keyPress(unsigned char key, const physx::PxTransform& cameraTransform);

    // Devuelve un puntero a la escena actual (no toma propiedad).
    [[nodiscard]] Scene* getCurrentScene() const { return m_currentScene.get(); }

private:
    SceneManager() = default;

    // Map de fábricas que crean instancias de Scene identificadas por nombre.
    std::unordered_map<std::string, std::function<std::unique_ptr<Scene>()>> m_factories;
    // Escena actualmente activa.
    std::unique_ptr<Scene> m_currentScene{ nullptr };
    // Nombre de la escena pendiente de cargar y flag para indicar cambio.
    std::string m_pendingSceneName;
    bool m_hasPendingChange{ false };

    // Aplica el cambio pendiente (limpia la escena actual y crea la nueva).
    void applyPendingSceneChange();
};
