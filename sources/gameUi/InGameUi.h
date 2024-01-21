#pragma once
#include "W4Framework.h"
#include "Ui/WorldUi.h"

using namespace games::benice::ui;

class InGameUi : public WorldUi{
public:
    InGameUi(sptr<Node> root, sptr<Camera> camera, float distance, float baseOrder)
    : WorldUi(root,camera,distance, baseOrder){};
    void setKeyPressedCallback( std::function<void()> callback)    {m_keyPressedCallback = callback;};
    void setCanisterPressedCallback( std::function<void()> callback)    {m_canisterPressedCallback = callback;};
protected:
    void initContent() override;
    void switchKeyToCanister();
private:
    bool m_isKeyPressed = false;
    sptr<UiRect> m_contentRect;
    std::function<void()> m_keyPressedCallback;
    std::function<void()> m_canisterPressedCallback;
    std::function<void()> m_accelerationStartedCallback;
    std::function<void()> m_accelerationEndedCallback;
};