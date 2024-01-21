#include "UiParser.h"
#include "Settings/ResourceLibary.h"

namespace nlohmann {
sptr<LayoutLabel> createLabel(const json &value, const math::Frustum &cameraFrustrum){
  auto label = make::sptr<LayoutLabel>();
  auto screenSize = gui::getVirtualResolution();
  std::string name = value.contains("name") ? value["name"] : "uiObject";
  std::string material = value.contains("material") ? value["material"] : "DefaultMaterial";
  std::string texture = value.contains("texture") ? value["texture"] : "DefaultTexture";
  Pivot pivot = Pivot::CenterCenter;
  if(value.contains("pivot")) pivot = value["pivot"];
  vec2 offset = vec2(0,0);
  if(value.contains("offset")) offset = value["offset"];
  ivec2 size = ivec2(1,1);
  if(value.contains("size")) size = value["size"];

  auto widget = createWidget<Label>(nullptr, "test", getScreenPoint(screenSize, pivot, offset, cameraFrustrum));
  widget->setName(name);
  widget->setHorizontalAlign(HorizontalAlign::Center);
  widget->setVerticalAlign(VerticalAlign::Center);
  widget->setSize(size);

  label->m_label = widget;
  label->m_pivot = pivot;
  label->m_offset = offset;
  label->m_size = size;

  return label;
}

sptr<LayoutImage> createImage(const json &value, const math::Frustum &cameraFrustrum, vec3 cameraPos,
                       sptr<Node> root) {
  auto image = make::sptr<LayoutImage>();

  std::string name = value.contains("name") ? value["name"] : "uiObject";
  std::string material = value.contains("material") ? value["material"] : "DefaultMaterial";
  std::string texture = value.contains("texture") ? value["texture"] : "DefaultTexture";
  Pivot pivot = Pivot::CenterCenter;
  if(value.contains("pivot")) pivot = value["pivot"];
  vec2 offset = vec2(0,0);
  if(value.contains("offset")) offset = value["offset"];
  vec2 size = vec2(0.01f,0.01f);
  if(value.contains("size")) size = value["size"];
  int renderOrder = 0;
  if(value.contains("renderOrder")) renderOrder = value["renderOrder"];
  float zOffset = 0.0f;
  if(value.contains("zOffset")) zOffset = value["zOffset"];
  auto plane = Mesh::create::plane(vec2(1, 1));
  plane->setWorldScale(vec3(size.x, size.y, 1));
  plane->setName(name);
  if(root) root->addChild(plane);
  plane->setLocalTranslation(cameraPos + getPivot(pivot,cameraFrustrum) + vec3(offset.x, offset.y, zOffset));

  //setup material
  sptr<MaterialInst> materialInst;
  if(material != "DefaultMaterial") {
    materialInst = ResourceLibary::instance().getMaterial(material)->createInstance();
  }
  else materialInst = Material::getDefaultLambert()->createInstance();

  materialInst->setTexture(TextureId::TEXTURE_0, ResourceLibary::instance().getTexture(texture));
  plane->setMaterialInst(materialInst);
  plane->setRenderOrder(renderOrder);

  image->m_mesh = plane;
  image->m_node = plane;
  image->m_pivot = pivot;
  image->m_offset = offset;
  image->m_size = size;
  return image;
}

sptr<LayoutButton> createImageButton(const json &value,
                                     const math::Frustum &cameraFrustrum,
                                     vec3 cameraPos, sptr<Node> root) {
  auto image = createImage(value,cameraFrustrum,cameraPos,root);
  auto button = make::sptr<LayoutButton>(image);
  auto buttonNode = button->m_node;
  auto buttonMesh = button->m_mesh;
  auto collider = buttonNode->addCollider(make::sptr<core::AABB>(buttonMesh));
  collider->setReceiveRaycasts();
  collider->setBlockRaycasts(true);
  collider->setScreencastCallback([button](const CollisionInfo& collisionInfo){
    W4_LOG_DEBUG("[BUTTON] %s hitted!", button->m_node->getName().c_str());
    button->invokeCallback();
  });
  button->setCollider(collider);

  return button;
}

vec3 getPivot(Pivot pivot, const math::Frustum &cameraFrustrum) {
  switch (pivot) {
  case Pivot::TopLeft:
    return cameraFrustrum.points[1];
  case Pivot::TopCenter:
    return (cameraFrustrum.points[2] + cameraFrustrum.points[1]) * 0.5f;
  case Pivot::TopRight:
    return cameraFrustrum.points[2];
  case Pivot::CenterLeft:
    return (cameraFrustrum.points[1] + cameraFrustrum.points[0]) * 0.5f;
  case Pivot::CenterCenter:
    return (getPivot(Pivot::CenterRight,cameraFrustrum) + getPivot(Pivot::CenterLeft,cameraFrustrum)) * 0.5f;
  case Pivot::CenterRight:
    return (cameraFrustrum.points[2] + cameraFrustrum.points[3]) * 0.5f;
  case Pivot::BottomLeft:
    return cameraFrustrum.points[0];
  case Pivot::BottomCenter:
    return (cameraFrustrum.points[3] + cameraFrustrum.points[0]) * 0.5f;
  case Pivot::BottomRight:
    return cameraFrustrum.points[3];
  }
}
ivec2 getScreenPoint(size screenSize, Pivot pivot, vec2 offset, const math::Frustum &cameraFrustrum) {
  auto point = getPivot(pivot, cameraFrustrum) + vec3(offset.x,offset.y,0);
  auto leftPointOffset = point.x - cameraFrustrum.points[1].x;
  auto topPointOffset = cameraFrustrum.points[1].y - point.y;
  auto frustrumWidth = (cameraFrustrum.points[2].x - cameraFrustrum.points[1].x);
  auto frustrumHeight = (cameraFrustrum.points[1].y - cameraFrustrum.points[0].y);
  W4_LOG_DEBUG("FRUSTRUM 1 Y = %f", cameraFrustrum.points[1].y);
  W4_LOG_DEBUG("FRUSTRUM 0 Y = %f", cameraFrustrum.points[0].y);
  W4_LOG_DEBUG("LEFTPOINTOFFSET = %f", leftPointOffset);
  W4_LOG_DEBUG("TOPPOINTOFFSET = %f", topPointOffset);
  W4_LOG_DEBUG("FRUSTRUM WIDTH = %f", frustrumWidth);
  W4_LOG_DEBUG("FRUSTRUM HEIGHT = %f", frustrumHeight);
  auto leftOffsetMultiplier = leftPointOffset / frustrumWidth;
  auto topOffsetMultiplier = topPointOffset / frustrumHeight;
  W4_LOG_DEBUG("leftOffset = %d", leftOffsetMultiplier);
  W4_LOG_DEBUG("topOffset = %d", topOffsetMultiplier);
  return ivec2(leftOffsetMultiplier * screenSize.w, topOffsetMultiplier * screenSize.h);
}
} // namespace nlohmann
void LayoutButton::setClickable(bool clickable) {
  m_clickable = clickable;
  m_collider->setReceiveRaycasts(clickable);
  m_collider->setBlockRaycasts(clickable);
  m_collider->setBlockScreencasts(clickable);
}
void LayoutButton::setClickCallback(std::function<void()> callback) {
  m_clickCallback = callback;
}
LayoutButton::LayoutButton(sptr<LayoutImage> image) {
  this->m_node = image->m_node;
  this->m_mesh = image->m_mesh;
  this->m_offset = image->m_offset;
  this->m_pivot = image->m_pivot;
  this->m_size = image->m_size;
}
void LayoutButton::invokeCallback() {
  if (m_clickCallback!= nullptr && m_clickable)
  {
    m_clickCallback();
  }
  else{
    if(!m_clickable)      W4_LOG_DEBUG("[%s] BUTTON NOT CLICKABLE!", m_node->getName().c_str());
    if(!m_clickCallback)  W4_LOG_DEBUG("[%s] CALLBACK IS EMPTY!", m_node->getName().c_str());
  }

}
void LayoutButton::setCollider(sptr<Collider> collider) {
  m_collider = collider;
}
