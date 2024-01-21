#pragma once
#include "W4Framework.h"

W4_USE_UNSTRICT_INTERFACE

class CameraMovementComponent : public IComponent{
W4_COMPONENT(CameraMovementComponent, IComponent)
public:
  CameraMovementComponent(CloneTag, const CameraMovementComponent& from, Node& owner)
  : Super(CloneTag{}, from, owner)
  {}
  virtual ~CameraMovementComponent(){}

  virtual void update(float dt) override;

  void setup(sptr<Node> cameraNode, sptr<Node> targetNode);
private:
  sptr<Node> m_cameraNode;
  sptr<Node> m_targetNode;

  vec3 m_offset = {0,0,0};
  float m_lerpValue = 0.3f;
};

