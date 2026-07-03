#pragma once

#include <optional>
#include <Geode/loader/Event.hpp>
#include <Geode/utils/function.hpp>

GEODE_NS_IV_BEGIN

// Types of setting events
enum class SettingEventType {
    BackgroundColor,
    OutlineColor,
    TextColor,
};

// Event object carrying the type
class IVSettingEvent : public geode::Event {
public:
    IVSettingEvent(SettingEventType type)
        : m_type(type) {}

    SettingEventType getType() const noexcept {
        return m_type;
    }

private:
    SettingEventType m_type;
};

// Filter for listening to specific setting events
class IVSettingFilter {
public:
    IVSettingFilter()
        : m_type(std::nullopt) {}

    IVSettingFilter(std::nullopt_t)
        : IVSettingFilter() {}

    IVSettingFilter(SettingEventType type)
        : m_type(type) {}

    using Callback = void(SettingEventType);

    geode::ListenerResult handle(geode::Function<Callback> fn, IVSettingEvent* event) {
        if (m_type && m_type.value() != event->getType())
            return geode::ListenerResult::Propagate;

        fn(event->getType());
        return geode::ListenerResult::Propagate;
    }

private:
    std::optional<SettingEventType> m_type;
};

GEODE_NS_IV_END
