#pragma once
#include <Geode/Geode.hpp>

GEODE_NS_IV_BEGIN

enum class LevelSettingsType {
    Classic,
    Platformer
};

struct NodeTransform {
    cocos2d::CCPoint position;
    float scale;
    float rotation;
    bool isVisible;
};

struct LevelSettings {
    NodeTransform p1Transform;
    NodeTransform p2Transform;
};

GEODE_NS_IV_END
