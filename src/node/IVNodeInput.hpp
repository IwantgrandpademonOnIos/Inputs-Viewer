#pragma once
#include "node/IVNodeBase.hpp"

GEODE_NS_IV_BEGIN

enum class IVInputType {
    Jump,
    Left,
    Right,
    Unknown
};

class IVNodeInput : public IVNodeBase {
public:
    IVNodeInput();
    static IVNodeInput* create(IVInputType type);

    bool init(IVInputType type);

    // Update pressed state
    void setPressed(bool pressed);

    // Refresh appearance (color, scale, etc.)
    void refreshAppearance() override;

protected:
    IVInputType m_type = IVInputType::Unknown;
    cocos2d::CCSprite* m_icon = nullptr;
    bool m_pressed = false;
};

GEODE_NS_IV_END
