#include <Adafruit_NeoPixel.h>

// ==========================================
// CONFIGURATION SETTINGS
// ==========================================

// Define the GPIO pins connected to your two LED strips
#define PIN_STRIP_1 5
#define PIN_STRIP_2 6

// Define the number of LEDs on each pin
#define NUM_LEDS_STRIP_1 600
#define NUM_LEDS_STRIP_2 600

// Total size of the combined virtual array (1200 LEDs)
#define TOTAL_LEDS (NUM_LEDS_STRIP_1 + NUM_LEDS_STRIP_2)

// Define the delay (in milliseconds) between lighting up consecutive LEDs
#define STEP_DELAY_MS 5

// Define the brightness (0 to 255)
// Keep this value conservative (e.g., 30-80) during initial testing
// to avoid drawing excessive current from your power supply.
#define BRIGHTNESS 50

// ==========================================
// NEOPIXEL INITIALIZATION
// ==========================================

Adafruit_NeoPixel strip1(NUM_LEDS_STRIP_1, PIN_STRIP_1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2(NUM_LEDS_STRIP_2, PIN_STRIP_2, NEO_GRB + NEO_KHZ800);

// ==========================================
// VIRTUAL LED ARRAY ABSTRACTION LAYER
// ==========================================

/**
 * Sets the color of an LED using a single virtual index (0 to TOTAL_LEDS - 1).
 * This function handles the routing of pixels to the correct physical strip.
 */
void setVirtualPixel(int index, uint32_t color) {
  if (index < 0 || index >= TOTAL_LEDS) {
    return; // Out of bounds safety check
  }
  
  if (index < NUM_LEDS_STRIP_1) {
    // Pixel is on the first strip
    strip1.setPixelColor(index, color);
  } else {
    // Pixel is on the second strip (offset index by length of first strip)
    strip2.setPixelColor(index - NUM_LEDS_STRIP_1, color);
  }
}

/**
 * Pushes the updated color data out to both physical LED strips.
 */
void showAllStrips() {
  strip1.show();
  strip2.show();
}

/**
 * Turns off all pixels in the virtual array.
 */
void clearAllStrips() {
  for (int i = 0; i < TOTAL_LEDS; i++) {
    setVirtualPixel(i, 0); // 0 (or strip1.Color(0,0,0)) turns pixel off
  }
  showAllStrips();
}

// ==========================================
// ARDUINO SETUP & LOOP
// ==========================================

void setup() {
  // Initialize Serial Communication
  Serial.begin(115200);
  delay(1000); // Wait for Serial Monitor to connect
  
  Serial.println("\n==============================================");
  Serial.println("    ESP32-S3 Zero Virtual LED Array Test      ");
  Serial.println("==============================================");
  Serial.printf("Strip 1 (Physical): Pin %d with %d LEDs\n", PIN_STRIP_1, NUM_LEDS_STRIP_1);
  Serial.printf("Strip 2 (Physical): Pin %d with %d LEDs\n", PIN_STRIP_2, NUM_LEDS_STRIP_2);
  Serial.printf("Virtual Array (Abstracted): 0 to %d (Total %d LEDs)\n\n", TOTAL_LEDS - 1, TOTAL_LEDS);

  // Initialize physical strips
  strip1.begin();
  strip1.setBrightness(BRIGHTNESS);

  strip2.begin();
  strip2.setBrightness(BRIGHTNESS);

  clearAllStrips();
  Serial.println("Initialization complete! Starting test loop.");
}

void loop() {
  Serial.println("\nStarting test sequence...");

  // Step 1: Turn all pixels off
  Serial.println("Clearing all virtual pixels...");
  clearAllStrips();
  delay(1000); // Wait 1 second before starting animation

  // Step 2: Step through the virtual array (0 to TOTAL_LEDS - 1)
  Serial.printf("Stepping through all %d LEDs sequentially (Red)...\n", TOTAL_LEDS);
  for (int i = 0; i < TOTAL_LEDS; i++) {
    uint32_t red = strip1.Color(255, 0, 0); // Generate Red color value
    setVirtualPixel(i, red);
    showAllStrips();
    delay(STEP_DELAY_MS);
  }

  // Step 3: Hold the completed state
  Serial.println("All LEDs are now RED. Holding state for 2 seconds...");
  delay(2000);
}
