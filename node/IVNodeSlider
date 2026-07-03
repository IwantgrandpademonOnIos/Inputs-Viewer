#pragma once
#include "IVNodeBase.hpp"

GEODE_NS_IV_BEGIN

class IVNodeSlider : public IVNodeBase {
public:
    IVNodeSlider();
    static IVNodeSlider* create(float minValue, float maxValue, float startValue);

    bool init(float minValue, float maxValue, float startValue);

    // Set current value
    void setValue(float value);

    // Get current value
    float getValue() const { return m_value; }

    // Refresh appearance (bar fill, knob position)
    void refreshAppearance() override;

protected:
    float m_min = 0.f;
    float m_max = 1.f;
    float m_value = 0.f;

    cocos2d::CCSprite* m_bar = nullptr;
    cocos2d::CCSprite* m_knob = nullptr;
};

GEODE_NS_IV_END
