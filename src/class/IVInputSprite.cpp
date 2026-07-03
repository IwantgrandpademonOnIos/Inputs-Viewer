#include "IVInputSprite.hpp"
#include "IVPlayerInputNode.hpp"
#include <IVConstants.hpp>

using namespace geode::prelude;

GEODE_NS_IV_BEGIN

InputSprite::InputSprite() {}

InputSprite* InputSprite::create(PlayerInputNode* inputNode, PlayerButton button, char const* playerText) {
    auto ret = new (std::nothrow) InputSprite();
    if (ret && ret->init(inputNode, button, playerText)) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool InputSprite::init(PlayerInputNode* inputNode, PlayerButton button, char const* playerText) {
    if (!BackgroundSprite::init())
        return false;

    m_inputNode = inputNode;
    m_currentCPSCalculation = CPSCalculation::RealTime;

    // Input symbol (Jump / Left / Right)
    m_inputSymbol = CCSprite::createWithSpriteFrameName(constants::getButtonSprite(button));
    m_inputSymbol->setScale(0.75f);
    this->addChild(m_inputSymbol);

    // Player text (P1 / P2)
    if (playerText) {
        m_playerText = CCLabelBMFont::create(playerText, "chatFont.fnt");
        m_playerText->setScale(m_textScale);
        this->addChild(m_playerText);
    }

    // Total inputs counter
    m_totalInputsText = CCLabelBMFont::create("0", "chatFont.fnt");
    m_totalInputsText->setScale(m_textScale);
    m_totalInputsText->setVisible(false);
    this->addChild(m_totalInputsText);

    // CPS counter
    m_cpsText = CCLabelBMFont::create("0", "chatFont.fnt");
    m_cpsText->setScale(m_textScale);
    m_cpsText->setVisible(false);
    this->addChild(m_cpsText);

    // CPS update scheduling
    this->schedule(schedule_selector(InputSprite::cpsSchedule), 0.1f);

    return true;
}

void InputSprite::press(bool pressed, bool updateCounters) {
    if (pressed) {
        m_totalInputs++;
        m_clicksPerSecond++;

        if (updateCounters) {
            m_shouldUpdateTotalInputsDisplay = true;
            m_shouldUpdateCPSDisplay = true;
        }
    }

    // Visual feedback
    this->setOpacity(pressed ? 180 : 255);
}

void InputSprite::setShowTotalInputs(bool show) {
    m_totalInputsText->setVisible(show);
}

void InputSprite::setShowCPS(bool show) {
    m_cpsText->setVisible(show);
}

void InputSprite::setCPSMode(CPSCalculation mode) {
    m_currentCPSCalculation = mode;
}

void InputSprite::setMinimal(bool minimal) {
    if (minimal) {
        if (m_playerText) m_playerText->setVisible(false);
        m_totalInputsText->setVisible(false);
        m_cpsText->setVisible(false);
    } else {
        if (m_playerText) m_playerText->setVisible(true);
    }
}

void InputSprite::updateButtonAppearance() {
    // Update label widths to avoid clipping
    if (m_playerText) updateLabelWidth(m_playerText);
    updateLabelWidth(m_totalInputsText);
    updateLabelWidth(m_cpsText);
}

void InputSprite::onSettingChange(SettingEventType type) {
    if (type == SettingEventType::KeyAppearance)
        updateButtonAppearance();
}

void InputSprite::visit() {
    BackgroundSprite::visit();

    if (m_shouldUpdateTotalInputsDisplay)
        updateTotalInputsDisplay();

    if (m_shouldUpdateCPSDisplay)
        updateCPSDisplay();
}

void InputSprite::updateTotalInputsDisplay() {
    m_totalInputsText->setString(std::to_string(m_totalInputs).c_str());
    m_shouldUpdateTotalInputsDisplay = false;
}

void InputSprite::updateCPSDisplay() {
    m_cpsText->setString(std::to_string(m_displayedCPS).c_str());
    m_shouldUpdateCPSDisplay = false;
}

void InputSprite::cpsSchedule(float dt) {
    if (m_currentCPSCalculation == CPSCalculation::RealTime) {
        m_displayedCPS = m_clicksPerSecond;
        m_clicksPerSecond = 0;
    } else {
        subtractCPS();
    }

    m_shouldUpdateCPSDisplay = true;
}

void InputSprite::subtractCPS() {
    if (m_clicksPerSecond > 0)
        m_clicksPerSecond--;
    m_displayedCPS = m_clicksPerSecond;
}

void InputSprite::updateLabelWidth(CCLabelBMFont* font) {
    if (!font) return;

    float width = font->getContentSize().width;
    if (width > constants::buttonWidth)
        font->setScale(constants::buttonWidth / width * m_textScale);
}

GEODE_NS_IV_END
