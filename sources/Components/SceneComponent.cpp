#include "SceneComponent.h"
#include "Settings/ResourceLibary.h"
#include "Settings/Settings.h"
#include "Components/Inventory.h"

void SceneComponent::initialize(const variant::Variant& data) {
    Super::initialize(data);
    W4_LOG_DEBUG("[SCENE COMPONENT] INITIALIZE");
    //Spawn scene
    m_sceneRoot = ResourceLibary::instance().getModel("Scene")->getFirstRoot();
    m_sceneRoot->setWorldTranslation(Settings::instance().getVec3("ScenePosition"));
    Render::getRoot()->addChild(m_sceneRoot);

    auto sceneMat = ResourceLibary::instance().getMaterial("SceneMaterial")->createInstance();
    sceneMat->setTexture(TextureId::TEXTURE_0, ResourceLibary::instance().getTexture("SceneTexture"));
    sceneMat->setParam("light_params", Settings::instance().getVec3("ShadowIntensity"));
    sceneMat->setParam("shinessParam", Settings::instance().getFloat("LightShiness"));
    m_sceneRoot->traversalTyped<VisibleNode>([&](cref<VisibleNode> entry) {
        entry->setMaterialInst(sceneMat);
    });
}

void SceneComponent::setup(sptr<Node> cameraNode) {
    m_cameraNode = cameraNode;
    auto& score = Inventory::instance();
    //HARDCODE!!!
    score.setNeededDistance(100);
    score.setPassedDistance(0);
}

sptr<Node> SceneComponent::getCameraNode() {
    return m_cameraNode;
}

SceneComponent::~SceneComponent() {
    W4_LOG_DEBUG("[SCENE COMPONENT] Destructor called!");
}

void SceneComponent::finalize() {
    IComponent::finalize();
    W4_LOG_DEBUG("[SCENE COMPONENT] FINALIZE called!");
    Render::getRoot()->removeChild(m_sceneRoot);
    m_sceneRoot.reset();
}
