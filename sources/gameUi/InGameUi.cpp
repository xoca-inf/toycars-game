#include "Settings/ResourceLibary.h"
#include "InGameUi.h"

void InGameUi::initContent() {
    auto mainRect = getRect();

    auto m_contentRect = make::sptr<UiRect>(Offset(0.0, OffsetType::PERCENT, PivotAt::LEFT),
                                          Offset(0.0, OffsetType::PERCENT, PivotAt::RIGHT),
                                          Offset(0.0, OffsetType::PERCENT, PivotAt::TOP),
                                          Offset(0.0, OffsetType::PERCENT, PivotAt::BOTTOM));
    mainRect->addChild(m_contentRect);

    //KeyButton button
    createItem(
            m_contentRect,
            "Button",
            Offset(9 / 15., OffsetType::PERCENT, PivotAt::LEFT),
            Offset(2 / 15., OffsetType::PERCENT, PivotAt::RIGHT),
            Offset(9 / 15., OffsetType::PERCENT, PivotAt::TOP),
            Offset(2 / 15., OffsetType::PERCENT, PivotAt::BOTTOM),
            ResourceLibary::instance().getTexturePath("KeyTexture"),
            1.0);
    auto rect = m_contentRect->findChild("Button");
    rect->setFill(FillType::FIT_HORIZONTAL, 3./2.);
    auto item = getItem("Button");
    item->setClickCallback([this](){
        if(m_keyPressedCallback && !m_isKeyPressed) {
            m_keyPressedCallback();
            m_isKeyPressed = true;
            Timer::addTask(0.5, [this](){switchKeyToCanister(); return true;});
        }
    });
    item->setClickable(true);
}

void InGameUi::switchKeyToCanister() {
    //CanisterButton button
    auto item = getItem("Button");
    auto mat = item->getMaterial();
    mat->setTexture(TextureId::TEXTURE_0, ResourceLibary::instance().getTexture("FuelFull"));
    item->setMaterial(mat);
    item->setClickCallback([this](){
        if(m_canisterPressedCallback) m_canisterPressedCallback();
    });
    item->setClickable(true);
}
