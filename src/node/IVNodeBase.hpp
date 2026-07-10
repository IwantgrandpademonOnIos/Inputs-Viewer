#pragma once
#include <Geode/Geode.hpp>

GEODE_NS_IV_BEGIN

class IVNodeBase : public cocos2d::CCNode {
public:
    IVNodeBase();
    virtual bool init();

    // Base hook for appearance updates
    virtual void refreshAppearance() {}
};

GEODE_NS_IV_END
