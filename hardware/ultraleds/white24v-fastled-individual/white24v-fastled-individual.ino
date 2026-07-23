#include <FastLED.h>

#define DATA_PIN    6
#define NUM_LEDS    6   // 6 pixels for the 0.5m N1217 sample
#define BRIGHTNESS  150

CRGB leds[NUM_LEDS];

void setup() {
  // Corrected driver definition for the 16-bit UCS7604 chip
  FastLED.addLeds<UCS7604, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  
  FastLED.clear();
  FastLED.show();
}

void loop() {
  // 1. STEP THROUGH EACH PIXEL IN RED
  for (int i = 0; i < NUM_LEDS; i++) {
    FastLED.clear();              // Turn off all previous pixels
    leds[i] = CRGB::Red;          // Set current pixel to Red
    FastLED.show();
    delay(300);                   // Pause to watch each pixel light up
  }

  // 2. STEP THROUGH EACH PIXEL IN GREEN
  for (int i = 0; i < NUM_LEDS; i++) {
    FastLED.clear();
    leds[i] = CRGB::Green;
    FastLED.show();
    delay(300);
  }

  // 3. STEP THROUGH EACH PIXEL IN BLUE
  for (int i = 0; i < NUM_LEDS; i++) {
    FastLED.clear();
    leds[i] = CRGB::Blue;
    FastLED.show();
    delay(300);
  }

  // 4. STEP THROUGH EACH PIXEL IN WARM WHITE
  for (int i = 0; i < NUM_LEDS; i++) {
    FastLED.clear();
    // Warm White mix (Red + Green + soft Blue)
    leds[i] = CRGB(255, 180, 60);
    FastLED.show();
    delay(300);
  }

  // Brief pause off before repeating
  FastLED.clear();
  FastLED.show();
  delay(1000);
}