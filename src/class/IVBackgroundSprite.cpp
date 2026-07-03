#include "IVBackgroundSprite.hpp"
#include "IVManager.hpp"

using namespace geode::prelude;

GEODE_NS_IV_BEGIN

BackgroundSprite::BackgroundSprite(
    cocos2d::ccColor4B const& backgroundColor,
    cocos2d::ccColor4B const& outlineColor,
    cocos2d::ccColor4B const& textColor
)
    : m_backgroundColor(backgroundColor)
    , m_outlineColor(outlineColor)
    , m_textColor(textColor)
{}

BackgroundSprite::BackgroundSprite()
    : BackgroundSprite(
        IVManager::get().m_backgroundReleaseColor,
        IVManager::get().m_outlineReleaseColor,
        IVManager::get().m_textReleaseColor
    )
{}

BackgroundSprite* BackgroundSprite::create(
    cocos2d::ccColor4B const& backgroundColor,
    cocos2d::ccColor4B const& outlineColor,
    cocos2d::ccColor4B const& textColor
) {
    auto ret = new (std::nothrow) BackgroundSprite(backgroundColor, outlineColor, textColor);
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

BackgroundSprite* BackgroundSprite::create() {
    auto ret = new (std::nothrow) BackgroundSprite;
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool BackgroundSprite::init() {
    if (!CCNode::init()) return false;
    this->setAnchorPoint(ccp(0.5f, 0.5f));

    m_fill = CCScale9Sprite::create("background_fill.png"_spr);
    this->addChild(m_fill);
    addBackgroundNode(m_fill);

    m_outline = CCScale9Sprite::create("background_outline.png"_spr);
    this->addChild(m_outline);
    addOutlineNode(m_outline);

    updateBackgroundColorNodes();
    updateOutlineColorNodes();
    updateTextColorNodes();

    return true;
}

void BackgroundSprite::addBackgroundNode(cocos2d::CCNode* node) {
    if (!node) return;
    m_backgroundColorNodes.addObject(node);
    m_shouldUpdateLayout = true;
}

void BackgroundSprite::addOutlineNode(cocos2d::CCNode* node) {
    if (!node) return;
    m_outlineColorNodes.addObject(node);
    m_shouldUpdateLayout = true;
}

void BackgroundSprite::addTextNode(cocos2d::CCNode* node) {
    if (!node) return;
    m_textColorNodes.addObject(node);
    m_shouldUpdateLayout = true;
}

void BackgroundSprite::removeBackgroundNode(cocos2d::CCNode* node) {
    if (!node) return;
    m_backgroundColorNodes.removeObject(node);
    m_shouldUpdateLayout = true;
}

void BackgroundSprite::removeOutlineNode(cocos2d::CCNode* node) {
    if (!node) return;
    m_outlineColorNodes.removeObject(node);
    m_shouldUpdateLayout = true;
}

void BackgroundSprite::removeTextNode(cocos2d::CCNode* node) {
    if (!node) return;
    m_textColorNodes.removeObject(node);
    m_shouldUpdateLayout = true;
}

void BackgroundSprite::setBackgroundColor(cocos2d::ccColor4B const& color) {
    m_backgroundColor = color;
    updateBackgroundColorNodes();
}

void BackgroundSprite::setOutlineColor(cocos2d::ccColor4B const& color) {
    m_outlineColor = color;
    updateOutlineColorNodes();
}

void BackgroundSprite::setTextColor(cocos2d::ccColor4B const& color) {
    m_textColor = color;
    updateTextColorNodes();
}

void BackgroundSprite::setContentSize(cocos2d::CCSize const& size) {
    CCNode::setContentSize(size);
    if (m_fill) {
        m_fill->setContentSize(size);
    }
    if (m_outline) {
        m_outline->setContentSize(size);
    }
    m_shouldUpdateLayout = true;
}

void BackgroundSprite::visit() {
    if (m_shouldUpdateLayout) {
        updateBackgroundColorNodes();
        updateOutlineColorNodes();
        updateTextColorNodes();
        m_shouldUpdateLayout = false;
    }
    CCNode::visit();
}

void BackgroundSprite::updateBackgroundColorNodes() {
    for (auto node : m_backgroundColorNodes) {
        if (auto sprite = typeinfo_cast<CCSprite*>(node)) {
            sprite->setColor({ m_backgroundColor.get().r, m_backgroundColor.get().g, m_backgroundColor.get().b });
            sprite->setOpacity(m_backgroundColor.get().a);
        }
    }
    if (m_fill) {
        m_fill->setColor({ m_backgroundColor.get().r, m_backgroundColor.get().g, m_backgroundColor.get().b });
        m_fill->setOpacity(m_backgroundColor.get().a);
    }
}

void BackgroundSprite::updateOutlineColorNodes() {
    for (auto node : m_outlineColorNodes) {
        if (auto sprite = typeinfo_cast<CCSprite*>(node)) {
            sprite->setColor({ m_outlineColor.get().r, m_outlineColor.get().g, m_outlineColor.get().b });
            sprite->setOpacity(m_outlineColor.get().a);
        }
    }
    if (m_outline) {
        m_outline->setColor({ m_outlineColor.get().r, m_outlineColor.get().g, m_outlineColor.get().b });
        m_outline->setOpacity(m_outlineColor.get().a);
    }
}

void BackgroundSprite::updateTextColorNodes() {
    for (auto node : m_textColorNodes) {
        if (auto label = typeinfo_cast<CCLabelBMFont*>(node)) {
            label->setColor({ m_textColor.get().r, m_textColor.get().g, m_textColor.get().b });
            label->setOpacity(m_textColor.get().a);
        }
    }
}

GEODE_NS_IV_END
