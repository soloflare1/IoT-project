/*
   SHUROKKHA
   IoT-Based Smart Wearable Emergency Safety System

   Components:
   - ESP32
   - NEO-6M GPS
   - SIM800L GSM
   - SOS Button
   - Buzzer
   - OLED Display

*/

#include <TinyGPS++.h>
#include <HardwareSerial.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED Display
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

// Emergency Number
String phoneNumber = "+8801XXXXXXXXX";

void setup() {

  Serial.begin(115200);

  // SOS Button
  pinMode(SOS_BUTTON, INPUT_PULLUP);

  // Buzzer
  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, LOW);

  // GPS Serial
  gpsSerial.begin(9600, SERIAL_8N1, 16, 17);

  // GSM Serial
  gsmSerial.begin(9600, SERIAL_8N1, 26, 27);

  // OLED Setup
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED Failed");
    while(true);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  showMessage("SHUROKKHA", "System Ready");

  delay(2000);
}

void loop() {

  // Read GPS Data
  while (gpsSerial.available()) {
    gps.encode(gpsSerial.read());
  }

  // SOS Button Pressed
  if (digitalRead(SOS_BUTTON) == LOW) {

    digitalWrite(BUZZER, HIGH);

    showMessage("SOS ACTIVATED", "Sending Alert...");

    sendEmergencySMS();

    delay(5000);

    digitalWrite(BUZZER, LOW);

    showMessage("Alert Sent", "Stay Safe");

    delay(3000);
  }
}

void sendEmergencySMS() {

  String latitude = "0.000000";
  String longitude = "0.000000";

  if (gps.location.isValid()) {
    latitude = String(gps.location.lat(), 6);
    longitude = String(gps.location.lng(), 6);
  }

  String message = "EMERGENCY ALERT!\n";
  message += "I need help.\n";
  message += "Location:\n";
  message += "https://maps.google.com/?q=";
  message += latitude;
  message += ",";
  message += longitude;

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

  Serial.println("SMS Sent");
}

void showMessage(String line1, String line2) {

  display.clearDisplay();

  display.setCursor(0, 15);
  display.setTextSize(2);
  display.println(line1);

  display.setTextSize(1);
  display.setCursor(0, 45);
  display.println(line2);

  display.display();
}
