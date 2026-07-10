#include "node/IVPlayerInputNode.hpp"

using namespace geode::prelude;

GEODE_NS_IV_BEGIN

IVPlayerInputNode::IVPlayerInputNode() {}

IVPlayerInputNode* IVPlayerInputNode::create(IVInputType type) {
    auto ret = new (std::nothrow) IVPlayerInputNode();
    if (ret && ret->init(type)) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool IVPlayerInputNode::init(IVInputType type) {
    if (!IVNodeInput::init(type))
        return false;

    m_currentPressed = false;
    refreshAppearance();
    return true;
}

void IVPlayerInputNode::updateInputState(bool pressed) {
    m_currentPressed = pressed;
    this->setPressed(pressed);
    refreshAppearance();
}

void IVPlayerInputNode::refreshAppearance() {
    IVNodeInput::refreshAppearance();
}

GEODE_NS_IV_END
