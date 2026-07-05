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
// JSON SERIALIZATION (Result<T> + unwrapOr())
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
        auto& obj = v;

        auto posVec = obj["position"].asArray().unwrapOr({}); // fallback empty array

        float x = posVec.size() > 0 ? posVec[0].asDouble().unwrapOr(0.0) : 0.0;
        float y = posVec.size() > 1 ? posVec[1].asDouble().unwrapOr(0.0) : 0.0;

        return inputs_viewer::NodeTransform{
            { x, y },
            obj["scale"].asDouble().unwrapOr(1.0f),
            obj["rotation"].asDouble().unwrapOr(0.0f),
            obj["isVisible"].asBool().unwrapOr(true)
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
        auto& obj = v;

        return inputs_viewer::LevelSettings{
            matjson::Serialize<inputs_viewer::NodeTransform>::fromJson(obj["p1Transform"]),
            matjson::Serialize<inputs_viewer::NodeTransform>::fromJson(obj["p2Transform"])
        };
    }
};
