#pragma once

#include <Geode/Geode.hpp>
#include <Geode/utils/cocos.hpp>
#include <matjson.hpp>

GEODE_NS_IV_BEGIN

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

// ---------------------------------------------------------
// JSON SERIALIZATION (for Result<> matjson API)
// ---------------------------------------------------------

template <>
struct matjson::Serialize<inputs_viewer::NodeTransform> {
    static matjson::Value toJson(inputs_viewer::NodeTransform const& t) {
        auto obj = matjson::Value::object();

        auto pos = matjson::Value::array();
        pos.push(t.position.x);
        pos.push(t.position.y);

        obj["position"] = pos;
        obj["scale"] = t.scale;
        obj["rotation"] = t.rotation;
        obj["isVisible"] = t.isVisible;

        return obj;
    }

    static inputs_viewer::NodeTransform fromJson(matjson::Value const& v) {
        auto obj = v();

        auto posResult = obj["position"].asArray();
        auto const& pos = posResult.value();   // ⭐ THIS FIXES YOUR ERROR

        return inputs_viewer::NodeTransform{
            { pos[0].asDouble(), pos[1].asDouble() },
            obj["scale"].asDouble(),
            obj["rotation"].asDouble(),
            obj["isVisible"].asBool()
        };
    }
};

template <>
struct matjson::Serialize<inputs_viewer::LevelSettings> {
    static matjson::Value toJson(inputs_viewer::LevelSettings const& s) {
        auto obj = matjson::Value::object();
        obj["p1Transform"] = matjson::Serialize<inputs_viewer::NodeTransform>::toJson(s.p1Transform);
        obj["p2Transform"] = matjson::Serialize<inputs_viewer::NodeTransform>::toJson(s.p2Transform);
        return obj;
    }

    static inputs_viewer::LevelSettings fromJson(matjson::Value const& v) {
        auto obj = v.asObject();

        return inputs_viewer::LevelSettings{
            matjson::Serialize<inputs_viewer::NodeTransform>::fromJson(obj["p1Transform"]),
            matjson::Serialize<inputs_viewer::NodeTransform>::fromJson(obj["p2Transform"])
        };
    }
};
