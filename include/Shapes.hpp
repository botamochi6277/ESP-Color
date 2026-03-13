// Shape functions
#ifndef BOTAMOCHI_SHAPES_HPP
#define BOTAMOCHI_SHAPES_HPP
#include <Arduino.h>

#include "Easing.hpp"
namespace ESP_Color::spatial
{

    void heat(float t, float x[], float intensity[], uint16_t num_pixels)
    {
        for (size_t i = 0; i < num_pixels; i++)
        {
            intensity[i] = t;
        }
    }

    void wipeQuad(float t, float x[], float intensity[], uint16_t num_pixels,
                  float blur_width = 0.25f)
    {
        for (uint16_t index = 0; index < num_pixels; index++)
        {
            auto tt = t - (x[index] / (1.0f + 2.0f * blur_width));

            intensity[index] = easing::quadInOut(tt, blur_width);
        }
    }

    void pulseQuad(float t, float x[], float intensity[], uint16_t num_pixels,
                   float pulse_width = 0.25f)
    {
        // pulse_width 0--1.0 relative length to pixels length
        auto a =
            easing::remap((1.0f - abs(t)), 0.0f, 1.0f, -1.0f * 0.5f * pulse_width,
                          1.0f + 0.5f * pulse_width);
        float v = 1.0f + 3.5f * pulse_width;

        for (uint16_t index = 0; index < num_pixels; index++)
        {
            float tt = (t - pulse_width) - x[index] / v;
            intensity[index] =
                (easing::quadInOut(tt + 0.5f * pulse_width, 0.5f * pulse_width) -
                 easing::quadInOut(tt - 0.5f * pulse_width, 0.5f * pulse_width));
        }
    }

    void waveSaw(float t, float x[], float intensity[], uint16_t num_pixels)
    {
        static float v = 1.001f;
        for (size_t i = 0; i < num_pixels; i++)
        {
            intensity[i] = ceilf(t - x[i] / v) - (t - x[i] / v);
        }
    }

    void waveSine(float t, float x[], float intensity[], uint16_t num_pixels)
    {
        for (size_t i = 0; i < num_pixels; i++)
        {
            intensity[i] = (0.5f * (sinf(2.0f * M_PI * 1.0f * (t - x[i]))) + 0.5f);
        }
    }

} // namespace spatial_color::shape

#endif