#include <Adafruit_NeoPixel.h>

// ==========================================
// CONFIGURATION SETTINGS
// ==========================================

#define PIN_STRIP_1 5
#define PIN_STRIP_2 6

#define NUM_LEDS_STRIP_1 600
#define NUM_LEDS_STRIP_2 600

#define TOTAL_LEDS (NUM_LEDS_STRIP_1 + NUM_LEDS_STRIP_2)

// Frame delay in milliseconds
#define LOOP_DELAY_MS 50

#define BRIGHTNESS 61

// ==========================================
// NEOPIXEL INITIALIZATION
// ==========================================

Adafruit_NeoPixel strip1(NUM_LEDS_STRIP_1, PIN_STRIP_1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2(NUM_LEDS_STRIP_2, PIN_STRIP_2, NEO_GRB + NEO_KHZ800);

unsigned long lastUpdate = 0;
float flowPosition = 0;
float tidePhase = 0;

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
}

void loop() {
  if (millis() - lastUpdate >= LOOP_DELAY_MS) {
    lastUpdate = millis();
    
    // 1. Advance the tidal phase cycle (slow sine wave modulation)
    tidePhase += 0.001; 
    if (tidePhase >= TWO_PI) tidePhase = 0;
    
    // 2. Flow speed oscillates between positive (downstream) and negative (upstream)
    float flowSpeed = sin(tidePhase) * 1.5;
    flowPosition += flowSpeed;
    
    // 3. speedMagnitude represents water agitation (for foam/light reflection)
    float speedMagnitude = abs(flowSpeed);
    
    // 4. Calculate color for each virtual pixel
    for (int i = 0; i < TOTAL_LEDS; i++) {
      // Overlapping sine waves moving relative to the tide flowPosition
      float wave1 = (sin(i * 0.03 - flowPosition) + 1.0) / 2.0;
      float wave2 = (sin(i * 0.08 - flowPosition * 1.3 + PI) + 1.0) / 2.0;
      float riverVal = (wave1 + wave2) / 2.0;
      
      // Interpolate colors: Calm Deep Blue -> Teal/Cyan -> White Foam
      // High speed magnitude introduces more foam (r and g channels rise)
      uint8_t r = (uint8_t)(riverVal * 120.0 * speedMagnitude);
      uint8_t g = (uint8_t)(20.0 + riverVal * 180.0 * speedMagnitude);
      uint8_t b = (uint8_t)(100.0 + riverVal * 155.0);
      
      setVirtualPixel(i, strip1.Color(r, g, b));
    }
    
    showAllStrips();
  }
}