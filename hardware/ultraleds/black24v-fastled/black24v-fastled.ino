#include <FastLED.h>

#define DATA_PIN    6
#define NUM_LEDS    10   // Adjust to match your 0.5m sample length
#define BRIGHTNESS  150

CRGB leds[NUM_LEDS];

void setup() {
  // WS2811 protocol handles GS8206 / UCS1903 / UCS2903 24V pixels seamlessly
  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear();
  FastLED.show();
}

void loop() {
  // 1. RED
  fill_solid(leds, NUM_LEDS, CRGB::Red);
  FastLED.show();
  delay(1000);

  // 2. GREEN
  fill_solid(leds, NUM_LEDS, CRGB::Green);
  FastLED.show();
  delay(1000);

  // 3. BLUE
  fill_solid(leds, NUM_LEDS, CRGB::Blue);
  FastLED.show();
  delay(1000);
}