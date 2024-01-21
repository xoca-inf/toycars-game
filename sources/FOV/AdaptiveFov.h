#pragma once

#include "W4Math.h"

/**
 *  https://github.com/Calinou/fov source of math
 */
namespace games::benice::utils
{
    class AdaptiveFov
    {
    public:
        static constexpr float DEFAULT_HFOV = 60.0f;
        static constexpr float DEFAULT_VFOV = 60.0f;

        static constexpr float HALF_DEG2RAD = w4::math::PI / 360.0f;
        static constexpr float DOUBLE_RAD2DEG = 360.0f / w4::math::PI;

        static float getAdaptiveFov (float aspect)
        {
            if (aspect <= 1.0f)
            {
                return DEFAULT_HFOV;
            }

            float hFov = atan(tan(DEFAULT_VFOV * HALF_DEG2RAD)) * DOUBLE_RAD2DEG;
            float hFovNew = atan(tan(hFov * HALF_DEG2RAD) * aspect) * DOUBLE_RAD2DEG;
            return hFovNew;
        }

        static float getAdaptiveFov (w4::math::size sz)
        {
            return getAdaptiveFov((float) sz.w / (float) sz.h);
        }

        static float getAdaptiveFov (w4::math::ivec2 sz)
        {
            return getAdaptiveFov((float) sz.w / (float) sz.h);
        }
    };
}