#pragma once
#include "IVNodeInput.hpp"

GEODE_NS_IV_BEGIN

class IVPlayerInputNode : public IVNodeInput {
public:
    IVPlayerInputNode();
    static IVPlayerInputNode* create(IVInputType type);

    bool init(IVInputType type);

    // Called when the player presses or releases an input
    void updateInputState(bool pressed);

    // Refresh appearance (color, scale, etc.)
    void refreshAppearance() override;

protected:
    bool m_currentPressed = false;
};

GEODE_NS_IV_END
