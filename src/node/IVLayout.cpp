#include "IVLayout.hpp"

using namespace geode::prelude;

GEODE_NS_IV_BEGIN

void IVLayout::applyVerticalLayout(CCArray* nodes, const IVStyle& style) {
    if (!nodes) return;

    float y = 0.f;

    CCObject* obj;
    CCARRAY_FOREACH(nodes, obj) {
        auto node = dynamic_cast<IVNodeBase*>(obj);
        if (!node) continue;

        node->setPosition({0.f, y});
        y -= style.spacing;
    }
}

void IVLayout::applyHorizontalLayout(CCArray* nodes, const IVStyle& style) {
    if (!nodes) return;

    float x = 0.f;

    CCObject* obj;
    CCARRAY_FOREACH(nodes, obj) {
        auto node = dynamic_cast<IVNodeBase*>(obj);
        if (!node) continue;

        node->setPosition({x, 0.f});
        x += style.spacing;
    }
}

GEODE_NS_IV_END
