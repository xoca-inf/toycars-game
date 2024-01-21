#include "CameraMovementComponent.h"
#include "Settings/ResourceLibary.h"
#include "Settings/Settings.h"
void CameraMovementComponent::update(float dt) {
  IComponent::update(dt);
  if(m_cameraNode != nullptr && m_targetNode != nullptr){
    auto targetPosition = m_targetNode->getWorldTranslation();
    auto selfPosition = m_cameraNode->getWorldTranslation();

    if(selfPosition + m_offset != targetPosition)
    {
      m_cameraNode->setWorldTranslation(selfPosition.lerp(targetPosition + m_offset, m_lerpValue));
    }
  }
}
void CameraMovementComponent::setup(sptr<Node> cameraNode,
                                    sptr<Node> targetNode) {
  W4_LOG_DEBUG("[CAMERA MOVEMENT] setup called!");
  m_cameraNode = cameraNode;
  m_targetNode = targetNode;

  m_offset = Settings::instance().getVec3("CameraOffset");
  //m_offset = targetNode->getWorldTranslation() - cameraNode->getWorldTranslation();
  m_lerpValue = Settings::instance().getFloat("CameraLerpValue");
  //setup start position
  m_cameraNode->setWorldTranslation(m_targetNode->getWorldTranslation() + m_offset);
  m_cameraNode->setWorldRotation(Rotator(Settings::instance().getVec3("CameraAngle")));
}
