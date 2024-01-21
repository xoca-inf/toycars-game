#include "ScoreComponent.h"
#include "Settings/Settings.h"

void ScoreComponent::initialize(const variant::Variant& data) {
  Super::initialize(data);
  W4_LOG_DEBUG("[SCORE COMPONENT] INITIALIZE");
  //API here

}
void ScoreComponent::finalize() {
    IComponent::finalize();
    W4_LOG_DEBUG("[SCORE COMPONENT] FINALIZE called!");
}
ScoreComponent::~ScoreComponent() {
  W4_LOG_DEBUG("[SCORE COMPONENT] Destructor called!");
}

int ScoreComponent::getPoints() const
{
  return m_points;
}

void ScoreComponent::setPoints(int count)
{
  m_points = count;
}

void ScoreComponent::addPoints(int count)
{
  m_points += count;
}

void ScoreComponent::spendPoints(int count)
{
  m_points -= count;
}

int ScoreComponent::getOpened() const
{
  return m_opened_count;
}

void ScoreComponent::setOpened(int count)
{
  m_opened_count = count;
}

void ScoreComponent::incOpened()
{
  m_opened_count++;
}

int ScoreComponent::getPassed() const
{
  return m_passed_count;
}

void ScoreComponent::setPassed(int count)
{
  m_passed_count = count;
}

void ScoreComponent::incPassed()
{
  m_passed_count++;
}

int ScoreComponent::getCurrentCar() const
{
  return m_current_car;
}

void ScoreComponent::setCurrentCar(int count)
{
  m_current_car = count;
}

void ScoreComponent::incCurrentCar()
{
  m_current_car++;
}

int ScoreComponent::getCanisterLVL() const
{
  return m_canister_lvl;
}

void ScoreComponent::setCanisterLVL(int count)
{
  m_canister_lvl = count;
}

void ScoreComponent::incCanisterLVL()
{
  m_canister_lvl++;
}

int ScoreComponent::getEngineLVL() const
{
  return m_engine_lvl;
}

void ScoreComponent::setEngineLVL(int count)
{
  m_engine_lvl = count;
}

void ScoreComponent::incEngineLVL()
{
  m_engine_lvl++;
}

float ScoreComponent::getNeededDistance() const {
    return m_neededDistance;
}

void ScoreComponent::setNeededDistance(float value) {
    m_neededDistance = value;
}

float ScoreComponent::getPassedDistance() const {
    return m_passedDistance;
}

void ScoreComponent::setPassedDistance(float value) {
    m_passedDistance = value;
}
