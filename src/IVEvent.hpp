#pragma once

#include "IVConstants.hpp"
#include "macros.hpp"
#include <optional>
#include <Geode/loader/Event.hpp>
#include <Geode/utils/function.hpp>

GEODE_NS_IV_BEGIN

enum class SettingEventType {
    BackgroundColor,
    OutlineColor,
    TextColor,
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

    geode::ListenerResult handle(geode::Function<Callback> fn, IVSettingEvent* event);

private:
    std::optional<SettingEventType> m_type;
};

GEODE_NS_IV_END
