#include "IVBackgroundSprite.hpp"
#include "IVManager.hpp"

using namespace geode::prelude;

GEODE_NS_IV_BEGIN

BackgroundSprite::BackgroundSprite(ccColor4B const& backgroundColor,
                                   ccColor4B const& outlineColor,
                                   ccColor4B const& textColor)
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
    this->setAnchorPoint({0.5f, 0.5f});

    m_fill = CCScale9Sprite::create("background_fill.png"_spr);
    this->addChild(m_fill);
    this->addBackgroundNode(m_fill);

    m_outline = CCScale9Sprite::create("background_outline.png"_spr);
    this->addChild(m_outline);
    this->addOutlineNode(m_outline);

    this->setContentSize(m_outline->getContentSize());
    return true;
}

void BackgroundSprite::setContentSize(CCSize const& size) {
    CCNode::setContentSize(size);
}

void BackgroundSprite::setBackgroundColor(ccColor4B const& color) {
    m_backgroundColor = color;
    this->updateBackgroundColorNodes();
}

void BackgroundSprite::setOutlineColor(ccColor4B const& color) {
    m_outlineColor = color;
    this->updateOutlineColorNodes();
}

void BackgroundSprite::setTextColor(ccColor4B const& color) {
    m_textColor = color;
    this->updateTextColorNodes();
}

void BackgroundSprite::addBackgroundNode(CCNode* node) {
    if (auto protocol = typeinfo_cast<CCRGBAProtocol*>(node)) {
        protocol->setColor(m_backgroundColor);
        m_backgroundColorNodes.push_back(node);
    }
}

void BackgroundSprite::addOutlineNode(CCNode* node) {
    if (auto protocol = typeinfo_cast<CCRGBAProtocol*>(node)) {
        protocol->setColor(m_outlineColor);
        m_outlineColorNodes.push_back(node);
    }
}

void BackgroundSprite::addTextNode(CCNode* node) {
    if (auto protocol = typeinfo_cast<CCRGBAProtocol*>(node)) {
        protocol->setColor(m_textColor);
        m_textColorNodes.push_back(node);
    }
}

void BackgroundSprite::removeBackgroundNode(CCNode* node) {
    m_backgroundColorNodes.erase(
        std::remove(m_backgroundColorNodes.begin(), m_backgroundColorNodes.end(), node),
        m_backgroundColorNodes.end()
    );
}

void BackgroundSprite::removeOutlineNode(CCNode* node) {
    m_outlineColorNodes.erase(
        std::remove(m_outlineColorNodes.begin(), m_outlineColorNodes.end(), node),
        m_outlineColorNodes.end()
    );
}

void BackgroundSprite::removeTextNode(CCNode* node) {
    m_textColorNodes.erase(
        std::remove(m_textColorNodes.begin(), m_textColorNodes.end(), node),
        m_textColorNodes.end()
    );
}

void BackgroundSprite::updateBackgroundColorNodes() {
    for (auto node : m_backgroundColorNodes) {
        if (auto protocol = typeinfo_cast<CCRGBAProtocol*>(node)) {
            protocol->setColor(m_backgroundColor);
        }
    }
}

void BackgroundSprite::updateOutlineColorNodes() {
    for (auto node : m_outlineColorNodes) {
        if (auto protocol = typeinfo_cast<CCRGBAProtocol*>(node)) {
            protocol->setColor(m_outlineColor);
        }
    }
}

void BackgroundSprite::updateTextColorNodes() {
    for (auto node : m_textColorNodes) {
        if (auto protocol = typeinfo_cast<CCRGBAProtocol*>(node)) {
            protocol->setColor(m_textColor);
        }
    }
}

GEODE_NS_IV_END
