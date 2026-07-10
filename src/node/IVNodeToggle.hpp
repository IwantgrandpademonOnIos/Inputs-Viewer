#pragma once
#include "node/IVNodeBase.hpp"

GEODE_NS_IV_BEGIN

class IVNodeToggle : public IVNodeBase {
public:
    IVNodeToggle();
    static IVNodeToggle* create(bool startState);

    bool init(bool startState);

    // Change toggle state
    void setToggled(bool toggled);

    // Get current state
    bool isToggled() const { return m_toggled; }

    // Refresh appearance (color, icon, etc.)
    void refreshAppearance() override;

protected:
    bool m_toggled = false;
    cocos2d::CCSprite* m_box = nullptr;
    cocos2d::CCSprite* m_check = nullptr;
};

GEODE_NS_IV_END
