#pragma once
#include "IVLevelSettings.hpp"
#include <Geode/Geode.hpp>
#include <Geode/loader/Event.hpp>
#include <Geode/loader/SettingV3.hpp>

GEODE_NS_IV_BEGIN

// Old:
// using RGBASettingFilter = geode::SettingChangedEventV3;
// using RGBASettingListener = geode::EventListener<geode::SettingChangedEventV3>;
// Geode 5 removed EventListener, so we just keep the filter type for now.
using RGBASettingFilter = geode::SettingChangedEventV3;

class IVManager {
public:
    IVManager();
    static IVManager& get();
    static NodeTransform getDefaultP1Transform();
    static NodeTransform getDefaultP2Transform();
    LevelSettings& getLevelSettings(LevelSettingsType type) noexcept;

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
    // Geode 5: EventListener no longer exists, so these are removed.
    // If we want listeners later, we’ll re-add them using the new listen() API.
    // RGBASettingListener m_backgroundPressListener;
    // RGBASettingListener m_backgroundReleaseListener;
    // RGBASettingListener m_outlinePressListener;
    // RGBASettingListener m_outlineReleaseListener;
    // RGBASettingListener m_textPressListener;
    // RGBASettingListener m_textReleaseListener;
};

GEODE_NS_IV_END
