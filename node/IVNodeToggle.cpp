#include "IVNodeToggle.hpp"

using namespace geode::prelude;

GEODE_NS_IV_BEGIN

IVNodeToggle::IVNodeToggle() {}

IVNodeToggle* IVNodeToggle::create(bool startState) {
    auto ret = new (std::nothrow) IVNodeToggle();
    if (ret && ret->init(startState)) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool IVNodeToggle::init(bool startState) {
    if (!IVNodeBase::init())
        return false;

    m_toggled = startState;

    m_box = CCSprite::createWithSpriteFrameName("GJ_checkBox_001.png");
    m_check = CCSprite::createWithSpriteFrameName("GJ_check_001.png");

    if (m_box) {
        this->addChild(m_box);
    }
    if (m_check) {
        this->addChild(m_check);
    }

    refreshAppearance();
    return true;
}

void IVNodeToggle::setToggled(bool toggled) {
    m_toggled = toggled;
    refreshAppearance();
}

void IVNodeToggle::refreshAppearance() {
    if (!m_box || !m_check) return;

    // Show checkmark only when toggled
    m_check->setVisible(m_toggled);

    // Slight color feedback
    m_box->setColor(m_toggled ? ccGREEN : ccWHITE);
}

GEODE_NS_IV_END
