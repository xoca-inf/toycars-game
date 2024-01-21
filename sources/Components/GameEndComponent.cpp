#include "GameEndComponent.h"
#include "Settings/ResourceLibary.h"
#include "Settings/Settings.h"


void GameEndComponent::initialize(const variant::Variant& data) {
    Super::initialize(data);
    W4_LOG_DEBUG("[GameEndComponent] INITIALIZE");
}

void GameEndComponent::setup(sptr<Node> car, std::function<void()> onGameEnd){
    m_car = car;
    m_onGameEnd = onGameEnd;
}

void GameEndComponent::update(float dt) {
    IComponent::update(dt);

    if(m_car){
        auto& physics = m_car->getFirstComponent<physics::PhysicsComponent>();
        auto velocity = physics.getVelocity().length();
        if(velocity >= 0.05f){
            if(!m_isStarted)
                m_isStarted = true;
        }else if(m_isStarted){
            if(!m_isCallbackCalled){
                m_isCallbackCalled = true;
                W4_LOG_DEBUG("[GameEndComponent] Game end");
                m_onGameEnd();
            }
        }
    }
}

void GameEndComponent::finalize() {
    IComponent::finalize();
    m_car = nullptr;
    m_onGameEnd = nullptr;
    W4_LOG_DEBUG("[GameEndComponent] FINALIZE called!");
}

GameEndComponent::~GameEndComponent() {
    W4_LOG_DEBUG("[GameEndComponent] Destructor called!");
}