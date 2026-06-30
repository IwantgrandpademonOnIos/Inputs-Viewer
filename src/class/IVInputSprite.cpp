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

{
GEODE_NS_IV_END
