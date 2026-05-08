
# 🔷 How to Run ESP32 Arduino Project (Shurokkha)

## 1. Requirements

Before running the project, ensure you have:

* Arduino IDE installed
* ESP32 development board
* USB data cable
* Required libraries installed:

  * TinyGPS++
  * Adafruit SSD1306
  * Adafruit GFX

---

## 2. Install ESP32 Board in Arduino IDE

1. Open Arduino IDE
2. Go to **File → Preferences**
3. Paste this URL in “Additional Board Manager URLs”:

```
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
```

4. Go to **Tools → Board → Board Manager**
5. Search **ESP32** and install it

---

## 3. Select Board and Port

1. Go to **Tools → Board → ESP32 Dev Module**
2. Go to **Tools → Port → Select COM Port** (ESP32 connected port)

---

## 4. Open the Project Code

* Open your `.ino` file in Arduino IDE
* Check all code properly loaded

---

## 5. Compile the Code

* Click the **Verify (✔)** button
* Wait for compilation
* Fix errors if shown

---

## 6. Upload the Code

* Click the **Upload (→)** button
* If upload fails, press and hold **BOOT button on ESP32** during upload

---

## 7. After Upload

Once uploaded successfully:

* ESP32 will restart automatically
* OLED shows “System Ready”
* GPS starts collecting location data
* GSM module waits for SOS trigger

---

## 8. System Testing

* Press the SOS button
* System will:

  * Read GPS location
  * Send SMS via GSM
  * Show status on OLED
  * Activate buzzer (if audible mode enabled)

---

## 9. Common Issues

* Wrong COM port → upload fails
* GPS takes time → needs outdoor signal
* GSM not working → check SIM balance and signal

---



“The ESP32 firmware is developed and uploaded using Arduino IDE, and the system executes automatically upon power-up to handle real-time SOS emergency operations.”


