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

        float x = 0.f;
        float y = 0.f;

        // position array
        auto arrResult = obj["position"].asArray();
        if (arrResult.isOk()) {
            auto const& arr = arrResult.unwrap();

            if (arr.size() > 0 && arr[0].isNumber()) {
                auto n = arr[0].asDouble();
                if (n.isOk()) x = static_cast<float>(n.unwrap());
            }

            if (arr.size() > 1 && arr[1].isNumber()) {
                auto n = arr[1].asDouble();
                if (n.isOk()) y = static_cast<float>(n.unwrap());
            }
        }

        // scale
        float scale = 1.f;
        auto scaleResult = obj["scale"].asDouble();
        if (scaleResult.isOk())
            scale = static_cast<float>(scaleResult.unwrap());

        // rotation
        float rotation = 0.f;
        auto rotResult = obj["rotation"].asDouble();
        if (rotResult.isOk())
            rotation = static_cast<float>(rotResult.unwrap());

        // isVisible
        bool isVisible = true;
        auto visResult = obj["isVisible"].asBool();
        if (visResult.isOk())
            isVisible = visResult.unwrap();

        return inputs_viewer::NodeTransform{
            { x, y },
            scale,
            rotation,
            isVisible
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
