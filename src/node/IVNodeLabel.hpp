#include "IVNodeLabel.hpp"

using namespace geode::prelude;

GEODE_NS_IV_BEGIN

IVNodeLabel::IVNodeLabel() {}

IVNodeLabel* IVNodeLabel::create(const char* text) {
    auto ret = new (std::nothrow) IVNodeLabel();
    if (ret && ret->init(text)) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool IVNodeLabel::init(const char* text) {
    if (!IVNodeBase::init())
        return false;

    m_label = CCLabelBMFont::create(text, "chatFont.fnt");
    if (m_label) {
        m_label->setScale(0.6f);
        this->addChild(m_label);
    }

    return true;
}

void IVNodeLabel::setText(const char* text) {
    if (m_label) {
        m_label->setString(text);
    }
}

void IVNodeLabel::refreshAppearance() {
    if (!m_label) return;

    // Simple color styling
    m_label->setColor(ccWHITE);
}

GEODE_NS_IV_END
