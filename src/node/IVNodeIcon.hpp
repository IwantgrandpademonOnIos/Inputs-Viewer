#pragma once
#include "node/IVNodeBase.hpp"

GEODE_NS_IV_BEGIN

class IVNodeIcon : public IVNodeBase {
public:
    IVNodeIcon();
    static IVNodeIcon* create(const char* spriteName);

    bool init(const char* spriteName);

    // Change the icon sprite
    void setSprite(const char* spriteName);

    // Refresh appearance (color, scale, etc.)
    void refreshAppearance() override;

protected:
    cocos2d::CCSprite* m_icon = nullptr;
};

GEODE_NS_IV_END
