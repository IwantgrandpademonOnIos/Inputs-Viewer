#include "IVLevelSettings.hpp"

using namespace geode::prelude;

GEODE_NS_IV_BEGIN

void NodeTransform::applyTransform(cocos2d::CCNode* node) const {
    if (!node) return;

    node->setPosition(position);
    node->setScale(scale);
    node->setRotation(rotation);
    node->setVisible(isVisible);
}

void NodeTransform::setValues(cocos2d::CCNode* node) {
    if (!node) return;

    position = node->getPosition();
    scale = node->getScale();
    rotation = node->getRotation();
    isVisible = node->isVisible();
}

GEODE_NS_IV_END
