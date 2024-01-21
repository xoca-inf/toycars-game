#pragma once
#include "W4Framework.h"
#include "Ui/WorldUi.h"

using namespace games::benice::ui;

class MainMenuUi : public WorldUi
{
public:
    MainMenuUi(sptr<Node> root, sptr<Camera> camera, float distance, float baseOrder)
        : WorldUi(root,camera,distance, baseOrder){};
    void setSettingsPressedCallback( std::function<void()> callback)   {m_settingsPressedCallback = callback;};
    void setHighScoresPressedCallback( std::function<void()> callback)    {m_highscoresPressedCallback = callback;};
    void setShopPressedCallback( std::function<void()> callback)    {m_shopPressedCallback = callback;};
    void setPlayPressedCallback( std::function<void()> callback)    {m_playPressedCallback = callback;};
protected:
    void initContent() override;
private:
    std::function<void()> m_settingsPressedCallback;
    std::function<void()> m_highscoresPressedCallback;
    std::function<void()> m_shopPressedCallback;
    std::function<void()> m_playPressedCallback;
};


