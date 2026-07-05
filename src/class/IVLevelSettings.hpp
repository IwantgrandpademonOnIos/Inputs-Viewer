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

        if (obj["position"].isArray()) {
            auto arr = obj["position"].asArray();
            if (arr.size() > 0 && arr[0].isNumber())
                x = static_cast<float>(arr[0].asNumber());
            if (arr.size() > 1 && arr[1].isNumber())
                y = static_cast<float>(arr[1].asNumber());
        }

        float scale = obj["scale"].isNumber()
            ? static_cast<float>(obj["scale"].asNumber())
            : 1.f;

        float rotation = obj["rotation"].isNumber()
            ? static_cast<float>(obj["rotation"].asNumber())
            : 0.f;

        bool isVisible = obj["isVisible"].isBool()
            ? obj["isVisible"].asBool()
            : true;

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
