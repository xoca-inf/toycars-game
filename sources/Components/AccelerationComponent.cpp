#include "AccelerationComponent.h"
#include "Settings/ResourceLibary.h"
#include "Settings/Settings.h"
#include "Components/SceneComponent.h"
#include "Components/Inventory.h"
#include "Components/TestPhysicsComponent.h"
#include "Components/UiLayoutComponent.h"

void AccelerationComponent::initialize(const variant::Variant& data) {
    Super::initialize(data);
    W4_LOG_DEBUG("[LEVEL PROGRESS COMPONENT] INITIALIZE");
}

void AccelerationComponent::setup(sptr<Node> physicsComponent) {
    m_physicsComponent = physicsComponent;
}

AccelerationComponent::~AccelerationComponent() {
    W4_LOG_DEBUG("[ACCELERATION COMPONENT] Destructor called!");
}

void AccelerationComponent::finalize() {
    IComponent::finalize();
    m_physicsComponent = nullptr;
}

void AccelerationComponent::pressKey() {
    if (!m_isLaunchCar) {
        auto& physComp = m_physicsComponent->getFirstComponent<TestPhysicsComponent>();
        m_isLaunchCar = true;
        physComp.launchCar();
    }
}

void AccelerationComponent::pressCanister() {
    if (m_isLaunchCar) {
        if (m_isButtonCooldownPassed) {
            auto& physComp = m_physicsComponent->getFirstComponent<TestPhysicsComponent>();
            m_isButtonCooldownPassed = false;
            m_currentAccelerationDuration = Inventory::instance().getCanisterLVL();
            m_accelerationDuration = m_currentAccelerationDuration;
            physComp.startAcceleration();

            Timer::addTask(m_currentAccelerationDuration, [this]() {
                auto& physComp = m_physicsComponent->getFirstComponent<TestPhysicsComponent>();
                physComp.stopAcceleration();
                return true;
            });
        }
    }
}
