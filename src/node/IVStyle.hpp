#pragma once
#include <Geode/Geode.hpp>

GEODE_NS_IV_BEGIN

struct IVStyle {
    float padding = 6.f;
    float spacing = 10.f;

    ccColor3B colorDefault = ccWHITE;
    ccColor3B colorPressed = ccRED;

    float scaleDefault = 1.0f;
    float scalePressed = 0.9f;
};

GEODE_NS_IV_END
