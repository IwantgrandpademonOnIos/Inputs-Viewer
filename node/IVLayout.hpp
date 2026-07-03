#pragma once
#include <Geode/Geode.hpp>
#include "IVNodeBase.hpp"
#include "IVStyle.hpp"

GEODE_NS_IV_BEGIN

class IVLayout {
public:
    IVLayout() = default;

    void applyVerticalLayout(cocos2d::CCArray* nodes, const IVStyle& style);
    void applyHorizontalLayout(cocos2d::CCArray* nodes, const IVStyle& style);
};

GEODE_NS_IV_END
