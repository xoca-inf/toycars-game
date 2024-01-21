#pragma once
#include "W4Framework.h"

W4_USE_UNSTRICT_INTERFACE

class ScoreComponent : public IComponent{
  W4_COMPONENT(ScoreComponent, IComponent)
public:
  ScoreComponent(CloneTag, const ScoreComponent& from, Node& owner)
      : Super(CloneTag{}, from, owner)
  {}
  virtual ~ScoreComponent();

  int getPoints() const;
  void setPoints(int count);
  void addPoints(int count);
  void spendPoints(int count);

  int getOpened() const;
  void setOpened(int count);
  void incOpened();

  int getPassed() const;
  void setPassed(int count);
  void incPassed();

  int getCurrentCar() const;
  void setCurrentCar(int count);
  void incCurrentCar();

  int getCanisterLVL() const;
  void setCanisterLVL(int count);
  void incCanisterLVL();

  int getEngineLVL() const;
  void setEngineLVL(int count);
  void incEngineLVL();

  float getNeededDistance() const;
  void setNeededDistance(float value);


  float getPassedDistance() const;
  void setPassedDistance(float value);

  virtual void initialize(const variant::Variant& data) override;
  virtual void finalize() override;

private:
  int m_points = 0;
  int m_opened_count = 0;
  int m_passed_count = 0;
  int m_current_car = 0;
  int m_canister_lvl = 0;
  int m_engine_lvl = 0;
  float m_neededDistance;
  float m_passedDistance;
};
