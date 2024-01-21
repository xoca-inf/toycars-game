#pragma once
#include "W4Framework.h"
#include "Ui/UiParser.h"

W4_USE_UNSTRICT_INTERFACE

class UiLayoutComponent : public IComponent{
  W4_COMPONENT(UiLayoutComponent, IComponent)
public:
  UiLayoutComponent(CloneTag, const UiLayoutComponent& from, Node& owner)
  : Super(CloneTag{}, from, owner)
  {}
  virtual ~UiLayoutComponent(){}

  virtual void initialize(const variant::Variant& data) override;
  virtual void finalize() override;
  virtual void onEnabled(bool value) override;

  sptr<Node> getRoot();
  sptr<LayoutImage> getImage(const std::string& name);
  sptr<LayoutButton> getButton(const std::string& name);
  sptr<LayoutLabel> getLabel(const std::string& name);

  void resize(const math::size& newSize);
private:
  sptr<Node> m_uiRoot;
  std::vector<sptr<LayoutImage>> m_uiImages;
  std::vector<sptr<LayoutButton>> m_uiButtons;
  std::vector<sptr<LayoutLabel>> m_uiLabels;
};