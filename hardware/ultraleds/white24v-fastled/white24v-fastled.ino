#include <FastLED.h>

#define DATA_PIN    6
#define NUM_LEDS    6  // 6 pixels for 0.5m sample
#define BRIGHTNESS  150

CRGB leds[NUM_LEDS];

void setup() {
  // Uses FastLED's UCS7604 driver (handles preamble and 8-bit mode mapping)
  FastLED.addLeds<UCS7604, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear();
  FastLED.show();
}

void loop() {
  fill_solid(leds, NUM_LEDS, CRGB::Red);
  FastLED.show();
  delay(1000);

  fill_solid(leds, NUM_LEDS, CRGB::Green);
  FastLED.show();
  delay(1000);

  fill_solid(leds, NUM_LEDS, CRGB::Blue);
  FastLED.show();
  delay(1000);
}