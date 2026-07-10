#include "node/IVNodeIcon.hpp"

using namespace geode::prelude;

GEODE_NS_IV_BEGIN

IVNodeIcon::IVNodeIcon() {}

IVNodeIcon* IVNodeIcon::create(const char* spriteName) {
    auto ret = new (std::nothrow) IVNodeIcon();
    if (ret && ret->init(spriteName)) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool IVNodeIcon::init(const char* spriteName) {
    if (!IVNodeBase::init())
        return false;

    m_icon = CCSprite::createWithSpriteFrameName(spriteName);
    if (m_icon) {
        m_icon->setScale(0.8f);
        this->addChild(m_icon);
    }

    return true;
}

void IVNodeIcon::setSprite(const char* spriteName) {
    if (!m_icon) return;

    auto frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(spriteName);
    if (frame) {
        m_icon->setDisplayFrame(frame);
    }
}

void IVNodeIcon::refreshAppearance() {
    if (!m_icon) return;

    // Simple styling
    m_icon->setColor(ccWHITE);
}

GEODE_NS_IV_END
