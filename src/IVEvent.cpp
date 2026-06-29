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

IVSettingFilter::IVSettingFilter(std::nullopt_t)
    : IVSettingFilter() {}

IVSettingFilter::IVSettingFilter(SettingEventType type)
    : m_type(type) {}

// CORRECCIÓN: Geode 5 uses geode::Function instead of MiniFunction.
ListenerResult IVSettingFilter::handle(geode::Function<Callback> fn, IVSettingEvent* event) {
    // Si el tipo no coincide, propagamos sin ejecutar
    if (m_type && m_type.value() != event->getType())
        return ListenerResult::Propagate;

    // Ejecutamos la función con el tipo del evento
    fn(event->getType());
    return ListenerResult::Propagate;
}

GEODE_NS_IV_END
