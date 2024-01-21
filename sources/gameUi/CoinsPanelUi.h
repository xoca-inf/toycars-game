#pragma  once

#include "W4Framework.h"
#include "Ui/DomUi.h"

using namespace games::benice::ui;

class CoinsPanelUi : public DomUi
{
public:
      CoinsPanelUi(float baseOrder) : DomUi(baseOrder) {}

//    CoinsPanelUi(sptr<Node> root, sptr<Camera> camera, float distance, float baseOrder)
//            : WorldUi(root, camera, distance, baseOrder) {};

    void setCoins(int coins);

protected:
    void initContent() override;
private:
    sptr<Label> m_label;
};
