#pragma once
#include <Geode/Geode.hpp>
#include "node/IVPlayerInputNode.hpp"
#include "node/IVNodeContainer.hpp"

GEODE_NS_IV_BEGIN

class IVNodeManager : public cocos2d::CCNode {
public:
    IVNodeManager();
    static IVNodeManager* get();

    IVPlayerInputNode* createInputNode(IVInputType type);

    cocos2d::CCArray* getNodes() const { return m_nodes; }

protected:
    cocos2d::CCArray* m_nodes = nullptr;

    static IVNodeManager* s_instance;
};

GEODE_NS_IV_END
