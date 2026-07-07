Below is a **complete step-by-step Git workflow using ONE Arduino file named `shurokkhaCOde.ino` inside a folder `shurokkha`**, including how your project evolves through versions.

---

# 🔷 1. Project Folder Structure

```
shurokkha/
   └── shurokkhaCOde.ino
```

---

# 🔷 2. Step-by-step Version Control (Full Project Lifecycle)

---

## 🟢 STEP 1: Initialize Git (First time only)

```bash id="ginit1"
cd shurokkha
git init
```

---

## 🟢 STEP 2: First Version (Basic SOS System)

### ✏️ Code inside `shurokkhaCOde.ino`

```cpp id="v1code"
void setup() {
  Serial.begin(115200);
  pinMode(4, INPUT_PULLUP); // SOS button
}

void loop() {
  if (digitalRead(4) == LOW) {
    Serial.println("SOS Activated");
  }
}
```

### 💾 Save version

```bash id="v1git"
git add .
git commit -m "Version 1: Basic SOS button system"
```

---

## 🟡 STEP 3: Add GPS Module

### ✏️ Updated code

```cpp id="v2code"
#include <TinyGPS++.h>

TinyGPSPlus gps;

void setup() {
  Serial.begin(115200);
}

void loop() {
  while (Serial.available()) {
    gps.encode(Serial.read());
  }

  if (gps.location.isUpdated()) {
    Serial.print("Lat: ");
    Serial.println(gps.location.lat());
  }
}
```

### 💾 Commit

```bash id="v2git"
git add .
git commit -m "Version 2: Added GPS real-time location tracking"
```

---

## 🟠 STEP 4: Add GSM SMS Alert

### ✏️ Updated code

```cpp id="v3code"
#include <TinyGPS++.h>
TinyGPSPlus gps;

void sendSMS(String msg) {
  Serial.println("AT+CMGF=1");
  Serial.println("AT+CMGS=\"+880XXXXXXXXXX\"");
  Serial.print(msg);
  Serial.write(26);
}

void loop() {
  if (digitalRead(4) == LOW) {
    sendSMS("Emergency Alert Triggered");
  }
}
```

### 💾 Commit

```bash id="v3git"
git add .
git commit -m "Version 3: Added GSM SMS emergency alert system"
```

---

## 🔵 STEP 5: Add OLED Display + Status

### ✏️ Updated code

```cpp id="v4code"
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(128, 64, &Wire, -1);

void showMsg(String msg) {
  display.clearDisplay();
  display.setCursor(0, 10);
  display.println(msg);
  display.display();
}

void loop() {
  if (digitalRead(4) == LOW) {
    showMsg("Sending SOS...");
    sendSMS("Emergency Alert");
  }
}
```

### 💾 Commit

```bash id="v4git"
git add .
git commit -m "Version 4: Added OLED status display"
```

---

## 🔴 STEP 6: Final System (Full Shurokkha)

### ✏️ Final combined logic (concept)

```cpp id="finalcode"
void loop() {
  if (digitalRead(4) == LOW) {

    // GPS read
    // GSM send SMS with Google Maps link
    // OLED show status
    // Optional buzzer alert

    Serial.println("FULL SOS SYSTEM ACTIVATED");
  }
}
```

### 💾 Final commit

```bash id="finalgit"
git add .
git commit -m "Final Version: Complete Shurokkha IoT safety system"
```

---

## 🚀 STEP 7: Push to GitHub

```bash id="push1"
git remote add origin https://github.com/yourrepo/Shurokkha.git
git branch -M main
git push -u origin main
```

---

# 🔷 3. How Your Project Evolves (Very Important)

| Version | Feature                    |
| ------- | -------------------------- |
| V1      | SOS Button                 |
| V2      | GPS Tracking               |
| V3      | GSM SMS Alert              |
| V4      | OLED Display               |
| Final   | Complete IoT Safety System |

---

# 🔷 4. How to Update in Future

Every time you improve:

```bash id="cycle1"
git add .
git commit -m "describe new feature"
git push
```

---

# 🔷 5. 

> “The Shurokkha IoT system is developed in a single Arduino source file, where Git is used to maintain version control. Each update is tracked through commits representing different development stages from basic SOS functionality to the final integrated system.”




# Hardware Connections

| Component | Pin | Connect To |
|-----------|-----|------------|
| **18650 Li-ion Battery** | + | TP4056 B+ |
| | - | TP4056 B- |
| **TP4056 Charging Module** | OUT+ | XL6009 IN+ |
| | OUT- | XL6009 IN- |
| | OUT+ | LM2596 IN+ |
| | OUT- | LM2596 IN- |
| **XL6009 Boost Converter** | OUT+ (5V) | ESP32 VIN (5V) |
| | OUT- | ESP32 GND |
| **LM2596 Buck Converter** | OUT+ (4.0–4.2V) | SIM800L VCC |
| | OUT- | SIM800L GND |
| **ESP32 DevKit V1** | GPIO16 (RX2) | GPS TX |
| | GPIO17 (TX2) | GPS RX |
| | GPIO27 | SIM800L TX |
| | GPIO14 | SIM800L RX |
| | GPIO21 | OLED SDA |
| | GPIO22 | OLED SCL |
| | GPIO4 | SOS Button |
| | GPIO5 | Active Buzzer (+) |
| | GND | GPS GND |
| | GND | SIM800L GND |
| | GND | OLED GND |
| | GND | Buzzer (-) |
| **GPS (NEO-6M)** | VCC | ESP32 3.3V |
| | GND | ESP32 GND |
| **OLED SSD1306** | VCC | ESP32 3.3V |
| | GND | ESP32 GND |
| **SOS Push Button** | Other Side | ESP32 GND |