#include "IVManager.hpp"
#include "IVEvent.hpp"
#include "IVLevelSettings.hpp"

using namespace geode::prelude;

// Initializer order doesn't matter here
#pragma GCC diagnostic ignored "-Wreorder-ctor"

// Your macro stays EXACTLY as your fork defines it
#define GEODE_IV_CONSTRUCT_COLOR(__col) \
    m_##__col##PressColor(Mod::get()->getSettingValue<ccColor4B>(#__col "-press-color")); \
    m_##__col##ReleaseColor(Mod::get()->getSettingValue<ccColor4B>(#__col "-release-color")); \
    m_##__col##PressListener( \
        [this](std::shared_ptr<SettingV3> setting) { \
            using SettingType = SettingTypeForValueType<ccColor4B>::SettingType; \
            m_##__col##PressColor = std::static_pointer_cast<SettingType>(setting)->getValue(); \
            IVSettingEvent(SettingEventType::Color).post(); \
        } \
    ); \
    RGBASettingFilter(Mod::get()->getID(), #__col "-press-color"); \
    m_##__col##ReleaseListener( \
        [this](std::shared_ptr<SettingV3> setting) { \
            using SettingType = SettingTypeForValueType<ccColor4B>::SettingType; \
            m_##__col##ReleaseColor = std::static_pointer_cast<SettingType>(setting)->getValue(); \
            IVSettingEvent(SettingEventType::Color).post(); \
        } \
    ); \
    RGBASettingFilter(Mod::get()->getID(), #__col "-release-color");

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
    // The macro MUST be inside the constructor body.
    GEODE_IV_CONSTRUCT_COLOR
