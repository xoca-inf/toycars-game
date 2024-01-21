#include "W4Framework.h"
#include "Ui/UiParser.h"

W4_USE_UNSTRICT_INTERFACE

class AccelerationComponent : public IComponent{
    W4_COMPONENT(AccelerationComponent, IComponent)
public:
    AccelerationComponent(CloneTag, const AccelerationComponent& from, Node& owner)
    : Super(CloneTag{}, from, owner)
    {}
    virtual ~AccelerationComponent();

    virtual void initialize(const variant::Variant& data) override;
    virtual void finalize() override;

    void setup(sptr<Node> physicsComponent);
    void pressKey();
    void pressCanister();
    void restart();
private:
    sptr<Node> m_physicsComponent;
    std::function<void()> m_updateCallback;
    bool m_isLaunchCar = false;
    bool m_isButtonCooldownPassed = true;

    float m_accelerationDuration;
    float m_currentAccelerationDuration;

    float m_fuelTopBarSize;
    float m_fuelRadius;
    float m_topBarYOffsetCoef = 1.1f;

    float m_totalHeight;
};
