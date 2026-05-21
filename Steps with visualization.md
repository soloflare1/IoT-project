🟦  ESP32 + OLED + BUTTON + BUZZER + GPS + GSM

This guide explains EVERYTHING step-by-step:

✅ Wiring
✅ Breadboard usage
✅ Library installation
✅ Arduino IDE setup
✅ Code upload
✅ Serial Monitor
✅ Testing each module
✅ Common mistakes


---

🟦 STEP 0 — Understand Your ESP32

Important pins you will use:

Function	GPIO

OLED SDA	21
OLED SCL	22
Button	4
Buzzer	5
GPS RX/TX	16,17
GSM RX/TX	26,27



---

🟦 STEP 1 — Install Arduino IDE

Download Arduino IDE

[Arduino IDE Download](https://www.arduino.cc/en/software?utm_source=chatgpt.com)

Install normally.


---

🟦 STEP 2 — Install ESP32 Board Package

Open Arduino IDE

Go to:

File → Preferences

Find:

Additional Board Manager URLs

Paste:

https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json

Click OK.


---

🟦 STEP 3 — Install ESP32 Board

Go to:

Tools → Board → Boards Manager

Search:

ESP32

Install:

esp32 by Espressif Systems


---

🟦 STEP 4 — Connect ESP32 to PC

Use USB cable.

Then go to:

Tools → Port

Select available COM port.

Example:

COM5


---

🟦 STEP 5 — Select Board

Go to:

Tools → Board

Select:

ESP32 Dev Module


---

🟦 STEP 6 — Breadboard Setup

Important

Same row = connected

Red line = positive power

Blue line = ground

Place ESP32 in middle



---

🟦 STEP 7 — OLED DISPLAY TEST


---

🔌 OLED Wiring

OLED Pin	ESP32 Pin

VCC	3.3V
GND	GND
SCL	GPIO 22
SDA	GPIO 21



---

🟦 STEP 7.1 — Install OLED Libraries

Go to:

Sketch → Include Library → Manage Libraries

Search and install:

Adafruit GFX

Then install:

Adafruit SSD1306


---

🟦 STEP 7.2 — OLED Code

Create new sketch and paste:

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  -1
);

void setup() {

  Serial.begin(115200);

  if(!display.begin(
      SSD1306_SWITCHCAPVCC,
      0x3C)) {

    Serial.println("OLED Failed");

    while(true);
  }

  display.clearDisplay();

  display.setTextSize(2);

  display.setTextColor(WHITE);

  display.setCursor(5,20);

  display.println("SHUROKKHA");

  display.display();
}

void loop() {

}


---

🟦 STEP 7.3 — Upload Code

Click:

✅ Verify
⬆️ Upload


---

🟦 If Upload Fails

Hold BOOT button while uploading.


---

🟦 Expected OLED Output

SHUROKKHA


---

🟦 STEP 8 — BUTTON TEST


---

🔌 Button Wiring

Button	ESP32

One Pin	GPIO 4
Other Pin	GND



---

🟦 STEP 8.1 — Button Code

#define SOS_BUTTON 4

void setup() {

  Serial.begin(115200);

  pinMode(SOS_BUTTON, INPUT_PULLUP);
}

void loop() {

  if(digitalRead(SOS_BUTTON) == LOW) {

    Serial.println("BUTTON PRESSED");

    delay(300);
  }
}


---

🟦 STEP 8.2 — Open Serial Monitor

Go to:

Tools → Serial Monitor

Set baud rate:

115200


---

🟦 Expected Output

When button pressed:

BUTTON PRESSED


---

🟦 STEP 9 — BUZZER TEST


---

🔌 Buzzer Wiring

Buzzer	ESP32

+	GPIO 5
-	GND



---

🟦 STEP 9.1 — Buzzer Code

#define BUZZER 5

void setup() {

  pinMode(BUZZER, OUTPUT);
}

void loop() {

  digitalWrite(BUZZER, HIGH);

  delay(1000);

  digitalWrite(BUZZER, LOW);

  delay(1000);
}


---

🟦 Expected Result

Buzzer ON/OFF every second.


---

🟦 STEP 10 — GPS TEST


---

🔌 GPS Wiring

GPS	ESP32

VCC	3.3V
GND	GND
TX	GPIO 16
RX	GPIO 17



---

🟦 IMPORTANT

Cross connection:

GPS TX → ESP32 RX

GPS RX → ESP32 TX



---

🟦 STEP 10.1 — Install GPS Library

Install:

TinyGPSPlus


---

🟦 STEP 10.2 — GPS Code

#include <TinyGPS++.h>
#include <HardwareSerial.h>

TinyGPSPlus gps;

HardwareSerial gpsSerial(1);

void setup() {

  Serial.begin(115200);

  gpsSerial.begin(
    9600,
    SERIAL_8N1,
    16,
    17
  );
}

void loop() {

  while(gpsSerial.available()) {

    gps.encode(gpsSerial.read());

    if(gps.location.isUpdated()) {

      Serial.print("Latitude: ");

      Serial.println(
        gps.location.lat(),
        6
      );

      Serial.print("Longitude: ");

      Serial.println(
        gps.location.lng(),
        6
      );

      Serial.println();
    }
  }
}


---

🟦 Expected GPS Output

Latitude: 23.xxxxxx
Longitude: 90.xxxxxx


---

🟦 GPS NOT WORKING?

Fix

Go near window

Go outside

Wait 2–5 minutes

Check TX/RX wiring



---

🟦 STEP 11 — GSM TEST


---

⚠️ VERY IMPORTANT

SIM800L should use external battery.

Do NOT use ESP32 3.3V pin.


---

🔌 GSM Wiring

SIM800L	ESP32

TXD	GPIO 26
RXD	GPIO 27
GND	GND



---

🟦 STEP 11.1 — GSM Test Code

#include <HardwareSerial.h>

HardwareSerial gsmSerial(2);

void setup() {

  Serial.begin(115200);

  gsmSerial.begin(
    9600,
    SERIAL_8N1,
    26,
    27
  );

  delay(3000);

  gsmSerial.println("AT");
}

void loop() {

  while(gsmSerial.available()) {

    Serial.write(
      gsmSerial.read()
    );
  }
}


---

🟦 Expected Output

OK


---

🟦 STEP 12 — SMS TEST


---

🟦 SMS Code

#include <HardwareSerial.h>

HardwareSerial gsmSerial(2);

String phoneNumber =
"+8801XXXXXXXXX";

void setup() {

  gsmSerial.begin(
    9600,
    SERIAL_8N1,
    26,
    27
  );

  delay(3000);

  gsmSerial.println("AT+CMGF=1");

  delay(1000);

  gsmSerial.print("AT+CMGS=\"");

  gsmSerial.print(phoneNumber);

  gsmSerial.println("\"");

  delay(1000);

  gsmSerial.print(
    "SHUROKKHA TEST"
  );

  delay(1000);

  gsmSerial.write(26);
}

void loop() {

}


---

🟦 Expected Result

Phone receives SMS.


---

🟦 STEP 13 — 2 PRESS / 3 PRESS SYSTEM


---

🟦 Logic

Press Count	Mode

2 Press	Silent
3 Press	Audible



---

🟦 Code

#define BUTTON 4
#define BUZZER 5

int pressCount = 0;

unsigned long lastPress = 0;

void setup() {

  Serial.begin(115200);

  pinMode(BUTTON, INPUT_PULLUP);

  pinMode(BUZZER, OUTPUT);
}

void loop() {

  if(digitalRead(BUTTON) == LOW) {

    pressCount++;

    lastPress = millis();

    Serial.print("Count: ");

    Serial.println(pressCount);

    delay(300);
  }

  if(pressCount > 0 &&
     millis() - lastPress > 2000) {

    if(pressCount == 2) {

      Serial.println(
        "SILENT MODE"
      );
    }

    else if(pressCount == 3) {

      Serial.println(
        "AUDIBLE MODE"
      );

      digitalWrite(BUZZER, HIGH);

      delay(3000);

      digitalWrite(BUZZER, LOW);
    }

    pressCount = 0;
  }
}


---

🟦 FINAL TESTING ORDER

Step	Test

1	OLED
2	Button
3	Buzzer
4	GPS
5	GSM
6	SMS
7	Dual Press Logic
8	Final Full System



---

🟦 Common Problems

Problem	Solution

OLED blank	Check SDA/SCL
GPS no data	Go outside
GSM no response	Use external battery
Upload failed	Hold BOOT
No COM port	Install drivers
Random restart	Weak power supply
