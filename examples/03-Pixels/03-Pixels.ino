
#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#include "ESP_Color.h"

// NeoPixel variables
#ifdef ARDUINO_M5Stack_ATOM
#define PIXEL_PIN 32 // MOSI
#define BUTTON_PIN 36
#else
// user defined pin
#define PIXEL_PIN 7 // MOSI
#define BUTTON_PIN 10
#endif

#define NUM_PIXELS 45
#define PALETTE_SIZE 64

unsigned long milli_sec;
float clock_sec;
unsigned int loop_count = 0;

float intensity[NUM_PIXELS];               // cache for shape intensity
ESP_Color::Color color_caches[NUM_PIXELS]; // color cache
float pixel_x[NUM_PIXELS];                 // pixel x-position

Adafruit_NeoPixel pixels(NUM_PIXELS, PIXEL_PIN, NEO_GRB + NEO_KHZ800);
ESP_Color::Palette<uint16_t> palette(ESP_Color::Palettes64::HSV_64,
                                     PALETTE_SIZE);

void setup()
{
    pinMode(PIXEL_PIN, OUTPUT);

    Serial.begin(115200);

    digitalWrite(PIXEL_PIN, LOW);
    pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
    pixels.setBrightness(128);
    pixels.show(); // Turn OFF all pixels

    loop_count = 0;
    for (size_t i = 0; i < NUM_PIXELS; i++)
    {
        pixel_x[i] = static_cast<float>(i) / NUM_PIXELS;
    }

} // end of setup

void loop()
{
    // update clock
    milli_sec = millis();
    clock_sec = milli_sec * 1.0e-3f;

    float v = ESP_COLOR::beat::beatSaw(clock_sec, 0.5f);

    ESP_Color::spatial::wipeQuad(v, pixel_x, intensity, NUM_PIXELS);
    for (size_t i = 0; i < NUM_PIXELS; i++)
    {
        auto index = (int)(PALETTE_SIZE * intensity[i]) % PALETTE_SIZE;
        color_caches[i] = ESP_Color::Color(palette[index]);
    }
    for (uint16_t i = 0; i < pixels.numPixels(); i++)
    {
        pixels.setPixelColor(i, color_caches[i].ToRgb888());
    }

    pixels.show();
    delay(33); // about 30 FPS
    loop_count++;
}
