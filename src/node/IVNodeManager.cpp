#include "node/IVNodeManager.hpp"

using namespace geode::prelude;

GEODE_NS_IV_BEGIN

IVNodeManager* IVNodeManager::s_instance = nullptr;

IVNodeManager::IVNodeManager() {
    m_nodes = CCArray::create();
    m_nodes->retain();
}

IVNodeManager* IVNodeManager::get() {
    if (!s_instance) {
        s_instance = new IVNodeManager();
        s_instance->autorelease();
    }
    return s_instance;
}

IVPlayerInputNode* IVNodeManager::createInputNode(IVInputType type) {
    auto node = IVPlayerInputNode::create(type);
    if (node) {
        m_nodes->addObject(node);
    }
    return node;
}

GEODE_NS_IV_END
