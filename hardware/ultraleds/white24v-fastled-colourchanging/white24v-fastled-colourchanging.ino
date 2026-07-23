#include <FastLED.h>

#define DATA_PIN    6
#define NUM_LEDS    6   // 6 logical clusters for 0.5m N1217 sample
#define BRIGHTNESS  150

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<UCS7604, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  
  FastLED.clear();
  FastLED.show();
}

void loop() {
  // ----------------------------------------------------------------
  // TEST 1: SPATIAL GRADIENT (Gradient mapped across the 6 clusters)
  // ----------------------------------------------------------------
  // Holds static or slow-shifting gradients across the physical length
  // so you can closely examine the 83.3mm cluster boundaries.
  
  for (int step = 0; step < 256; step++) {
    for (int i = 0; i < NUM_LEDS; i++) {
      // Calculate a hue offset across the 6 clusters + animated shift over time
      uint8_t hue = (i * (255 / NUM_LEDS)) + step;
      leds[i] = CHSV(hue, 240, 255);
    }
    FastLED.show();
    delay(30); // Adjust speed of the spatial rainbow wave
  }

  // ----------------------------------------------------------------
  // TEST 2: TEMPORAL GRADIENT (Smooth Color Fades & Breathing)
  // ----------------------------------------------------------------
  // Fades smoothly between Red -> Warm White -> Blue -> Teal -> Red
  // to evaluate dimming resolution and color transition fluidity.

  // Fade 1: Red to Warm White
  fadeBetweenColors(CRGB(255, 0, 0), CRGB(255, 180, 60), 1000);
  delay(500);

  // Fade 2: Warm White to Deep Blue
  fadeBetweenColors(CRGB(255, 180, 60), CRGB(0, 30, 255), 1000);
  delay(500);

  // Fade 3: Deep Blue to Teal
  fadeBetweenColors(CRGB(0, 30, 255), CRGB(0, 220, 180), 1000);
  delay(500);

  // Fade 4: Teal back to Red
  fadeBetweenColors(CRGB(0, 220, 180), CRGB(255, 0, 0), 1000);
  delay(1000);
}

// Helper function to interpolate smoothly between two exact CRGB colors
void fadeBetweenColors(CRGB startColor, CRGB endColor, int durationMs) {
  int steps = 100;
  int stepDelay = durationMs / steps;

  for (int i = 0; i <= steps; i++) {
    // blend() interpolates smoothly between startColor and endColor (0 to 255 scale)
    uint8_t fraction = map(i, 0, steps, 0, 255);
    CRGB currentColor = blend(startColor, endColor, fraction);

    // Fill all 6 clusters with the blended color
    fill_solid(leds, NUM_LEDS, currentColor);
    FastLED.show();
    delay(stepDelay);
  }
}