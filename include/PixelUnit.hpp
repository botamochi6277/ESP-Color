#ifndef PIXEL_UNIT_HPP
#define PIXEL_UNIT_HPP

#include <math.h>
#include "ESP_Color.h"
namespace ESP_Color::spatial
{

    class PixelUnit
    {
    private:
        float position_;

    public:
        ESP_Color::Color color;

        PixelUnit();
        PixelUnit(float red, float green, float blue, float position);
        PixelUnit(unsigned int hexcolor, float position);
        // void setCmapColor(float intensity, ColormapId cmap,
        //                   float initial_phase = 0.0f);
        void setPosition(float position);
        void blendFromAnchors(PixelUnit &anchor1, PixelUnit &anchor2);

        float position();
    };

    PixelUnit::PixelUnit()
    {
        this->color = ESP_Color::Color(0.0f, 0.0f, 0.0f);
        this->setPosition(0.0f);
    }
    PixelUnit::PixelUnit(float red, float green, float blue, float position)
    {
        this->color = ESP_Color::Color(red, green, blue);
        this->setPosition(position);
    }
    PixelUnit::PixelUnit(unsigned int hexcolor, float position)
    {
        this->color = ESP_Color::Color(hexcolor);
        this->setPosition(position);
    }

    // void PixelUnit::setCmapColor(float intensity, ColormapId cmap,
    //                              float initial_phase)
    // {
    //     assignColorWithColormap(this->color.R, this->color.G, this->color.B,
    //                             intensity, cmap);
    // }

    float PixelUnit::position() { return this->position_; }
    void PixelUnit::setPosition(float position) { this->position_ = position; }

    void PixelUnit::blendFromAnchors(PixelUnit &anchor1, PixelUnit &anchor2)
    {
        float distance1 = abs(anchor1.position() - this->position_);
        float distance2 = abs(anchor2.position() - this->position_);
        float score1 = 1.0f / (distance1 + 1e-9f);
        float score2 = 1.0f / (distance2 + 1e-9f);
        float weight1 = score1 / (score1 + score2);
        float weight2 = score2 / (score1 + score2);

        // blend with weight
        // rgb blending
        this->color.R = weight1 * anchor1.color.R + weight2 * anchor2.color.R;
        this->color.G = weight1 * anchor1.color.G + weight2 * anchor2.color.G;
        this->color.B = weight1 * anchor1.color.B + weight2 * anchor2.color.B;
    }

} // namespace spatial_color
#endif