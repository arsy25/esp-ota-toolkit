#include <ESP8266WiFi.h>
#include <WiFiManager.h>      
#include <ArduinoOTA.h>

// =====================
// PIN CONFIG
// =====================
#define TRIG_PIN D6
#define ECHO_PIN D7

// =====================
// OTA CONFIG
// =====================
#define OTA_HOSTNAME "esp8266-ultrasonic"
#define OTA_PASSWORD "admin1234"

// =====================
// VARIABLES
// =====================
long duration;
float distanceCm;
unsigned long lastRead = 0;
const unsigned long readInterval = 500; // read every 500ms

// =====================
// READ DISTANCE FUNCTION
// =====================
float readDistance() {
  // Send trigger pulse
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Read echo
  duration = pulseIn(ECHO_PIN, HIGH, 30000); // timeout 30ms

  if (duration == 0) {
    return -1; // no object detected / timeout
  }

  // Calculate distance (cm)
  return (duration * 0.0343) / 2;
}

// =====================
// SETUP
// =====================
void setup() {
  Serial.begin(115200);
  Serial.println("\n\n=== Ultrasonic Monitor + OTA ===");

  // Setup ultrasonic pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // -------------------------
  // WiFiManager (tzapu)
  // -------------------------
  WiFiManager wifiManager;

  // Uncomment this line to reset saved WiFi credentials (for testing)
  // wifiManager.resetSettings();

  wifiManager.setAPStaticIPConfig(
    IPAddress(192, 168, 4, 1),
    IPAddress(192, 168, 4, 1),
    IPAddress(255, 255, 255, 0)
  );

  Serial.println("[WiFi] Connecting to WiFi...");

  // If connection fails, open Access Point "ESP8266-Setup"
  // Open browser → 192.168.4.1 → select WiFi & enter password
  if (!wifiManager.autoConnect("ESP8266-Setup")) {
    Serial.println("[WiFi] Connection failed! Restarting...");
    delay(3000);
    ESP.restart();
  }

  Serial.println("[WiFi] Connected!");
  Serial.print("[WiFi] IP Address: ");
  Serial.println(WiFi.localIP());

  // -------------------------
  // OTA Setup
  // -------------------------
  ArduinoOTA.setHostname(OTA_HOSTNAME);
  ArduinoOTA.setPassword(OTA_PASSWORD);

  ArduinoOTA.onStart([]() {
    String type = (ArduinoOTA.getCommand() == U_FLASH) ? "sketch" : "filesystem";
    Serial.println("[OTA] Starting update: " + type);
  });

  ArduinoOTA.onEnd([]() {
    Serial.println("\n[OTA] Update complete! Restarting...");
  });

  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("[OTA] Progress: %u%%\r", (progress / (total / 100)));
  });

  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("[OTA] Error[%u]: ", error);
    if      (error == OTA_AUTH_ERROR)    Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR)   Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR)     Serial.println("End Failed");
  });

  ArduinoOTA.begin();
  Serial.println("[OTA] Ready!");
  Serial.printf("[OTA] Hostname : %s\n", OTA_HOSTNAME);
  Serial.printf("[OTA] Password : %s\n", OTA_PASSWORD);
  Serial.println("================================\n");
}

// =====================
// LOOP
// =====================
void loop() {
  // Required to keep OTA running
  ArduinoOTA.handle();

  // Read sensor every interval
  if (millis() - lastRead >= readInterval) {
    lastRead = millis();

    distanceCm = readDistance();

    if (distanceCm == -1) {
      Serial.println("[Sensor] No object detected / timeout");
    } else {
      Serial.printf("[Sensor] Distance: %.2f cm", distanceCm);

      // Distance classification
      if (distanceCm < 10) {
        Serial.println("  WARNING: TOO CLOSE!");
      } else if (distanceCm < 30) {
        Serial.println("  NEAR");
      } else if (distanceCm < 100) {
        Serial.println("  NORMAL");
      } else {
        Serial.println("  FAR");
      }
    }
  }
}