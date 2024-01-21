#include "W4Framework.h"
#include "Ui/UiParser.h"

W4_USE_UNSTRICT_INTERFACE

class LevelProgressComponent : public IComponent{
    W4_COMPONENT(LevelProgressComponent, IComponent)
public:
    LevelProgressComponent(CloneTag, const LevelProgressComponent& from, Node& owner)
    : Super(CloneTag{}, from, owner)
    {}
    virtual ~LevelProgressComponent();

    virtual void initialize(const variant::Variant& data) override;
    virtual void update(float dt) override;
    virtual void finalize() override;

    void setup(sptr<LayoutImage> progressBar, sptr<LayoutImage> car, sptr<LayoutLabel> progressLabel);
private:
    Node m_sceneRoot;

    sptr<LayoutImage> m_progressBar;
    sptr<LayoutImage> m_car;
    sptr<LayoutLabel> m_label;

    vec3 m_startPos, m_destPos;
};
