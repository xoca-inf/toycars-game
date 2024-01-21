#pragma once
#include "W4Framework.h"
#include "Ui/WorldUi.h"
#include "Components/Inventory.h"
#include "Components/Transport.h"

using namespace games::benice::ui;

class VehicleSelectUi : public WorldUi {
public:
    VehicleSelectUi(sptr<Node> root, sptr<Camera> camera, float distance, float baseOrder)
            : WorldUi(root,camera,distance, baseOrder){};
    void setPlayPressedCallback( std::function<void()> callback)    {m_playPressedCallback = callback;};

    void setCarPressedCallback( std::function<void(const int id)> callback)    {m_setCar = callback;};

    void setBackPressedCallback( std::function<void()> callback)    {m_backPressedCallback = callback;};
protected:
    void initContent() override;
private:
    std::function<void()> m_playPressedCallback;
    std::function<void(const int id)> m_setCar;
    std::function<void()> m_backPressedCallback;
};
