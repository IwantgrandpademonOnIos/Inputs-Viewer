#include "node/IVNodeButton.hpp"

using namespace geode::prelude;

GEODE_NS_IV_BEGIN

IVNodeButton::IVNodeButton() {}

IVNodeButton* IVNodeButton::create(const char* labelText) {
    auto ret = new (std::nothrow) IVNodeButton();
    if (ret && ret->init(labelText)) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool IVNodeButton::init(const char* labelText) {
    if (!IVNodeBase::init())
        return false;

    // Create label
    m_label = CCLabelBMFont::create(labelText, "chatFont.fnt");
    m_label->setScale(0.6f);
    this->addChild(m_label);

    return true;
}

void IVNodeButton::setPressed(bool pressed) {
    m_pressed = pressed;

    // Simple visual feedback
    this->setOpacity(pressed ? 180 : 255);
    this->setScale(pressed ? 0.95f : 1.0f);
}

void IVNodeButton::refreshAppearance() {
    // Update label color based on pressed state
    if (m_label) {
        m_label->setColor(m_pressed ? ccRED : ccWHITE);
    }
}

GEODE_NS_IV_END
