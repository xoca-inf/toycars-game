#pragma once

#include "W4Framework.h"
#include "Ui/data/FillData.h"
#include "Ui/UiRect.h"
#include "Ui/data/Image3dData.h"

W4_USE_UNSTRICT_INTERFACE

namespace games::benice::ui {

    using namespace games::benice::ui::data;

    class Image3d {

    public:
        Image3d() = default;
        ~Image3d();
        void initialize(sptr<Node> root, Image3dData data);
        void setUiRect(sptr<UiRect> rect);
        void setFillData(const FillData& data);
        const FillData& getFillData() const;

        void setClickable(bool flag);
        void setClickCallback( std::function<void()> callback);
        const std::string& getId() const;
        sptr<MaterialInst> getMaterial();
        void setMaterial(sptr<MaterialInst> material);
    private:
        float getDistance() const;
        void onRectChange(math::rect newRect);

        sptr<Node> m_root;
        sptr<VisibleNode> m_visual;
        sptr<UiRect> m_uiRect;
        Image3dData m_data;
        sptr<Collider> m_collider;
        std::function<void()> m_clickCallback;

    };
}

