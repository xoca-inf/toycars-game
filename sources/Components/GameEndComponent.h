#pragma once
#include "W4Framework.h"

W4_USE_UNSTRICT_INTERFACE

class GameEndComponent : public IComponent{
W4_COMPONENT(GameEndComponent, IComponent)
public:
    GameEndComponent(CloneTag, const GameEndComponent& from, Node& owner)
            : Super(CloneTag{}, from, owner)
    {
    }

    void initialize(const variant::Variant& data) override;
    void update(float dt) override;
    void finalize() override;
    ~GameEndComponent() override;

    void setup(sptr<Node> car, std::function<void()> onGameEnd);
private:
    std::function<void()> m_onGameEnd;
    sptr<Node> m_car;
    bool m_isCallbackCalled = false;
    bool m_isStarted = false;
};

