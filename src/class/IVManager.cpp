#include "IVManager.hpp"
#include "IVLevelSettings.hpp"

using namespace geode::prelude;

GEODE_NS_IV_BEGIN

IVManager::IVManager() {}

IVManager& IVManager::get() {
    static IVManager instance;
    return instance;
}

NodeTransform IVManager::getDefaultP1Transform() {
    return NodeTransform{{0.f, 0.f}, 1.f, 0.f, true};
}

NodeTransform IVManager::getDefaultP2Transform() {
    return NodeTransform{{0.f, 0.f}, 1.f, 0.f, true};
}

void IVManager::loadSettings() {
    auto saved = Mod::get()->getSavedValue<matjson::Value>(
        "level-settings",
        matjson::Value::object()
    );

    if (!saved.isObject()) return;

    auto& obj = saved.as<matjson::Object>().unwrap(); // FIX: unwrap()

    for (auto& [key, value] : obj) {
        m_levelSettings[key] =
            matjson::Serialize<LevelSettings>::fromJson(value);
    }
}

void IVManager::saveSettings() {
    auto saved = matjson::Value::object();

    for (auto const& [key, settings] : m_levelSettings) {
        saved[key] =
            matjson::Serialize<LevelSettings>::toJson(settings);
    }

    Mod::get()->setSavedValue("level-settings", saved);
}

LevelSettings IVManager::getLevelSettings(std::string const& levelID) {
    if (m_levelSettings.contains(levelID)) {
        return m_levelSettings[levelID];
    }

    LevelSettings defaults{
        getDefaultP1Transform(),
        getDefaultP2Transform()
    };

    m_levelSettings[levelID] = defaults;
    return defaults;
}

void IVManager::setLevelSettings(std::string const& levelID,
                                 LevelSettings const& settings) {
    m_levelSettings[levelID] = settings;
    saveSettings();
}

GEODE_NS_IV_END
