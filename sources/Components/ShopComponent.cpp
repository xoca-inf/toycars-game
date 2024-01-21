#include "ShopComponent.h"
#include "Settings/Settings.h"


void ShopComponent::initialize(const variant::Variant& data) {
    Super::initialize(data);
    W4_LOG_DEBUG("[Inventory] INITIALIZE");
}

void ShopComponent::setup(sptr<Node> scoreNode,UiLayoutComponent& ui){
    m_itemMultiply = Settings::instance().getFloat("itemMultiply");
    m_scorePrice = Settings::instance().getFloat("scoreBoostPrice");
    m_enginePrice = Settings::instance().getFloat("enginePrice");
    m_fuelPrice = Settings::instance().getFloat("fuelPrice");
    m_FuelPriceLabel = ui.getLabel("FuelPrice");
    m_EnginePriceLabel = ui.getLabel("EnginePrice");
    m_ScorePriceLabel = ui.getLabel("ScorePrice");
    m_MoneyLabel = ui.getLabel("Score");
    m_FuelPriceLabel->m_label->setText(std::to_string(m_enginePrice));
    m_EnginePriceLabel->m_label->setText(std::to_string(m_fuelPrice));
    m_ScorePriceLabel->m_label->setText(std::to_string(m_scorePrice));
    m_scoreNode = scoreNode;
}

void ShopComponent::updateScores(){
    m_MoneyLabel->m_label->setText("Points: " + std::to_string(Inventory::instance().getPoints()));
}

void ShopComponent::buyItem(int &price, const std::function<void(int newPrice)>& onBought) {
    if(Inventory::instance().getPoints() >= price){
        Inventory::instance().spendPoints(price);
        price *= m_itemMultiply;
        m_MoneyLabel->m_label->setText("Points: " + std::to_string(Inventory::instance().getPoints()));
        onBought(price);
    }
}

void ShopComponent::buyFuel(){
    buyItem(m_fuelPrice, [this](int price){
        //update fuel price here
        Inventory::instance().incCanisterLVL();
        m_FuelPriceLabel->m_label->setText(std::to_string(price));
        W4_LOG_DEBUG("fuel price now: %f, money count = %f", price, m_moneyCount);
    });
}

void ShopComponent::buyEngine() {
    buyItem(m_enginePrice, [this](int price){
        //update engine price here
        Inventory::instance().incEngineLVL();
        m_EnginePriceLabel->m_label->setText(std::to_string(price));
        W4_LOG_DEBUG("engine price now: %f, money count = %f", price, m_moneyCount);
    });
}

void ShopComponent::buyScoreBoost() {
    buyItem(m_scorePrice, [this](int price){
        //update score price here
        m_ScorePriceLabel->m_label->setText(std::to_string(price));
        W4_LOG_DEBUG("score price now: %f, money count = %f", price, m_moneyCount);
    });
}

void ShopComponent::update(float dt) {
    IComponent::update(dt);
}

void ShopComponent::finalize() {
    IComponent::finalize();
    W4_LOG_DEBUG("[Inventory] FINALIZE called!");
}

ShopComponent::~ShopComponent() {
    W4_LOG_DEBUG("[Inventory] Destructor called!");
}