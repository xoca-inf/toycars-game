#include "CoinsPanelUi.h"

#include <string>

void CoinsPanelUi::initContent() {

    auto mainRect = getRect();

    auto contentRect = make::sptr<UiRect>(Offset(0.0, OffsetType::PERCENT, PivotAt::LEFT),
                                          Offset(0.0, OffsetType::PERCENT, PivotAt::RIGHT),
                                          Offset(0.0, OffsetType::PERCENT, PivotAt::TOP),
                                          Offset(0.0, OffsetType::PERCENT, PivotAt::BOTTOM));
    mainRect->addChild(contentRect);


    m_label = createLabel(
            contentRect,
            "label",
            Offset(0.4, OffsetType::PERCENT, PivotAt::LEFT),
            Offset(0.4, OffsetType::PERCENT, PivotAt::RIGHT),
            Offset(0.1, OffsetType::PERCENT, PivotAt::TOP),
            Offset(0.8, OffsetType::PERCENT, PivotAt::BOTTOM),
            0.0);
    m_label->setText("Text");
    m_label->setBold(true);
    m_label->setBgColor(color::zero);
    m_label->setTextAlign(HorizontalAlign::Center, VerticalAlign::Center);
 }

void CoinsPanelUi::setCoins(int coins) {
    m_label->setText(std::to_string(coins));
}
