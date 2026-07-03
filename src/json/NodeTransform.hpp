#pragma once
#include <Geode/Geode.hpp>

GEODE_NS_IV_BEGIN

struct NodeTransform {
    cocos2d::CCPoint position{0.f, 0.f};
    float scale{1.f};
    float rotation{0.f};
    bool isVisible{true};

    void applyTransform(cocos2d::CCNode* node) const;
    void setValues(cocos2d::CCNode* node);
};

GEODE_NS_IV_END
