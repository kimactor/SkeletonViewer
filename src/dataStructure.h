#pragma once
#include <iostream>
#include "GLFW/glfw3.h"
#include <GL/freeglut.h>

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

    // Struct for managing rotation of pointcloud view
    struct glfw_state {
        glfw_state(float yaw = 15.0, float pitch = 15.0) : yaw(yaw), pitch(pitch), last_x(0.0), last_y(0.0),
            ml(false), offset_x(2.f), offset_y(2.f) {}
        double yaw;
        double pitch;
        double last_x;
        double last_y;
        bool ml;
        float offset_x;
        float offset_y;
        //Texture tex;
    };


}
