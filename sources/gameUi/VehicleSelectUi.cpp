#include <Components/Inventory.h>
#include "VehicleSelectUi.h"
#include "Settings/ResourceLibary.h"

void VehicleSelectUi::initContent() {
    auto mainRect = getRect();

    auto contentRect = make::sptr<UiRect>(Offset(0.0, OffsetType::PERCENT, PivotAt::LEFT),
                                          Offset(0.0, OffsetType::PERCENT, PivotAt::RIGHT),
                                          Offset(0.0, OffsetType::PERCENT, PivotAt::TOP),
                                          Offset(0.0, OffsetType::PERCENT, PivotAt::BOTTOM));
    mainRect->addChild(contentRect);

    //Play button
    createItem(
            contentRect,
            "Play",
            Offset(5.5 / 15., OffsetType::PERCENT, PivotAt::LEFT),
            Offset(5.5 / 15., OffsetType::PERCENT, PivotAt::RIGHT),
            Offset(12 / 15., OffsetType::PERCENT, PivotAt::TOP),
            Offset(1 / 15., OffsetType::PERCENT, PivotAt::BOTTOM),
            ResourceLibary::instance().getTexturePath("PlayTexture"),
            1.0);
    auto rect = contentRect->findChild("Play");
    rect->setFill(FillType::FIT_HORIZONTAL, 3./2.);
    auto item = getItem("Play");
    item->setClickCallback([this](){
        if(m_playPressedCallback) m_playPressedCallback();
    });
    item->setClickable(true);

    auto WideRect = make::sptr<UiRect>(Offset(-0.5, OffsetType::PERCENT, PivotAt::LEFT),
                                       Offset(-0.5, OffsetType::PERCENT, PivotAt::RIGHT),
                                       Offset(0, OffsetType::PERCENT, PivotAt::TOP),
                                       Offset(0, OffsetType::PERCENT, PivotAt::BOTTOM));
    contentRect->addChild(WideRect);

    auto file = w4::filesystem::open("carResources.json");
    auto json = nlohmann::json::parse(file->data(), file->data() + file->size());
    int carId = 0;
    std::vector<sptr<UiRect>> buttons;
    std::vector<sptr<Image3d>> carButtons;

    for (auto &car : json["Cars"]) {
        createItem(
                WideRect,
                "CarButton" + std::to_string('0' + carId),
                Offset(carId * 0.2f, OffsetType::PERCENT, PivotAt::LEFT),
                Offset((carId + 1) * 0.2f, OffsetType::PERCENT, PivotAt::LEFT),
                Offset(0, OffsetType::PERCENT, PivotAt::TOP),
                Offset(0, OffsetType::PERCENT, PivotAt::BOTTOM),
                ResourceLibary::instance().getTexturePath("CarButton"),
                1.0);
        buttons.push_back(contentRect->findChild("CarButton" + std::to_string('0' + carId)));
        buttons[carId]->setFill(FillType::FIT_HORIZONTAL, 4./2.);

        createItem(
                buttons[carId],
                json["Cars"][carId]["name"].get<std::string>(),
                Offset( 0.2f, OffsetType::PERCENT, PivotAt::LEFT),
                Offset(0.2f, OffsetType::PERCENT, PivotAt::RIGHT),
                Offset(0, OffsetType::PERCENT, PivotAt::TOP),
                Offset(0, OffsetType::PERCENT, PivotAt::BOTTOM),
                ResourceLibary::instance().getTexturePath(json["Cars"][carId]["name"].get<std::string>() + "Texture"),
                3.0);
        rect = contentRect->findChild(json["Cars"][carId]["name"].get<std::string>());
        rect->setFill(FillType::FIT_HORIZONTAL, 3./2.);
        carButtons.push_back(getItem(json["Cars"][carId]["name"].get<std::string>()));
        carButtons[carId]->setClickCallback([this, carId, &WideRect](){
            if(m_setCar) {
                m_setCar(carId);
            }
        });
        carButtons[carId]->setClickable(true);

        carId++;
    }
}
