#include "LevelProgressComponent.h"
#include "Settings/ResourceLibary.h"
#include "Settings/Settings.h"
#include "Components/SceneComponent.h"
#include "Components/Inventory.h"
#include "Components/UiLayoutComponent.h"

void LevelProgressComponent::initialize(const variant::Variant& data) {
    Super::initialize(data);
    W4_LOG_DEBUG("[LEVEL PROGRESS COMPONENT] INITIALIZE");
}

void LevelProgressComponent::setup(sptr<LayoutImage> progressBar, sptr<LayoutImage> car, sptr<LayoutLabel> progressLabel) {
    m_progressBar = progressBar;
    m_car = car;
    m_label = progressLabel;

  m_startPos = m_car->m_node->getLocalTranslation();

  m_destPos = m_startPos + vec3(-2 * m_car->m_offset.x, 0, 0);
}

void LevelProgressComponent::update(float dt) {
    Super::update(dt);

    auto& score = Inventory::instance();

    float percent = score.getPassedDistance() / score.getNeededDistance();
    m_label->m_label->setText(utils::format("%d CM", (int)score.getPassedDistance()));
    m_car->m_node->setLocalTranslation(percent < 1.0f 
        ? m_destPos * percent + m_startPos * (1 - percent)
        : m_destPos);

    m_progressBar->m_mesh->getMaterialInst()->setParam<float>("percent", percent);
}

LevelProgressComponent::~LevelProgressComponent() {
    W4_LOG_DEBUG("[LEVEL PROGRESS COMPONENT] Destructor called!");
}

void LevelProgressComponent::finalize() {
    IComponent::finalize();
}
