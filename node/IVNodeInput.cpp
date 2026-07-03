#include "IVNodeInput.hpp"

using namespace geode::prelude;

GEODE_NS_IV_BEGIN

static const char* getInputSprite(IVInputType type) {
    switch (type) {
        case IVInputType::Jump: return "GJ_button_01.png";
        case IVInputType::Left: return "GJ_button_02.png";
        case IVInputType::Right: return "GJ_button_03.png";
        default: return "GJ_button_01.png";
    }
}

IVNodeInput::IVNodeInput() {}

IVNodeInput* IVNodeInput::create(IVInputType type) {
    auto ret = new (std::nothrow) IVNodeInput();
    if (ret && ret->init(type)) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool IVNodeInput::init(IVInputType type) {
    if (!IVNodeBase::init())
        return false;

    m_type = type;

    // Create icon
    m_icon = CCSprite::createWithSpriteFrameName(getInputSprite(type));
    if (m_icon) {
        m_icon->setScale(0.8f);
        this->addChild(m_icon);
    }

    return true;
}

void IVNodeInput::setPressed(bool pressed) {
    m_pressed = pressed;

    // Visual feedback
    if (m_icon) {
        m_icon->setOpacity(pressed ? 180 : 255);
        m_icon->setScale(pressed ? 0.9f : 1.0f);
    }
}

void IVNodeInput::refreshAppearance() {
    if (!m_icon) return;

    // Color feedback
    if (m_pressed)
        m_icon->setColor(ccRED);
    else
        m_icon->setColor(ccWHITE);
}

GEODE_NS_IV_END
