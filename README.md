# esp-ota-toolkit

A beginner-friendly toolkit for getting started with **Over-The-Air (OTA) firmware updates** on ESP8266 and ESP32. This repository contains simple, well-commented example sketches to help you understand flash memory and set up wireless firmware updates with ease.

> The sensor code (ultrasonic) is just a **placeholder** to demonstrate OTA in a real-world context. You can swap it with any sensor or logic you need.

---

## 📁 Repository Structure

```
esp-ota-toolkit/
├── README.md
├── 1_flash_check/
│   └── flash_check.ino        # Check flash memory size and availability
└── 2_ota_monitor/
    └── ota_monitor.ino        # OTA-ready sketch with WiFiManager + sensor placeholder
```

---

## 📋 Sketches

### 1. `flash_check`
Reads and displays flash memory information via Serial Monitor.
Useful to verify your board has enough space before setting up OTA.

**Output example:**
```
=== Flash Memory Info ===
Flash Size (config) : 4194304 bytes (4.0 MB)
Flash Size (real)   : 4194304 bytes (4.0 MB)
Sketch Size         : 285408 bytes
Free Sketch Space   : 2793472 bytes
OTA Status          : OK - Enough space for OTA
```

---

### 2. `ota_monitor`
A full OTA-ready sketch using:
- **WiFiManager (tzapu)** — connect to WiFi without hardcoding credentials
- **ArduinoOTA** — receive firmware updates wirelessly
- **Sensor placeholder** — ultrasonic sensor (HC-SR04) as an example, swap with your own

**Serial Monitor output example:**
```
=== Ultrasonic Monitor + OTA ===
[WiFi] Connecting to WiFi...
[WiFi] Connected!
[WiFi] IP Address: 192.168.1.105
[OTA] Ready!
[OTA] Hostname : esp8266-ultrasonic
================================

[Sensor] Distance: 25.10 cm  NEAR
[Sensor] Distance: 67.80 cm  NORMAL
```

---

## 🛠️ Requirements

### Hardware
- ESP8266 (NodeMCU, Wemos D1 Mini, etc.) **or** ESP32
- HC-SR04 Ultrasonic Sensor *(for `ota_monitor` placeholder)*
- USB cable *(for first upload only)*

### Software
- [Arduino IDE](https://www.arduino.cc/en/software)
- ESP8266 or ESP32 board package installed
- Libraries:
  - `WiFiManager` by tzapu — install via Library Manager
  - `ArduinoOTA` — built-in with ESP board packages

---

## ⚡ Wiring (HC-SR04 Placeholder)

| HC-SR04 | ESP8266 (NodeMCU) |
|---------|-------------------|
| VCC     | 3.3V or 5V        |
| GND     | GND               |
| TRIG    | D6                |
| ECHO    | D7                |

> ⚠️ If powering HC-SR04 with 5V, use a **voltage divider** on the ECHO pin since ESP8266 is 3.3V tolerant only.

---

## 🚀 How to Use

### First Time (USB Required)
1. Open `ota_monitor.ino` in Arduino IDE
2. Select your board and COM port under **Tools**
3. Upload via USB cable
4. Open Serial Monitor at **115200 baud**

### Connecting to WiFi (WiFiManager)
1. ESP8266 will create an Access Point: **`ESP8266-Setup`**
2. Connect your phone or laptop to that WiFi network
3. Open browser → go to **`192.168.4.1`**
4. Select your WiFi network and enter the password
5. ESP8266 will restart and connect automatically

### Future Updates (OTA / Wireless)
1. Make sure your laptop is on the **same WiFi network** as the ESP
2. Open your updated sketch in Arduino IDE
3. Go to **Tools → Port** and select the network port:
   ```
   Network ports:
     esp8266-ultrasonic at 192.168.1.xxx
   ```
4. Click **Upload** and enter OTA password: `admin1234`
5. Done! ESP will restart with the new firmware automatically

---

## ⚠️ Important Notes

- Every new firmware version **must include OTA code**, otherwise you lose wireless update capability and need USB again
- `ArduinoOTA.handle()` must always be called inside `loop()`
- For OTA to work, free sketch space must be **≥ sketch size** (use `flash_check` to verify)
- ESP8266 only supports **2.4GHz WiFi** (not 5GHz)

---

## 🔧 OTA Configuration

| Parameter | Value |
|-----------|-------|
| Hostname  | `esp8266-ultrasonic` |
| Password  | `admin1234` |
| AP Name   | `ESP8266-Setup` |
| AP IP     | `192.168.4.1` |

> Change these values in the sketch before uploading for security.

---

## 📄 License

MIT License — free to use, modify, and distribute.

---

## 🤝 Contributing

Pull requests are welcome! Feel free to swap out the sensor placeholder with your own hardware and share it back.