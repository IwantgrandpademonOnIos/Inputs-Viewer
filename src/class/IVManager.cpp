#include "IVManager.hpp"
#include "IVEvent.hpp"
#include "IVLevelSettings.hpp"

using namespace geode::prelude;

// Initializer order doesn't matter here
#pragma GCC diagnostic ignored "-Wreorder-ctor"

// This macro now ONLY loads colors.
// No listeners, no events, no invalid calls.
#define GEODE_IV_CONSTRUCT_COLOR(__col) \
    m_##__col##PressColor = Mod::get()->getSettingValue<ccColor4B>(#__col "-press-color"); \
    m_##__col##ReleaseColor = Mod::get()->getSettingValue<ccColor4B>(#__col "-release-color");

GEODE_NS_IV_BEGIN

IVManager::IVManager()
    : m_isInSetting(false)
    , m_settingClassic(
        Mod::get()->getSavedValue<LevelSettings>("classic", {
            .p1Transform = IVManager::getDefaultP1Transform(),
            .p2Transform = IVManager::getDefaultP2Transform()
        }))
    , m_settingPlatformer(
        Mod::get()->getSavedValue<LevelSettings>("platformer", {
            .p1Transform = IVManager::getDefaultP1Transform(),
            .p2Transform = IVManager::getDefaultP2Transform()
        }))
{
    // Load all color settings
    GEODE_IV_CONSTRUCT_COLOR(background)
    GEODE_IV_CONSTRUCT_COLOR(outline)
    GEODE_IV_CONSTRUCT_COLOR(text)
}

IVManager& IVManager::get() {
    static IVManager instance;
    return instance;
}

NodeTransform IVManager::getDefaultP1Transform() {
    return {
        .position = { 0.f, 0.f },
        .scale = 1.f,
        .rotation = 0.f,
        .isVisible = true
    };
}

NodeTransform IVManager::getDefaultP2Transform() {
    return {
        .position = { 0.f, 0.f },
        .scale = 1.f,
        .rotation = 0.f,
        .isVisible = true
    };
}

LevelSettings& IVManager::getLevelSettings(LevelSettingsType type) noexcept {
    switch (type) {
        case LevelSettingsType::Classic:
            return m_settingClassic;
        case LevelSettingsType::Platformer:
            return m_settingPlatformer;
    }
    return m_settingClassic; // fallback
}

GEODE_NS_IV_END
