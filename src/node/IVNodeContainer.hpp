#pragma once
#include "node/IVNodeBase.hpp"

GEODE_NS_IV_BEGIN

class IVNodeContainer : public IVNodeBase {
public:
    IVNodeContainer();
    static IVNodeContainer* create();

    bool init() override;

    // Add a child node with layout support
    void addNode(IVNodeBase* node);

    // Refresh appearance for all children
    void refreshAppearance() override;
};

GEODE_NS_IV_END
