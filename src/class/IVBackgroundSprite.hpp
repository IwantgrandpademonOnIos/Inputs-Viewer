#pragma once

#include <Geode/Geode.hpp>
#include <Geode/modify/CCNode.hpp>
#include <Geode/utils/cocos.hpp>

#include <vector>

GEODE_NS_IV_BEGIN

class BackgroundSprite : public cocos2d::CCNode {
public:
    BackgroundSprite();
    BackgroundSprite(ccColor4B const& backgroundColor,
                     ccColor4B const& outlineColor,
                     ccColor4B const& textColor);

    static BackgroundSprite* create();

    bool init() override;

    void setContentSize(CCSize const& size) override;

    void setBackgroundColor(ccColor4B const& color);
    void setOutlineColor(ccColor4B const& color);
    void setTextColor(ccColor4B const& color);

    void addBackgroundNode(cocos2d::CCNode* node);
    void addOutlineNode(cocos2d::CCNode* node);
    void addTextNode(cocos2d::CCNode* node);

    void removeBackgroundNode(cocos2d::CCNode* node);
    void removeOutlineNode(cocos2d::CCNode* node);
    void removeTextNode(cocos2d::CCNode* node);

private:
    void updateBackgroundColorNodes();
    void updateOutlineColorNodes();
    void updateTextColorNodes();

    cocos2d::CCScale9Sprite* m_fill = nullptr;
    cocos2d::CCScale9Sprite* m_outline = nullptr;

    ccColor4B m_backgroundColor;
    ccColor4B m_outlineColor;
    ccColor4B m_textColor;

    // Replaced CCArrayExt with std::vector
    std::vector<cocos2d::CCNode*> m_backgroundColorNodes;
    std::vector<cocos2d::CCNode*> m_outlineColorNodes;
    std::vector<cocos2d::CCNode*> m_textColorNodes;
    std::vector<cocos2d::CCNode*> m_tColorNodes;
};

GEODE_NS_IV_END
