
# 📌 🔥 IMPORTANT NOTES (Shurokkha Project)

## 🧠 1. This is a Simulation Project

* This project is a **Wokwi simulation version**
* Real GPS and GSM hardware are not used
* GPS location is represented using **fixed coordinates**

```text
Latitude = 23.8103  
Longitude = 90.4125
```

---

## 📱 2. Phone Number (Not Used in Wokwi)

* No SIM800L module is used in Wokwi
* So **no phone number is required**
* SMS is simulated using Serial Monitor output

👉 In real hardware:

* SIM800L GSM module is required
* Phone number is necessary for sending SMS

---

## 🔘 3. Button Working Logic

Pushbutton

* SOS button is connected to GPIO14
* When pressed, it becomes LOW
* System triggers SOS immediately

```text
Press → SOS Activated  
Release → System Ready
```

---

## 🎚️ 4. Mode Switch Logic

Slide Switch

* Connected to GPIO12
* Used to select emergency mode

| Position  | Mode         | Result    |
| --------- | ------------ | --------- |
| GND side  | Silent Mode  | No buzzer |
| Open side | Audible Mode | Buzzer ON |

---

## 🔊 5. Buzzer Behavior

Piezo Buzzer

* Silent Mode → OFF
* Audible Mode → ON for 3 seconds

---

## 📺 6. OLED Display

SSD1306 OLED Display

Displays:

* System Ready
* Silent Mode
* Audible Mode
* SOS Sent

---

## 📡 7. GPS Simulation

NEO-6M GPS Module (real hardware only)

* Not available in Wokwi
* Uses fixed latitude and longitude values instead

---

## 📲 8. GSM Module Simulation

SIM800L GSM Module

* Not included in Wokwi
* SMS is simulated using Serial Monitor
* Real version sends actual SMS with location link

---

## ⚡ 9. Power System (Real Hardware)

18650 Li-ion Battery
TP4056 Charging Module

* Portable power supply
* Safe charging system for Li-ion batteries

---

## 🎯 10. Overall Working Flow

```text
System ON
   ↓
OLED shows "System Ready"
   ↓
User presses SOS button
   ↓
ESP32 checks mode switch
   ↓
Generates GPS location (simulated)
   ↓
Sends SOS message (Serial Monitor)
   ↓
Buzzer ON (only in Audible mode)
   ↓
OLED shows "SOS Sent"
```

---

