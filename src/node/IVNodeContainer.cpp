#include "IVNodeContainer.hpp"

using namespace geode::prelude;

GEODE_NS_IV_BEGIN

IVNodeContainer::IVNodeContainer() {}

IVNodeContainer* IVNodeContainer::create() {
    auto ret = new (std::nothrow) IVNodeContainer();
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool IVNodeContainer::init() {
    if (!IVNodeBase::init())
        return false;

    return true;
}

void IVNodeContainer::addNode(IVNodeBase* node) {
    if (!node) return;
    this->addChild(node);
}

void IVNodeContainer::refreshAppearance() {
    // Refresh appearance for all children
    CCArray* children = this->getChildren();
    if (!children) return;

    CCObject* obj;
    CCARRAY_FOREACH(children, obj) {
        auto child = dynamic_cast<IVNodeBase*>(obj);
        if (child) {
            child->refreshAppearance();
        }
    }
}

GEODE_NS_IV_END
