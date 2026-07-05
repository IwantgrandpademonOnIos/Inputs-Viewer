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

GEODE_NS_IV_END   // ⭐ THIS LINE FIXES YOUR BUILD

// ---------------------------------------------------------
// JSON SERIALIZATION (correct for your matjson version)
// ---------------------------------------------------------

template <>
struct matjson::Serialize<inputs_viewer::NodeTransform> {
    static matjson::Value to_json(inputs_viewer::NodeTransform const& t) {
        auto obj = matjson::Value::object();
        obj["position"] = matjson::Value::array({ t.position.x, t.position.y });
        obj["scale"] = t.scale;
        obj["rotation"] = t.rotation;
        obj["isVisible"] = t.isVisible;
        return obj;
    }

    static inputs_viewer::NodeTransform from_json(matjson::Value const& v) {
        auto obj = v.as_object();
        auto pos = obj["position"].as_array();

        return inputs_viewer::NodeTransform{
            { pos[0].as_double(), pos[1].as_double() },
            obj["scale"].as_double(),
            obj["rotation"].as_double(),
            obj["isVisible"].as_bool()
        };
    }
};

template <>
struct matjson::Serialize<inputs_viewer::LevelSettings> {
    static matjson::Value to_json(inputs_viewer::LevelSettings const& s) {
        auto obj = matjson::Value::object();
        obj["p1Transform"] = matjson::Serialize<inputs_viewer::NodeTransform>::to_json(s.p1Transform);
        obj["p2Transform"] = matjson::Serialize<inputs_viewer::NodeTransform>::to_json(s.p2Transform);
        return obj;
    }

    static inputs_viewer::LevelSettings from_json(matjson::Value const& v) {
        auto obj = v.as_object();
        return inputs_viewer::LevelSettings{
            matjson::Serialize<inputs_viewer::NodeTransform>::from_json(obj["p1Transform"]),
            matjson::Serialize<inputs_viewer::NodeTransform>::from_json(obj["p2Transform"])
        };
    }
};
