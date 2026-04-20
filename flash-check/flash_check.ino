#include <ESP8266WiFi.h>

void setup() {
  Serial.begin(115200);
  delay(1000);

  uint32_t flashSize = ESP.getFlashChipSize();
  uint32_t flashRealSize = ESP.getFlashChipRealSize();
  uint32_t sketchSize = ESP.getSketchSize();
  uint32_t freeSketchSpace = ESP.getFreeSketchSpace();

  Serial.println("=== Info Flash Memory ===");
  Serial.printf("Flash Size (config) : %d bytes (%.1f MB)\n", flashSize, flashSize / 1048576.0);
  Serial.printf("Flash Size (real)   : %d bytes (%.1f MB)\n", flashRealSize, flashRealSize / 1048576.0);
  Serial.printf("Sketch Size         : %d bytes\n", sketchSize);
  Serial.printf("Free Sketch Space   : %d bytes\n", freeSketchSpace);
}

void loop() {}