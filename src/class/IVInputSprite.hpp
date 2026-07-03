#pragma once
#include <Geode/Geode.hpp>

GEODE_NS_IV_BEGIN

class IVInputSprite : public cocos2d::CCSprite {
public:
    IVInputSprite();
    static IVInputSprite* create(const char* spriteName);

    bool init(const char* spriteName);

    // Update pressed state visuals
    void setPressed(bool pressed);

protected:
    bool m_pressed = false;
};

GEODE_NS_IV_END
