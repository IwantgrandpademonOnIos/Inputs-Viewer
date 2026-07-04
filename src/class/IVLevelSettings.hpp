#pragma once

#include <Geode/Geode.hpp>
#include <Geode/utils/cocos.hpp>
#include <matjson.hpp>

GEODE_NS_IV_BEGIN

// Transform for each player's input viewer node
struct NodeTransform {
    cocos2d::CCPoint position;
    float scale;
    float rotation;
    bool isVisible;
};

// Settings stored per-level
struct LevelSettings {
    NodeTransform p1Transform;
    NodeTransform p2Transform;
};

GEODE_NS_IV_END

// ---------------------------------------------------------
// JSON SERIALIZATION (REQUIRED FOR getSavedValue<LevelSettings>)
// ---------------------------------------------------------

// Serialize NodeTransform
template <>
struct matjson::Serialize<inputs_viewer::NodeTransform> {
    static matjson::Value toJson(inputs_viewer::NodeTransform const& t) {
        return matjson::Object{
            {"position", matjson::Array{t.position.x, t.position.y}},
            {"scale", t.scale},
            {"rotation", t.rotation},
            {"isVisible", t.isVisible}
        };
    }

    static inputs_viewer::NodeTransform fromJson(matjson::Value const& v) {
        auto obj = v.asObject();
        auto
