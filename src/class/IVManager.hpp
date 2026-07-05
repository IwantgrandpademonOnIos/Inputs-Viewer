#pragma once

#include "IVLevelSettings.hpp"
#include <Geode/Geode.hpp>
#include <Geode/loader/Event.hpp>
#include <Geode/loader/SettingV3.hpp>
#include <unordered_map>

GEODE_NS_IV_BEGIN

using RGBASettingFilter = geode::SettingChangedEventV3;

class IVManager {
public:
    IVManager();
    static IVManager& get();

    // Default transforms
    static NodeTransform getDefaultP1Transform();
    static NodeTransform getDefaultP2Transform();

    // Per-level settings
    LevelSettings getLevelSettings(std::string const& levelID);
    void setLevelSettings(std::string const& levelID, LevelSettings const& settings);

    // Load/save all settings
    void loadSettings();
    void saveSettings();

public:
    bool m_isInSetting;

    cocos2d::ccColor4B m_backgroundPressColor;
    cocos2d::ccColor4B m_backgroundReleaseColor;
    cocos2d::ccColor4B m_outlinePressColor;
    cocos2d::ccColor4B m_outlineReleaseColor;
    cocos2d::ccColor4B m_textPressColor;
    cocos2d::ccColor4B m_textReleaseColor;

    LevelSettings m_settingClassic;
    LevelSettings m_settingPlatformer;

protected:
    // Map of levelID → LevelSettings
    std::unordered_map<std::string, LevelSettings> m_levelSettings;
};

GEODE_NS_IV_END
