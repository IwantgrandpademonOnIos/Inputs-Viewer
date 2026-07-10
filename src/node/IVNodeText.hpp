#pragma once
#include "node/IVNodeBase.hpp"

GEODE_NS_IV_BEGIN

class IVNodeText : public IVNodeBase {
public:
    IVNodeText();
    static IVNodeText* create(const char* text);

    bool init(const char* text);

    // Update text content
    void setText(const char* text);

    // Refresh appearance (color, scale, etc.)
    void refreshAppearance() override;

protected:
    cocos2d::CCLabelBMFont* m_text = nullptr;
};

GEODE_NS_IV_END
