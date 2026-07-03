#include "IVInputSprite.hpp"

using namespace geode::prelude;

GEODE_NS_IV_BEGIN

IVInputSprite::IVInputSprite() {}

IVInputSprite* IVInputSprite::create(const char* spriteName) {
    auto ret = new (std::nothrow) IVInputSprite();
    if (ret && ret->init(spriteName)) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool IVInputSprite::init(const char* spriteName) {
    auto frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(spriteName);
    if (!frame)
        return false;

    if (!CCSprite::initWithSpriteFrame(frame))
        return false;

    m_pressed = false;
    return true;
}

void IVInputSprite::setPressed(bool pressed) {
    m_pressed = pressed;

    this->setOpacity(pressed ? 180 : 255);
    this->setScale(pressed ? 0.9f : 1.0f);
}

GEODE_NS_IV_END
