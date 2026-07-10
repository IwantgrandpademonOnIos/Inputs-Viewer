#include "IVNodeText.hpp"

using namespace geode::prelude;

GEODE_NS_IV_BEGIN

IVNodeText::IVNodeText() {}

IVNodeText* IVNodeText::create(const char* text) {
    auto ret = new (std::nothrow) IVNodeText();
    if (ret && ret->init(text)) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool IVNodeText::init(const char* text) {
    if (!IVNodeBase::init())
        return false;

    m_text = CCLabelBMFont::create(text, "chatFont.fnt");
    if (m_text) {
        m_text->setScale(0.5f);
        m_text->setAnchorPoint({0.f, 1.f}); // top-left style
        this->addChild(m_text);
    }

    return true;
}

void IVNodeText::setText(const char* text) {
    if (m_text) {
        m_text->setString(text);
    }
}

void IVNodeText::refreshAppearance() {
    if (!m_text) return;

    // Simple styling
    m_text->setColor(ccWHITE);
}

GEODE_NS_IV_END
