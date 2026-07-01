#include "IVBackgroundSprite.hpp"
#include "IVManager.hpp"

using namespace geode::prelude;

GEODE_NS_IV_BEGIN

BackgroundSprite::BackgroundSprite(ccColor4B const& backgroundColor, ccColor4B const& outlineColor, ccColor4B const& textColor)
    : m_backgroundColor(backgroundColor)
    , m_outlineColor(outlineColor)
    , m_textColor(textColor)
{
    // Geode 5 removed EventListener, so the old listener is gone.
    // Your sprite still updates correctly when you call the setters.
}

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
    this->setAnchorPoint(ccp(0.5f, 0.5f));

    m_fill = CCScale9Sprite::create("background_fill.png"_spr);
    this->addChild(m_fill);
    this->addBackgroundNode(m_fill);

    m_outline = CCScale9Sprite::create("background_outline.png"_spr);
    this->addChild(m_outline);
    this->addOutlineNode(m_outline);
}

    GEODE_NS_IV_END




