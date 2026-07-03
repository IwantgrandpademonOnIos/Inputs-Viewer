#include "IVNodeSlider.hpp"

using namespace geode::prelude;

GEODE_NS_IV_BEGIN

IVNodeSlider::IVNodeSlider() {}

IVNodeSlider* IVNodeSlider::create(float minValue, float maxValue, float startValue) {
    auto ret = new (std::nothrow) IVNodeSlider();
    if (ret && ret->init(minValue, maxValue, startValue)) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool IVNodeSlider::init(float minValue, float maxValue, float startValue) {
    if (!IVNodeBase::init())
        return false;

    m_min = minValue;
    m_max = maxValue;
    m_value = startValue;

    m_bar = CCSprite::createWithSpriteFrameName("GJ_sliderBar_001.png");
    m_knob = CCSprite::createWithSpriteFrameName("GJ_sliderKnob_001.png");

    if (m_bar) {
        this->addChild(m_bar);
    }
    if (m_knob) {
        this->addChild(m_knob);
    }

    refreshAppearance();
    return true;
}

void IVNodeSlider::setValue(float value) {
    m_value = std::max(m_min, std::min(m_max, value));
    refreshAppearance();
}

void IVNodeSlider::refreshAppearance() {
    if (!m_bar || !m_knob) return;

    float t = (m_value - m_min) / (m_max - m_min);
    float width = m_bar->getContentSize().width;

    m_knob->setPosition({ -width / 2.f + width * t, 0.f });
}

GEODE_NS_IV_END
