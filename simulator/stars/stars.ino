#include <Adafruit_NeoPixel.h>

// ==========================================
// CONFIGURATION SETTINGS
// ==========================================

#define PIN_STRIP_1 5
#define PIN_STRIP_2 6

#define NUM_LEDS_STRIP_1 600
#define NUM_LEDS_STRIP_2 600

#define TOTAL_LEDS (NUM_LEDS_STRIP_1 + NUM_LEDS_STRIP_2)

// Frequency of updates
#define LOOP_DELAY_MS 25

#define BRIGHTNESS 60

// ==========================================
// NEOPIXEL INITIALIZATION
// ==========================================

Adafruit_NeoPixel strip1(NUM_LEDS_STRIP_1, PIN_STRIP_1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2(NUM_LEDS_STRIP_2, PIN_STRIP_2, NEO_GRB + NEO_KHZ800);

// ==========================================
// VIRTUAL LED ARRAY ABSTRACTION LAYER
// ==========================================

void setVirtualPixel(int index, uint32_t color) {
  if (index < 0 || index >= TOTAL_LEDS) return;
  if (index < NUM_LEDS_STRIP_1) {
    strip1.setPixelColor(index, color);
  } else {
    strip2.setPixelColor(index - NUM_LEDS_STRIP_1, color);
  }
}

uint32_t getVirtualPixel(int index) {
  if (index < 0 || index >= TOTAL_LEDS) return 0;
  if (index < NUM_LEDS_STRIP_1) {
    return strip1.getPixelColor(index);
  } else {
    return strip2.getPixelColor(index - NUM_LEDS_STRIP_1);
  }
}

void showAllStrips() {
  strip1.show();
  strip2.show();
}

void clearAllStrips() {
  for (int i = 0; i < TOTAL_LEDS; i++) {
    setVirtualPixel(i, 0);
  }
  showAllStrips();
}

// ==========================================
// SETUP & LOOP
// ==========================================

void setup() {
  strip1.begin();
  strip1.setBrightness(BRIGHTNESS);
  strip2.begin();
  strip2.setBrightness(BRIGHTNESS);
  clearAllStrips();
  
  // Seed random number generator using open analog pin
  randomSeed(analogRead(0));
}

void loop() {
  // 1. Fade all pixels slowly to black to create trails
  for (int i = 0; i < TOTAL_LEDS; i++) {
    uint32_t c = getVirtualPixel(i);
    uint8_t r = (c >> 16) & 0xFF;
    uint8_t g = (c >> 8) & 0xFF;
    uint8_t b = c & 0xFF;
    
    r = r * 9 / 10;
    g = g * 9 / 10;
    b = b * 9 / 10;
    
    setVirtualPixel(i, strip1.Color(r, g, b));
  }

  // 2. Randomly spark a few new pixels
  if (random(100) < 30) {
    int sparklesToCreate = random(1, 4);
    for(int s = 0; s < sparklesToCreate; s++) {
      int randIdx = random(TOTAL_LEDS);
      int colorType = random(3);
      uint32_t sparkColor;
      
      if (colorType == 0) {
        sparkColor = strip1.Color(255, 255, 255); // White
      } else if (colorType == 1) {
        sparkColor = strip1.Color(255, 200, 50);  // Gold
      } else {
        sparkColor = strip1.Color(100, 200, 255); // Blue
      }
      
      setVirtualPixel(randIdx, sparkColor);
    }
  }

  showAllStrips();
  delay(LOOP_DELAY_MS);
}