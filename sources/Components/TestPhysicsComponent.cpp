#include "TestPhysicsComponent.h"
#include "Settings/ResourceLibary.h"
#include "Components/GameEndComponent.h"
#include "Settings/Settings.h"
#include "Components/Inventory.h"
#include "Components/SceneComponent.h"

void TestPhysicsComponent::initialize(const variant::Variant& data) {
    Super::initialize(data);
    W4_LOG_DEBUG("[TEST PHYSICS COMPONENT] INITIALIZE!");
    m_phisNode = make::sptr<Node>("PhysicsNode");
    Render::getRoot()->addChild(m_phisNode);
    m_phisSim = make::sptr<physics::Simulator>(500, 10, 0, Settings::instance().getVec3("Gravity"));
    w4::physics::SimulatorCollector::addSimulator(m_phisSim);

    spawnObstacles();
    auto car = Inventory::instance().getCurrentCar();
    m_carNode = car->getAsset()->getFirstRoot();

    m_carNode->setWorldTranslation(Settings::instance().getVec3("CarPosition") + vec3(0,car->getVehicleSize().y/2,0));
    m_carNode->setWorldRotation(Rotator(Settings::instance().getVec3("CarRotation")));
    m_prevPoint = m_carNode->getWorldTranslation();
    m_phisNode->addChild(m_carNode);

    auto carMaterial = ResourceLibary::instance().getMaterial("SceneMaterial")->createInstance();
    carMaterial->setTexture(TextureId::TEXTURE_0, Inventory::instance().getCurrentCar()->getTexture());
    carMaterial->setParam("light_params", Settings::instance().getVec3("ShadowIntensity"));
    carMaterial->setParam("shinessParam", Settings::instance().getFloat("LightShiness"));
    m_carNode->traversalTyped<VisibleNode>([&](cref<VisibleNode> entry) {
        entry->setMaterialInst(carMaterial);
    });

}

void TestPhysicsComponent::finalize() {
    IComponent::finalize();
    W4_LOG_DEBUG("[TESTPHYSICS COMPONENT] FINALIZE called!");
    m_carNode->template removeAllComponents<GameEndComponent>();
    m_carNode->template removeAllComponents<PhysicsComponent>();
    m_phisNode->foreachChildren([this](Node& node){node.removeAllComponents<PhysicsComponent>();});
    Render::getRoot()->removeChild(m_phisNode);
    w4::physics::SimulatorCollector::removeSimulator(m_phisSim);
    m_phisSim = nullptr;
    m_phisNode = nullptr;
    m_carNode = nullptr;
    m_carGeometry = nullptr;
    m_obstaclesMaterial = nullptr;
}

void TestPhysicsComponent::launchCar() {
  //ADDING CAR GEOMETRY
  W4_LOG_DEBUG("[PHYSICS COMPONENT] CAR LAUNCHED");
  m_carGeometry = make::sptr<w4::physics::CubeGeometry>(Inventory::instance().getCurrentCar()->getVehicleSize());
  auto& physics = m_carNode->addComponent<PhysicsComponent>();
  physics.setup(m_phisSim,Body::BodyType::Rigid, PhysicsGeometry::Custom);
  physics.addGeometry(m_carGeometry);
  physics.setInertiaTensor(calculateBoxInertiaTensor(Inventory::instance().getCurrentCar()->getVehicleSize(), Settings::instance().getFloat("VehicleMass")));
  auto material = make::sptr<PhysicsMaterial>(Settings::instance().getFloat("Friction"), Settings::instance().getFloat("Restitution"));
  physics.setMaterial(material);
  physics.setMass(Settings::instance().getFloat("VehicleMass"));
  
  
  setVelocity(m_carNode->getWorldRight());

	W4_LOG_DEBUG("StartAcceleration: %f, StartAccelerationForce: %f",
		Settings::instance().getVec3("StartAcceleration").length(), Settings::instance().getFloat("StartAccelerationForce"));
	W4_LOG_DEBUG("Velocity: %f", getVelocity().length());

	m_isFirstAcceleration = true;
	m_isCarStarted = true;
	Timer::addTask(Settings::instance().getFloat("StartAccelerationTime"), [this] () {
		m_isCarStarted = false;
		return true;
	});
  
  
  m_carNode->template addComponent<GameEndComponent>().setup(m_carNode, [this](){
      m_zeroVelocityCallback();
  });
}

void TestPhysicsComponent::setZeroVelocityCallback(std::function<void()> callback) {
    m_zeroVelocityCallback = callback;
}

vec3 TestPhysicsComponent::getVelocity() const
{
	return m_carNode->getFirstComponent<physics::PhysicsComponent>().getVelocity();
}

vec3 TestPhysicsComponent::getForce() const
{
	return m_carNode->getFirstComponent<physics::PhysicsComponent>().getForce();
}

void TestPhysicsComponent::setVelocity(const vec3& velocity)
{
	m_carNode->getFirstComponent<physics::PhysicsComponent>().setVelocity(velocity);
}

void TestPhysicsComponent::setVelocity(const float& velocity)
{
	setVelocity(getVelocity().normalize() * velocity);
}

void TestPhysicsComponent::setForce(const vec3& force)
{
	m_carNode->getFirstComponent<physics::PhysicsComponent>().setForce(force);
}

void TestPhysicsComponent::setForce(const float& force)
{
	setForce(getForce().normalize() * force);
}

void TestPhysicsComponent::startAcceleration() {
  m_isCarAccelerated = true;
  W4_LOG_DEBUG("ACCELERATION STARTED. WILL END IN %d", Inventory::instance().getCanisterLVL());
  Timer::addTask(Inventory::instance().getCanisterLVL(), [&](){stopAcceleration(); return true;});
}

void TestPhysicsComponent::stopAcceleration() {
  m_isCarAccelerated = false;
}

//void TestPhysicsComponent::pushPhysicsButton() {
//  if(!m_isCarStarted && m_carNode != nullptr){
//    m_isCarStarted = true;
//    Timer::addTask(0.5,[this](){m_isButtonCooldownPassed = true; return true;});
//    launchCar();
//  }
//  if(m_isCarStarted && m_isButtonCooldownPassed && !m_isCarAccelerated && m_carNode != nullptr){
//    m_isCarAccelerated = true;
//    accelerateCar();
//  }
//}

void TestPhysicsComponent::spawnObstacles() {
  m_obstaclesMaterial = ResourceLibary::instance().getMaterial("SceneMaterial")->createInstance();
  m_obstaclesMaterial->setTexture(TextureId::TEXTURE_0, ResourceLibary::instance().getTexture("GridTexture"));
  m_obstaclesMaterial->setParam("light_params", Settings::instance().getVec3("ShadowIntensity"));
  m_obstaclesMaterial->setParam("shinessParam", Settings::instance().getFloat("LightShiness"));

  auto file = w4::filesystem::open("Temp/obstacles.json");
  auto json = nlohmann::json::parse(file->data(), file->data() + file->size());
  for (auto& value : json["obstacles"]){
    vec3 size = value["size"];
    vec3 translation = value["position"];
    vec3 rotation = value["rotation"];
    auto mesh = Mesh::create::cube(size);
    mesh->setWorldTranslation(translation);
    mesh->setWorldRotation(rotation);
    mesh->setMaterialInst(m_obstaclesMaterial);
    m_phisNode->addChild(mesh);
    mesh->addComponent<PhysicsComponent>().setup(m_phisSim,Body::BodyType::Animated, PhysicsGeometry::AutoCube);
  }
}
void TestPhysicsComponent::update(float dt) {
  IComponent::update(dt);
  vec3 tmpPos = m_carNode->getWorldTranslation();

  auto &score = Inventory::instance();
  score.setPassedDistance(score.getPassedDistance() +
                          (tmpPos - m_prevPoint).length());

  m_prevPoint = tmpPos;

  if (m_isCarStarted) {
    setVelocity(Settings::instance().getFloat("StartAccelerationForce"));
  }

  if (m_isCarAccelerated) {
    if (m_isFirstAcceleration)
      setVelocity(m_carNode->getWorldRight() * Settings::instance().getFloat("StartAccelerationForce") *
                                               Settings::instance().getFloat("AccelerationForce"));
    m_isFirstAcceleration = false;
    m_isCarStarted = false;
  }
}
