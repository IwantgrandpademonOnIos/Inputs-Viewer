#pragma once
#include "node/IVNodeBase.hpp"

GEODE_NS_IV_BEGIN

class IVNodeButton : public IVNodeBase {
public:
    IVNodeButton();
    static IVNodeButton* create(const char* labelText);

    bool init(const char* labelText);

    // Visual update when pressed
    void setPressed(bool pressed);

    // Refresh appearance (colors, scale, etc.)
    void refreshAppearance() override;

protected:
    cocos2d::CCLabelBMFont* m_label = nullptr;
    bool m_pressed = false;
};

GEODE_NS_IV_END
