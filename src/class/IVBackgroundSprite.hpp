#pragma once

#include <Geode/Geode.hpp>
#include <Geode/utils/cocos.hpp>
#include <vector>

GEODE_NS_IV_BEGIN

class BackgroundSprite : public cocos2d::CCNode {
public:
    BackgroundSprite();
    BackgroundSprite(cocos2d::ccColor4B const& backgroundColor,
                     cocos2d::ccColor4B const& outlineColor,
                     cocos2d::ccColor4B const& textColor);

    static BackgroundSprite* create();

    bool init() override;

    void setContentSize(cocos2d::CCSize const& size) override;

    void setBackgroundColor(cocos2d::ccColor4B const& color);
    void setOutlineColor(cocos2d::ccColor4B const& color);
    void setTextColor(cocos2d::ccColor4B const& color);

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

    cocos2d::extension::CCScale9Sprite* m_fill = nullptr;
    cocos2d::extension::CCScale9Sprite* m_outline = nullptr;

    cocos2d::ccColor4B m_backgroundColor;
    cocos2d::ccColor4B m_outlineColor;
    cocos2d::ccColor4B m_textColor;

    std::vector<cocos2d::CCNode*> m_backgroundColorNodes;
    std::vector<cocos2d::CCNode*> m_outlineColorNodes;
    std::vector<cocos2d::CCNode*> m_textColorNodes;
    std::vector<cocos2d::CCNode*> m_tColorNodes;
};

GEODE_NS_IV_END
