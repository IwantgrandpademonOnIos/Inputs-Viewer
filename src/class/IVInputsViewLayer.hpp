#pragma once
#include <Geode/Geode.hpp>
#include "IVPlayerInputNode.hpp"
#include "IVNodeContainer.hpp"

GEODE_NS_IV_BEGIN

class IVInputsViewerLayer : public cocos2d::CCLayer {
public:
    IVInputsViewerLayer();
    static IVInputsViewerLayer* create();

    bool init() override;

    // Called every frame to update input states
    void update(float dt) override;

    // Add an input node to the viewer
    void addInputNode(IVPlayerInputNode* node);

protected:
    IVNodeContainer* m_container = nullptr;
};

GEODE_NS_IV_END
