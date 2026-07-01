#pragma once

#include "IVEvent.hpp"
#include "IVLevelSettings.hpp"
#include "class/IVPlayerInputNode.hpp"

GEODE_NS_IV_BEGIN

class InputsViewLayer : public cocos2d::CCLayer {
public:
    InputsViewLayer(LevelSettingsType type);
    static InputsViewLayer* create(LevelSettingsType type);

    bool init() override;

    void handleButton(bool down, PlayerButton input, bool isP1, bool updateCounters);
    LevelSettings const& getLevelSettings() const noexcept;
    void setLevelSettings(LevelSettingsType type);
    void releaseAllButtons();
    void refreshDisplay();

    void onSettingEvent(SettingEventType);

protected:
    std::reference_wrapper<LevelSettings> m_currentSetting;

    IVPlayerInputNode* m_p1InputNode = nullptr;
    IVPlayerInputNode* m_p2InputNode = nullptr;

    // Geode 5 removed EventListener, so this member is gone.
    // geode::EventListener<IVSettingFilter> m_settingListener;
};

GEODE_NS_IV_END
