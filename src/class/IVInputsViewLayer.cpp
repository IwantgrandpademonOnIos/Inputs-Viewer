#include "IVInputsViewerLayer.hpp"

using namespace geode::prelude;

GEODE_NS_IV_BEGIN

IVInputsViewerLayer::IVInputsViewerLayer() {}

IVInputsViewerLayer* IVInputsViewerLayer::create() {
    auto ret = new (std::nothrow) IVInputsViewerLayer();
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool IVInputsViewerLayer::init() {
    if (!CCLayer::init())
        return false;

    m_container = IVNodeContainer::create();
    this->addChild(m_container);

    this->scheduleUpdate();
    return true;
}

void IVInputsViewerLayer::addInputNode(IVPlayerInputNode* node) {
    if (m_container && node) {
        m_container->addNode(node);
    }
}

void IVInputsViewerLayer::update(float dt) {
    // Example input polling (replace with actual GD input hooks)
    bool jumpPressed = cocos2d::CCKeyboardDispatcher::get()->getShiftKeyPressed();

    // Update all children
    auto children = m_container->getChildren();
    if (!children) return;

    CCObject* obj;
    CCARRAY_FOREACH(children, obj) {
        auto inputNode = dynamic_cast<IVPlayerInputNode*>(obj);
        if (inputNode) {
            inputNode->updateInputState(jumpPressed);
        }
    }
}

GEODE_NS_IV_END
