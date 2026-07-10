#include "node/IVNodeBase.hpp"

using namespace geode::prelude;

GEODE_NS_IV_BEGIN

IVNodeBase::IVNodeBase() {}

bool IVNodeBase::init() {
    return CCNode::init();
}

GEODE_NS_IV_END
