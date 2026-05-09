# Shurokkha Project: Full Wokwi Process with Code

This guide shows you how to build a **100% Wokwi-compatible demo** of your **Shurokkha** emergency safety device.

---

# 1. Components to Add in Wokwi

Search and add these components:

1. ESP32 DevKit V1
2. SSD1306 OLED (128x64, I2C)
3. Pushbutton (SOS Button)
4. Slide Switch (Silent/Audible Mode)
5. Buzzer

---

# 2. Circuit Connections

## 2.1 OLED Connections

| OLED Pin | ESP32 Pin |
| -------- | --------- |
| VCC      | 3V3       |
| GND      | GND       |
| SDA      | GPIO21    |
| SCL      | GPIO22    |

---

## 2.2 SOS Push Button Connections

Pushbutton has 4 pins:

```text
A1    A2
B1    B2
```

* A1 and A2 are connected together.
* B1 and B2 are connected together.
* When pressed, A side connects to B side.

### Connect:

| Button Pin | ESP32 Pin |
| ---------- | --------- |
| A1         | GPIO14    |
| B1         | GND       |

---

## 2.3 Slide Switch Connections

The slide switch has 3 pins.

### Connect:

| Switch Pin | Connection    |
| ---------- | ------------- |
| Center Pin | GPIO12        |
| One Side   | GND           |
| Other Side | Not Connected |

### Logic

* Switch connected to GND → Silent Mode
* Switch open → Audible Mode

---

## 2.4 Buzzer Connections

| Buzzer Pin | ESP32 Pin |
| ---------- | --------- |
| +          | GPIO27    |
| -          | GND       |

---

# 3. Complete Wiring Diagram

```text
OLED:
VCC -> 3V3
GND -> GND
SDA -> GPIO21
SCL -> GPIO22

SOS Button:
A1  -> GPIO14
B1  -> GND

Mode Switch:
Center -> GPIO12
One Side -> GND

Buzzer:
+ -> GPIO27
- -> GND
```

---

# 4. How the System Works

1. ESP32 powers on.
2. OLED shows `System Ready`.
3. User selects mode using slide switch.
4. User presses SOS button.
5. ESP32 generates a Google Maps link using fixed GPS coordinates.
6. Serial Monitor prints the SOS message.
7. If Audible Mode is selected, buzzer sounds for 3 seconds.
8. OLED shows `SOS Sent`.
9. System returns to `System Ready`.

---

# 5. Complete Arduino Code

```cpp
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED configuration
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Pin definitions
#define SOS_BUTTON   14
#define MODE_SWITCH  12
#define BUZZER_PIN   27

// Fixed GPS coordinates (Dhaka)
float latitude  = 23.8103;
float longitude = 90.4125;

void showMessage(String line1, String line2);
void sendSOS();

void setup() {
  Serial.begin(115200);

  pinMode(SOS_BUTTON, INPUT_PULLUP);
  pinMode(MODE_SWITCH, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);

  digitalWrite(BUZZER_PIN, LOW);

  // Initialize OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED initialization failed!");
    while (true);
  }

  showMessage("Shurokkha", "System Ready");
  delay(2000);
}

void loop() {
  // Check SOS button
  if (digitalRead(SOS_BUTTON) == LOW) {
    delay(50); // debounce

    if (digitalRead(SOS_BUTTON) == LOW) {
      sendSOS();

      // Wait until button released
      while (digitalRead(SOS_BUTTON) == LOW) {
        delay(10);
      }
    }
  }
}

void sendSOS() {
  // INPUT_PULLUP logic:
  // LOW  = Silent Mode (switch connected to GND)
  // HIGH = Audible Mode (switch open)
  bool audibleMode = (digitalRead(MODE_SWITCH) == HIGH);

  String mapsLink = "https://maps.google.com/?q=" +
                    String(latitude, 6) + "," +
                    String(longitude, 6);

  if (audibleMode) {
    showMessage("Audible Mode", "Sending SOS");
  } else {
    showMessage("Silent Mode", "Sending SOS");
  }

  // Simulated SMS output
  Serial.println("\n==============================");
  Serial.println("      EMERGENCY SOS ALERT");
  Serial.println("==============================");
  Serial.print("Mode: ");
  Serial.println(audibleMode ? "Audible" : "Silent");
  Serial.println("Message: I am in danger! Please help.");
  Serial.print("Location: ");
  Serial.println(mapsLink);
  Serial.println("==============================\n");

  // Audible mode: buzzer ON
  if (audibleMode) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(3000);
    digitalWrite(BUZZER_PIN, LOW);
  }

  showMessage("SOS Sent", "Help Notified");
  delay(3000);

  showMessage("Shurokkha", "System Ready");
}

void showMessage(String line1, String line2) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(0, 15);
  display.println(line1);

  display.setCursor(0, 35);
  display.println(line2);

  display.display();
}
```

---

# 6. Required Libraries in Wokwi

When Wokwi asks for libraries, add:

* Adafruit GFX Library
* Adafruit SSD1306

---

# 7. Testing Procedure

## Silent Mode

1. Move switch to GND side.
2. Press SOS button.
3. OLED shows `Silent Mode`.
4. Serial Monitor shows SOS message.
5. Buzzer does not sound.

## Audible Mode

1. Move switch away from GND.
2. Press SOS button.
3. OLED shows `Audible Mode`.
4. Serial Monitor shows SOS message.
5. Buzzer sounds for 3 seconds.

---

# 8. Serial Monitor Output Example

```text
==============================
      EMERGENCY SOS ALERT
==============================
Mode: Audible
Message: I am in danger! Please help.
Location: https://maps.google.com/?q=23.810300,90.412500
==============================
```

---

# 9. Presentation Explanation

> In this simulation, the SOS button triggers an emergency alert. The slide switch selects between Silent and Audible mode. In Silent mode, the system sends the SOS message without sound. In Audible mode, the buzzer is activated for 3 seconds. The OLED displays the current system status, and the Serial Monitor simulates the SMS message containing a Google Maps location link.

---

# 10. Real Hardware Upgrade

In the final hardware version, replace the simulated parts with:

* ESP32-WROOM-32
* NEO-6M GPS Module
* SIM800L GSM Module
* TP4056 Charging Module
* 18650 Li-ion Batteries

The same logic will work, but GPS coordinates will be live and SMS will be sent through the GSM mod
