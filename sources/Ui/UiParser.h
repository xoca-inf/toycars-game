#pragma once
#include "W4Framework.h"
#include "W4JSON.h"

W4_USE_UNSTRICT_INTERFACE

struct LayoutImage;
struct LayoutButton;
struct LayoutLabel;

namespace nlohmann{

enum class Pivot : uint {
  TopLeft = 0,
  TopCenter = 1,
  TopRight = 2,
  CenterLeft = 3,
  CenterCenter = 4,
  CenterRight = 5,
  BottomLeft = 6,
  BottomCenter = 7,
  BottomRight = 8
};

W4_NLOHMANN_JSON_SERIALIZE_ENUM(Pivot,
                                {{Pivot::TopLeft, "TopLeft"},
                                 {Pivot::TopCenter, "TopCenter"},
                                 {Pivot::TopRight, "TopRight"},
                                 {Pivot::CenterLeft, "CenterLeft"},
                                 {Pivot::CenterCenter, "CenterCenter"},
                                 {Pivot::CenterRight, "CenterRight"},
                                 {Pivot::BottomLeft, "BottomLeft"},
                                 {Pivot::BottomCenter, "BottomCenter"},
                                 {Pivot::BottomRight, "BottomRight"}});

vec3 getPivot(Pivot pivot, const math::Frustum &cameraFrustrum);
ivec2 getScreenPoint(size screenSize, Pivot pivot, vec2 offset, const math::Frustum &cameraFrustrum);

sptr<LayoutLabel> createLabel(const json &value, const math::Frustum &cameraFrustrum);
sptr<LayoutImage> createImage(const json &value, const math::Frustum &cameraFrustrum, vec3 cameraPos,
                       sptr<Node> root = nullptr);

sptr<LayoutButton> createImageButton(const json &value, const math::Frustum &cameraFrustrum, vec3 cameraPos,
                               sptr<Node> root = nullptr);
}
struct LayoutLabel{
  sptr<Label>     m_label;
  nlohmann::Pivot m_pivot;
  vec2            m_offset;
  ivec2           m_size;
};

struct LayoutImage{
  sptr<Mesh>      m_mesh;
  sptr<Node>      m_node;
  nlohmann::Pivot m_pivot;
  vec2            m_offset;
  vec2            m_size;
};

struct LayoutButton : public LayoutImage{
public:
  LayoutButton(sptr<LayoutImage> image);
  void setClickable(bool clickable);
  void setClickCallback( std::function<void()> callback);
  void setCollider(sptr<Collider> collider);
  void invokeCallback();
private:
  sptr<Collider>          m_collider;
  bool                    m_clickable       = true;
  std::function<void()>   m_clickCallback;
};

