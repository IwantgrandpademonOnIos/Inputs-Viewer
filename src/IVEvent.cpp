#include "IVEvent.hpp"

using namespace geode::prelude;

GEODE_NS_IV_BEGIN

IVSettingEvent::IVSettingEvent(SettingEventType type)
    : m_type(type) {}

SettingEventType IVSettingEvent::getType() const noexcept {
    return m_type;
}

IVSettingFilter::IVSettingFilter()
    : m_type(std::nullopt) {}

IVSettingFilter::IVSettingFilter(std::nullopt_t) : IVSettingFilter() {}

IVSettingFilter::IVSettingFilter(SettingEventType type)
    : m_type(type) {}

// CORRECCIÓN V5: Adiós std::function.
ListenerResult geode::IVSettingFilter::handle(geode::utils::MiniFunction<Callback> fn, IVSettingEvent* event) {
    // Evaluamos si el tipo coincide
    if (m_type && m_type.value() != event->getType()) return ListenerResult::Propagate;

    // Ejecutamos la función
    fn(event->getType());
    return ListenerResult::Propagate;
}

GEODE_NS_IV_END
