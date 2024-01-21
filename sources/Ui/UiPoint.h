#pragma once

#include "data/Offset.h"
#include "W4Framework.h"

W4_USE_UNSTRICT_INTERFACE
namespace games::benice::ui
{
    using namespace games::benice::ui::data;

    class UiPoint
    {
    public:
        UiPoint(const Offset &h, const Offset &v);

        void initialize(const Offset &h, const Offset &v);

        ~UiPoint();

        void parentSize(const math::rect &parentRect);

        vec2 getValue() const;

        Offset getHorizontalOffset() const;

        Offset getVerticalOffset() const;

    private:
        vec2 m_value;
        Offset m_horizontalOffset;
        Offset m_verticalOffset;
    };
}

namespace nlohmann
{
    using games::benice::ui::UiPoint;

    template<>
    struct adl_serializer<UiPoint>
    {
        static void to_json(json &j, const UiPoint &obj)
        {
            j["horizontalOffset"] = obj.getHorizontalOffset();
            j["verticalOffset"] = obj.getVerticalOffset();
        }

        static void from_json(const json &j, UiPoint &obj)
        {
            obj.initialize(j["horizontalOffset"].get<Offset>(), j["verticalOffset"].get<Offset>());
        }
    };
}

