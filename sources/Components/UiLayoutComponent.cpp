#include "UiLayoutComponent.h"
#include "W4JSON.h"

void UiLayoutComponent::initialize(const variant::Variant &data) {
  IComponent::initialize(data);
  auto filename = data.get<std::string>();
  auto filenameFull = "Ui/" + filename + ".json";

  m_uiRoot = make::sptr<Node>(filename);
  this->getOwner().addChild(m_uiRoot);
  auto file = w4::filesystem::open(filenameFull);
  auto json = nlohmann::json::parse(file->data(), file->data() + file->size());
  auto cameraPos = Render::getScreenCamera()->getWorldTranslation();
  auto frustrum = Render::getScreenCamera()->getFrustum();

  for (auto& value : json["labels"]){
    auto label = nlohmann::createLabel(value, frustrum);
    m_uiLabels.push_back(label);
  }
  for (auto& value : json["images"]){
    auto image = nlohmann::createImage(value, frustrum, cameraPos, m_uiRoot);
    m_uiImages.push_back(image);
  }
  for (auto& value : json["imageButtons"]){
    auto button = nlohmann::createImageButton(value, frustrum, cameraPos, m_uiRoot);
    m_uiButtons.push_back(button);
  }
}

void UiLayoutComponent::resize(const math::size& newSize) {
  auto cameraPos = Render::getScreenCamera()->getWorldTranslation();
  auto frustrum = Render::getScreenCamera()->getFrustum();
  auto screenSize = gui::getVirtualResolution();
  for (const auto &object : m_uiImages){
    object->m_node->setLocalTranslation(cameraPos + nlohmann::getPivot(object->m_pivot,frustrum) + vec3(object->m_offset.x, object->m_offset.y, 0));
  }
  for (const auto &object : m_uiButtons){
    object->m_node->setLocalTranslation(cameraPos + nlohmann::getPivot(object->m_pivot,frustrum) + vec3(object->m_offset.x, object->m_offset.y, 0));
  }
  for (const auto &label : m_uiLabels){
    label->m_label->setPosition(nlohmann::getScreenPoint(screenSize, label->m_pivot, label->m_offset, Render::getScreenCamera()->getFrustum()));
  }
}

void UiLayoutComponent::finalize() {
  IComponent::finalize();
  W4_LOG_DEBUG("UiLayoutComponent finalized!");
}

void UiLayoutComponent::onEnabled(bool value) {
  IComponent::onEnabled(value);
  W4_LOG_DEBUG("%s UI COMPONENT ENABLED CHANGED TO %d", m_uiRoot->getName().c_str(), value);
  m_uiRoot->setEnabled(value);
  for (const auto &item : m_uiButtons){
    W4_LOG_DEBUG("SET BUTTON [%s] CLICKABLE: %d", item->m_node->getName().c_str(), value);
    item->setClickable(value);
  }
  for (const auto &label : m_uiLabels){
    label->m_label->setVisible(value);
  }
}
sptr<LayoutImage> UiLayoutComponent::getImage(const std::string &name) {
  for (const auto &image : m_uiImages)
  {
    if(image->m_node->getName() == name) return image;
  }
  FATAL_ERROR("Image with name [%s] was not found", name.c_str());
  return w4::sptr<LayoutImage>();
}
sptr<LayoutButton> UiLayoutComponent::getButton(const std::string &name) {
  for (const auto &button : m_uiButtons)
  {
    if(button->m_node->getName() == name) return button;
  }
  FATAL_ERROR("Button with name [%s] was not found", name.c_str());
  return w4::sptr<LayoutButton>();
}
sptr<LayoutLabel> UiLayoutComponent::getLabel(const std::string &name) {
  for (const auto &label : m_uiLabels)
  {
    if(label->m_label->getName() == name) return label;
  }
  FATAL_ERROR("Label with name [%s] was not found", name.c_str());
  return w4::sptr<LayoutLabel>();
}
sptr<Node> UiLayoutComponent::getRoot() {
  return m_uiRoot;
}
