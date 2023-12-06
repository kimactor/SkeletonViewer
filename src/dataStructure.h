#pragma once
#include <iostream>

namespace SkeletonViewerApplication
{
    struct float3 {
        float x, y, z;
        float3 operator*(float t)
        {
            return { x * t, y * t, z * t };
        }

        float3 operator-(float t)
        {
            return { x - t, y - t, z - t };
        }

        void operator*=(float t)
        {
            x = x * t;
            y = y * t;
            z = z * t;
        }

        void operator=(float3 other)
        {
            x = other.x;
            y = other.y;
            z = other.z;
        }

        void add(float t1, float t2, float t3)
        {
            x += t1;
            y += t2;
            z += t3;
        }
    };
    struct float2 { float x, y; };

    struct rect
    {
        float x, y;
        float w, h;

        // Create new rect within original boundaries with give aspect ration
        rect adjust_ratio(float2 size) const
        {
            auto H = static_cast<float>(h), W = static_cast<float>(h) * size.x / size.y;
            if (W > w)
            {
                auto scale = w / W;
                W *= scale;
                H *= scale;
            }

            return{ x + (w - W) / 2, y + (h - H) / 2, W, H };
        }
    };
}
