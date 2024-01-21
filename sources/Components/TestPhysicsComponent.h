#pragma once
#include "W4Framework.h"

W4_USE_UNSTRICT_INTERFACE

class TestPhysicsComponent : public IComponent{
    W4_COMPONENT(TestPhysicsComponent, IComponent)
public:
    TestPhysicsComponent(CloneTag, const TestPhysicsComponent& from, Node& owner)
    : Super(CloneTag{}, from, owner)
    {}
    virtual ~TestPhysicsComponent(){}

    virtual void initialize(const variant::Variant& data) override;
    virtual void finalize() override;
    virtual void update(float dt) override;

    sptr<Node> getCarNode(){return m_carNode;}
    void setZeroVelocityCallback( std::function<void()> callback);

	vec3 getVelocity() const;
    vec3 getForce() const;

    void setVelocity(const vec3& velocity);
    void setVelocity(const float& velocity);

    void setForce(const vec3& force);
    void setForce(const float& force);

    void pushPhysicsButton(); //main gameplay button

    void startAcceleration();
    void stopAcceleration();
    void launchCar();
private:
    void spawnObstacles();

    bool m_isCarStarted = false;
    bool m_isCarAccelerated = false;
	bool m_isFirstAcceleration = false;

    sptr<physics::Simulator> m_phisSim;
    sptr<Node> m_phisNode;
    sptr<Node> m_carNode;
    sptr<CubeGeometry> m_carGeometry;
    sptr<MaterialInst> m_obstaclesMaterial;

    std::function<void()>   m_zeroVelocityCallback;

    vec3 m_prevPoint;
};
