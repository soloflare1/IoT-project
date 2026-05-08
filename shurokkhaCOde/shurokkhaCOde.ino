#include <TinyGPS++.h>
#include <HardwareSerial.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

// ---------- GPS ----------
TinyGPSPlus gps;
HardwareSerial gpsSerial(1); // RX=16, TX=17

// ---------- GSM ----------
HardwareSerial gsmSerial(2); // RX=16/17 alternative pins if needed

// ---------- OLED ----------
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// ---------- Pins ----------
#define SOS_BUTTON 4
#define BUZZER 5
#define MODE_SWITCH 18   // 0 = Silent, 1 = Audible

// ---------- Phone Number ----------
String phoneNumber = "+880XXXXXXXXXX";

bool lastButtonState = HIGH;

void setup() {
  Serial.begin(115200);

  pinMode(SOS_BUTTON, INPUT_PULLUP);
  pinMode(BUZZER, OUTPUT);
  pinMode(MODE_SWITCH, INPUT);

  // GPS UART
  gpsSerial.begin(9600, SERIAL_8N1, 16, 17);

  // GSM UART
  gsmSerial.begin(9600, SERIAL_8N1, 26, 27);

  // OLED setup
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();

  showMessage("System Ready");
}

void loop() {
  // Read GPS data continuously
  while (gpsSerial.available()) {
    gps.encode(gpsSerial.read());
  }

  bool buttonState = digitalRead(SOS_BUTTON);

  if (buttonState == LOW && lastButtonState == HIGH) {
    delay(300); // debounce
    triggerSOS();
  }

  lastButtonState = buttonState;
}

// ---------- SOS FUNCTION ----------
void triggerSOS() {

  showMessage("Sending SOS...");

  float lat = gps.location.isValid() ? gps.location.lat() : 0.0;
  float lng = gps.location.isValid() ? gps.location.lng() : 0.0;

  String googleMapsLink = "https://maps.google.com/?q=" + String(lat, 6) + "," + String(lng, 6);

  String message = "EMERGENCY ALERT!\nLocation: " + googleMapsLink;

  sendSMS(message);

  int mode = digitalRead(MODE_SWITCH);

  if (mode == HIGH) {
    digitalWrite(BUZZER, HIGH);
    delay(2000);
    digitalWrite(BUZZER, LOW);
  }

  showMessage("SOS Sent");
}

// ---------- SMS FUNCTION ----------
void sendSMS(String text) {
  gsmSerial.println("AT+CMGF=1");
  delay(1000);

  gsmSerial.println("AT+CMGS=\"" + phoneNumber + "\"");
  delay(1000);

  gsmSerial.print(text);
  delay(500);

  gsmSerial.write(26); // CTRL+Z to send
  delay(3000);
}

// ---------- OLED ----------
void showMessage(String msg) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.println(msg);
  display.display();
}