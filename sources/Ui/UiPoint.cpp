#include "UiPoint.h"

namespace games::benice::ui
{
    UiPoint::UiPoint(const Offset &h, const Offset &v) : m_horizontalOffset(h), m_verticalOffset(v), m_value(vec2(0, 0))
    {
    }

    UiPoint::~UiPoint()
    {}

    vec2 UiPoint::getValue() const
    {
        return m_value;
    };

    Offset UiPoint::getHorizontalOffset() const
    {
        return m_horizontalOffset;
    };

    Offset UiPoint::getVerticalOffset() const
    {
        return m_verticalOffset;
    }

    void UiPoint::parentSize(const math::rect &parentRect)
    {
        float x = 0;
        float y = 0;

        switch (m_horizontalOffset.pivot)
        {
            case PivotAt::LEFT:
            case PivotAt::RIGHT:
            case PivotAt::CENTER:
                x = m_horizontalOffset.calcDimension(parentRect.position.x - parentRect.size.w / 2.0, parentRect.position.x + parentRect.size.w / 2.0);
                break;
            default:
                W4_LOG_ERROR("[UiPoint] cant use PivotAt type in horizontal offset %d", (int) m_horizontalOffset.pivot);
                break;
        }

        switch (m_verticalOffset.pivot)
        {
            case PivotAt::TOP:
            case PivotAt::BOTTOM:
            case PivotAt::CENTER:
                y = m_verticalOffset.calcDimension(parentRect.position.y - parentRect.size.h / 2.0, parentRect.position.y + parentRect.size.h / 2.0);
                break;
            default:
                W4_LOG_ERROR("[UiPoint] cant use PivotAt type in vertical offset %d", (int) m_horizontalOffset.pivot);
                break;
        }

        m_value.x = x;
        m_value.y = y;

    }
}