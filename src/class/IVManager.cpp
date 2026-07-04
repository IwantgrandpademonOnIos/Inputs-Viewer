#include "IVManager.hpp"
#include "IVLevelSettings.hpp"

using namespace geode::prelude;

GEODE_NS_IV_BEGIN

IVManager& IVManager::get() {
    static IVManager instance;
    return instance;
}

void IVManager::loadSettings() {
    auto saved = Mod::get()->getSavedValue<matjson::Value>("level-settings", matjson::Object{});

    for (auto& [key, value] : saved.asObject()) {
        // Deserialize LevelSettings from JSON
        LevelSettings settings = matjson::Serialize<LevelSettings>::fromJson(value);

        m_levelSettings[key] = settings;
    }
}

void IVManager::saveSettings() {
    matjson::Object saved;

    for (auto const& [key, settings] : m_levelSettings) {
        // Serialize LevelSettings into JSON
        saved[key] = matjson::Serialize<LevelSettings>::toJson(settings);
    }

    Mod::get()->setSavedValue("level-settings", saved);
}

LevelSettings IVManager::getLevelSettings(std::string const& levelID) {
    if (m_levelSettings.contains(levelID)) {
        return m_levelSettings[levelID];
    }

    // Default settings
    LevelSettings defaultSettings{
        NodeTransform{{0.f, 0.f}, 1.f, 0.f, true},
        NodeTransform{{0.f, 0.f}, 1.f, 0.f, true}
    };

    // Save default using proper JSON serialization
    m_levelSettings[levelID] = defaultSettings;

    return defaultSettings;
}

void IVManager::setLevelSettings(std::string const& levelID, LevelSettings const& settings) {
    m_levelSettings[levelID] = settings;
    saveSettings();
}

GEODE_NS_IV_END
