#pragma once

#include "IVConstants.hpp"
#include "macros.hpp"

GEODE_NS_IV_BEGIN

enum class SettingEventType {
    BackgroundColor,
    OutlineColor,
    TextColor,
    // add any other types you use here
};

class IVSettingEvent {
public:
    IVSettingEvent(SettingEventType type);

    SettingEventType getType() const noexcept;

private:
    SettingEventType m_type;
};

class IVSettingFilter {
public:
    IVSettingFilter();
    IVSettingFilter(std::nullopt_t);
    IVSettingFilter(SettingEventType type);

    using Callback = void(SettingEventType);

    ListenerResult handle(geode::Function<Callback> fn, IVSettingEvent* event);

private:
    std::optional<SettingEventType> m_type;
};

GEODE_NS_IV_END
