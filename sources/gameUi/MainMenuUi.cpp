#include "MainMenuUi.h"
#include "Settings/ResourceLibary.h"

void MainMenuUi::initContent() {
    auto mainRect = getRect();

    auto contentRect = make::sptr<UiRect>(Offset(0.0, OffsetType::PERCENT, PivotAt::LEFT),
                                          Offset(0.0, OffsetType::PERCENT, PivotAt::RIGHT),
                                          Offset(0.0, OffsetType::PERCENT, PivotAt::TOP),
                                          Offset(0.0, OffsetType::PERCENT, PivotAt::BOTTOM));
    mainRect->addChild(contentRect);

    //Coin window
    createItem(
            contentRect,
            "CoinWindow",
            Offset(0.4, OffsetType::PERCENT, PivotAt::LEFT),
            Offset(0.4, OffsetType::PERCENT, PivotAt::RIGHT),
            Offset(0.1, OffsetType::PERCENT, PivotAt::TOP),
            Offset(0.8, OffsetType::PERCENT, PivotAt::BOTTOM),
            ResourceLibary::instance().getTexturePath("CoinWindow"),
            1.0);
    auto rect = contentRect->findChild("CoinWindow");
    rect->setFill(FillType::FIT_HORIZONTAL, 5./1.);

    //Play button
    createItem(
            contentRect,
            "Play",
            Offset(4 / 15., OffsetType::PERCENT, PivotAt::LEFT),
            Offset(4 / 15., OffsetType::PERCENT, PivotAt::RIGHT),
            Offset(8.3 / 15., OffsetType::PERCENT, PivotAt::TOP),
            Offset(1.5 / 15., OffsetType::PERCENT, PivotAt::BOTTOM),
            ResourceLibary::instance().getTexturePath("PlayTexture"),
            1.0);
    rect = contentRect->findChild("Play");
    rect->setFill(FillType::FIT_HORIZONTAL, 3./1.2);
    auto item = getItem("Play");
    item->setClickCallback([this](){
        if(m_playPressedCallback) m_playPressedCallback();
    });
    item->setClickable(true);

    //Settings button
    createItem(
            contentRect,
            "Settings",
            Offset(12 / 15., OffsetType::PERCENT, PivotAt::LEFT),
            Offset(-0.01f, OffsetType::PERCENT, PivotAt::RIGHT),
            Offset(3 / 15., OffsetType::PERCENT, PivotAt::TOP),
            Offset(7 / 15., OffsetType::PERCENT, PivotAt::BOTTOM),
            ResourceLibary::instance().getTexturePath("SettingsTexture"),
            1.0);
    rect = contentRect->findChild("Settings");
    rect->setFill(FillType::FIT_HORIZONTAL, 3./1.6);
    item = getItem("Settings");
    item->setClickCallback([this](){
        if(m_settingsPressedCallback) m_settingsPressedCallback();
    });
    item->setClickable(true);

    //Highscores button
    createItem(
            contentRect,
            "Highscores",
            Offset(12 / 15., OffsetType::PERCENT, PivotAt::LEFT),
            Offset(-0.01f, OffsetType::PERCENT, PivotAt::RIGHT),
            Offset(5.5 / 15., OffsetType::PERCENT, PivotAt::TOP),
            Offset(5.5 / 15., OffsetType::PERCENT, PivotAt::BOTTOM),
            ResourceLibary::instance().getTexturePath("HighScoresTexture"),
            1.0);
    rect = contentRect->findChild("Highscores");
    rect->setFill(FillType::FIT_HORIZONTAL, 3./1.6);
    item = getItem("Highscores");
    item->setClickCallback([this](){
        if(m_highscoresPressedCallback) m_highscoresPressedCallback();
    });
    item->setClickable(true);

    //Shop button
    createItem(
            contentRect,
            "Shop",
            Offset(12 / 15., OffsetType::PERCENT, PivotAt::LEFT),
            Offset(-0.01f, OffsetType::PERCENT, PivotAt::RIGHT),
            Offset(7 / 15., OffsetType::PERCENT, PivotAt::TOP),
            Offset(3 / 15., OffsetType::PERCENT, PivotAt::BOTTOM),
            ResourceLibary::instance().getTexturePath("ShopTexture"),
            1.0);
    rect = contentRect->findChild("Shop");
    rect->setFill(FillType::FIT_HORIZONTAL, 3./1.6);
    item = getItem("Shop");
    item->setClickCallback([this](){
        if(m_shopPressedCallback) m_shopPressedCallback();
    });
    item->setClickable(true);
}
