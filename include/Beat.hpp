#ifndef BOTAMOCHI_BEAT_HPP
#define BOTAMOCHI_BEAT_HPP

#include <Arduino.h>
namespace ESP_COLOR::beat
{

    float beatSin(float t, float frequency = 1.0f, float initial_phase = 0.0f, float amplitude = 0.5f, float dc = 0.5f)
    {
        return amplitude * sinf(2.0f * M_PI * frequency * t + initial_phase) + dc;
    }

    float beatSaw(float t, float frequency = 1.0f)
    {
        return frequency * t - floorf(frequency * t);
    }

} // namespace ESP_COLOR::beat

#endif