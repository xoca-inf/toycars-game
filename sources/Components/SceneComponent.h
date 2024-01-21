#include "W4Framework.h"

W4_USE_UNSTRICT_INTERFACE

class SceneComponent : public IComponent{
    W4_COMPONENT(SceneComponent, IComponent)
public:
    SceneComponent(CloneTag, const SceneComponent& from, Node& owner)
    : Super(CloneTag{}, from, owner)
    {}
    virtual ~SceneComponent();

    virtual void initialize(const variant::Variant& data) override;
    virtual void finalize() override;
    void setup(sptr<Node> cameraNode);

    sptr<Node> getCameraNode();

private:
    sptr<Node> m_sceneRoot;
    sptr<Node> m_cameraNode;

    float m_needLength;
};
