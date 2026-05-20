```cpp
/*
   SHUROKKHA
   Dual Mode System

   2 Press  = Silent Mode
   3 Press  = Audible Mode

   Components:
   - ESP32
   - SOS Button
   - Buzzer
   - GPS (NEO-6M)
   - GSM (SIM800L)
   - OLED Display
*/

#include <TinyGPS++.h>
#include <HardwareSerial.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// GPS
TinyGPSPlus gps;
HardwareSerial gpsSerial(1);

// GSM
HardwareSerial gsmSerial(2);

// Pins
#define SOS_BUTTON 4
#define BUZZER 5

// Phone Number
String phoneNumber = "+8801XXXXXXXXX";

// Press Counter
int pressCount = 0;

unsigned long lastPressTime = 0;

void setup() {

  Serial.begin(115200);

  pinMode(SOS_BUTTON, INPUT_PULLUP);

  pinMode(BUZZER, OUTPUT);

  digitalWrite(BUZZER, LOW);

  // GPS
  gpsSerial.begin(9600, SERIAL_8N1, 16, 17);

  // GSM
  gsmSerial.begin(9600, SERIAL_8N1, 26, 27);

  // OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {

    Serial.println("OLED Failed");

    while(true);
  }

  showMessage("SHUROKKHA", "System Ready");
}

void loop() {

  // GPS Read
  while(gpsSerial.available()) {

    gps.encode(gpsSerial.read());
  }

  // Button Press Detect
  if(digitalRead(SOS_BUTTON) == LOW) {

    pressCount++;

    lastPressTime = millis();

    Serial.print("Press Count: ");
    Serial.println(pressCount);

    delay(300);
  }

  // Check after 2 seconds
  if(pressCount > 0 && millis() - lastPressTime > 2000) {

    // 2 PRESS = SILENT MODE
    if(pressCount == 2) {

      showMessage("SILENT MODE", "Sending SMS");

      sendEmergencySMS();

      showMessage("ALERT SENT", "Silent Mode");
    }

    // 3 PRESS = AUDIBLE MODE
    else if(pressCount == 3) {

      showMessage("AUDIBLE MODE", "Buzzer Active");

      digitalWrite(BUZZER, HIGH);

      sendEmergencySMS();

      delay(5000);

      digitalWrite(BUZZER, LOW);

      showMessage("ALERT SENT", "Audible Mode");
    }

    else {

      showMessage("INVALID PRESS", "Try Again");
    }

    pressCount = 0;
  }
}

// SEND SMS FUNCTION
void sendEmergencySMS() {

  String latitude = "0.000000";
  String longitude = "0.000000";

  // GPS Check
  if(gps.location.isValid()) {

    latitude = String(gps.location.lat(), 6);

    longitude = String(gps.location.lng(), 6);
  }

  // Message
  String message = "EMERGENCY ALERT!\n";

  message += "Need Help!\n";

  message += "Location:\n";

  message += "https://maps.google.com/?q=";

  message += latitude;

  message += ",";

  message += longitude;

  // GSM Commands
  gsmSerial.println("AT");

  delay(1000);

  gsmSerial.println("AT+CMGF=1");

  delay(1000);

  gsmSerial.print("AT+CMGS=\"");

  gsmSerial.print(phoneNumber);

  gsmSerial.println("\"");

  delay(1000);

  gsmSerial.print(message);

  delay(1000);

  gsmSerial.write(26);

  delay(3000);

  Serial.println("SMS SENT");
}

// OLED FUNCTION
void showMessage(String line1, String line2) {

  display.clearDisplay();

  display.setTextSize(2);

  display.setTextColor(WHITE);

  display.setCursor(0, 10);

  display.println(line1);

  display.setTextSize(1);

  display.setCursor(0, 45);

  display.println(line2);

  display.display();
}
```
