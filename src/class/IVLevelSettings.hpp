#pragma once

#include <Geode/Geode.hpp>
#include <Geode/utils/cocos.hpp>
#include <matjson.hpp>

GEODE_NS_IV_BEGIN

// Transform for each player’s input viewer node
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

// -------------------------------
// JSON SERIALIZATION (REQUIRED)
// -------------------------------

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
        auto pos = obj["position"].asArray();

        return inputs_viewer::NodeTransform{
            {pos[0].asDouble(), pos[1].asDouble()},
            obj["scale"].asDouble(),
            obj["rotation"].asDouble(),
            obj["isVisible"].asBool()
        };
    }
};

template <>
struct matjson::Serialize<inputs_viewer::LevelSettings> {
    static matjson::Value toJson(inputs_viewer::LevelSettings const& s) {
        return matjson::Object{
            {"p1Transform", matjson::Serialize<inputs_viewer::NodeTransform>::toJson(s.p1Transform)},
            {"p2Transform", matjson::Serialize<inputs_viewer::NodeTransform>::toJson(s.p2Transform)}
        };
    }

    static inputs_viewer::LevelSettings fromJson(matjson::Value const& v) {
        auto obj = v.asObject();
        return inputs_viewer::LevelSettings{
            matjson::Serialize<inputs_viewer::NodeTransform>::fromJson(obj["p1Transform"]),
            matjson::Serialize<inputs_viewer::NodeTransform>::fromJson(obj["p2Transform"])
        };
    }
};
