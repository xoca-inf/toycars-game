#pragma once
#include "W4Framework.h"
#include "Components/UiLayoutComponent.h"
#include "Components/Inventory.h"

W4_USE_UNSTRICT_INTERFACE

class ShopComponent : public IComponent{
W4_COMPONENT(ShopComponent, IComponent)
public:
    ShopComponent(CloneTag, const ShopComponent& from, Node& owner)
            : Super(CloneTag{}, from, owner)
    {
    }
    void buyFuel();
    void buyEngine();
    void buyScoreBoost();

    void initialize(const variant::Variant& data) override;
    void update(float dt) override;
    void finalize() override;
    ~ShopComponent() override;

    void setup(sptr<Node> scoreNode, UiLayoutComponent& ui);
    void updateScores();
private:

    void buyItem(int& price, const std::function<void(int newPrice)>&);
    int m_moneyCount;
    int m_itemMultiply;
    int m_fuelPrice;
    int m_enginePrice;
    int m_scorePrice;
    sptr<LayoutLabel> m_MoneyLabel;
    sptr<LayoutLabel> m_FuelPriceLabel;
    sptr<LayoutLabel> m_EnginePriceLabel;
    sptr<LayoutLabel> m_ScorePriceLabel;
    sptr<Node> m_scoreNode;
};
