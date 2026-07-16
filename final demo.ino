/*
  ============================================================
  SHUROKKHA - ESP32-Based Personal Safety System
  with GPS and Wi-Fi Email Alert (No GSM / No SIM card)
  ============================================================

  HOW IT WORKS:
  - ESP32 connects to Wi-Fi at boot.
  - GPS constantly updates location and saves it to flash (Preferences)
    so the last known location survives power loss / lost GPS fix.
  - SOS button: press 2 times quickly = Silent SOS,
                press 3 times quickly = Loud SOS (buzzer on).
  - On SOS: sends a professional emergency email (with Google Maps
    location link) to the registered emergency contact over Wi-Fi.
  - OLED shows the current device state at all times.

  Hardware wiring:
    GPS (NEO-6M)     -> VCC=3.3V, GND, TX=GPIO16, RX=GPIO17
    OLED (SSD1306)   -> VCC=3.3V, GND, SDA=GPIO21, SCL=GPIO22, addr 0x3C
    SOS Push Button  -> GPIO4 <-> GND (INPUT_PULLUP, LOW = pressed)
    Active Buzzer    -> GPIO5 (digital output, ON only in Loud SOS)

    Power:
      18650 Battery(+) -> On/Off Switch -> XL6009 IN+
      18650 Battery(-) -> XL6009 IN-
      XL6009 OUT+       -> ESP32 VIN
      XL6009 OUT-       -> ESP32 GND

  Libraries required (install via Arduino Library Manager):
    - TinyGPS++
    - Preferences (built-in with ESP32 core)
    - Wire (built-in)
    - Adafruit GFX
    - Adafruit SSD1306
    - WiFi (built-in with ESP32 core)
    - ESP Mail Client (by Mobizt)
  ============================================================
*/

#include <TinyGPS++.h>
#include <HardwareSerial.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Preferences.h>
#include <WiFi.h>
#include <ESP_Mail_Client.h>

// ---------------- Pin Definitions ----------------
#define GPS_RX_PIN     16   // ESP32 RX <- GPS TX
#define GPS_TX_PIN     17   // ESP32 TX -> GPS RX
#define SOS_BUTTON_PIN 4    // INPUT_PULLUP, LOW = pressed
#define BUZZER_PIN     5

// ---------------- OLED Config ----------------
#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define OLED_ADDRESS  0x3C

// ---------------- Wi-Fi Config ----------------
#define WIFI_SSID     "Naba"
#define WIFI_PASSWORD "me*12345"

// ---------------- Email (SMTP) Config ----------------
#define SMTP_HOST        "smtp.gmail.com"
#define SMTP_PORT        465
#define SENDER_EMAIL     "nosratee.jn@gmail.com"
#define SENDER_APP_PASS  "eqqlmwidmriixfob"
#define ALERT_RECIPIENT  "nosratee.jn@gmail.com"

SMTPSession smtp;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

TinyGPSPlus gps;
HardwareSerial gpsSerial(1);

Preferences prefs;  // namespace "gps", keys "lat" / "lng"

// ---------------- Location State ----------------
double currentLat = 0.0;
double currentLng = 0.0;
double lastLat    = 0.0;
double lastLng    = 0.0;
bool   gpsAvailable = false;

// ---------------- Alert State ----------------
bool alertSent = false;

// ---------------- Button State ----------------
int  pressCount        = 0;
unsigned long lastPressTime = 0;
bool buttonState        = HIGH;
bool lastButtonState     = HIGH;
unsigned long lastDebounceTime = 0;

const unsigned long DEBOUNCE_MS     = 50;
const unsigned long PRESS_WINDOW_MS = 1000;

// ---------------- OLED State Machine ----------------
enum OledState {
  OLED_BOOT,
  OLED_CONNECTING_WIFI,
  OLED_READY,
  OLED_SILENT_SENDING,
  OLED_LOUD_SENDING,
  OLED_EMAIL_SENT,
  OLED_EMAIL_FAILED,
  OLED_NO_GPS
};
OledState oledState     = OLED_BOOT;
OledState lastOledState = OLED_BOOT;

// ---------------- Forward Declarations ----------------
void initializeOLED();
bool connectWiFi(unsigned long timeoutMs);

void readGPS();
void saveLocation();
void loadLocation();
double activeLat();
double activeLng();

void readButton();
void evaluatePresses();

void silentSOS();
void loudSOS();
bool sendEmailAlert(bool loud);
String buildEmailSubject(bool loud);
String buildEmailBody(bool loud, double lat, double lng);

void updateOLED();
void drawScreen(const char* line1, const char* line2, const char* line3 = "");

// ============================================================
void setup() {
  Serial.begin(115200);

  pinMode(SOS_BUTTON_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  initializeOLED();
  oledState = OLED_BOOT;
  updateOLED();

  prefs.begin("gps", false);
  loadLocation();

  gpsSerial.begin(9600, SERIAL_8N1, GPS_RX_PIN, GPS_TX_PIN);

  oledState = OLED_CONNECTING_WIFI;
  updateOLED();
  connectWiFi(20000);

  oledState = OLED_READY;
  updateOLED();
}

void loop() {
  readGPS();
  readButton();
  updateOLED();
}

// ---------------- GPS ----------------
void readGPS() {
  while (gpsSerial.available() > 0) {
    gps.encode(gpsSerial.read());
  }

  if (gps.location.isValid()) {
    currentLat = gps.location.lat();
    currentLng = gps.location.lng();
    gpsAvailable = true;

    lastLat = currentLat;
    lastLng = currentLng;
    saveLocation();
  } else {
    gpsAvailable = false;
  }
}

void saveLocation() {
  prefs.putDouble("lat", lastLat);
  prefs.putDouble("lng", lastLng);
}

void loadLocation() {
  lastLat = prefs.getDouble("lat", 0.0);
  lastLng = prefs.getDouble("lng", 0.0);
}

double activeLat() {
  return gpsAvailable ? currentLat : lastLat;
}

double activeLng() {
  return gpsAvailable ? currentLng : lastLng;
}

// ---------------- Button (debounced, multi-press) ----------------
void readButton() {
  bool reading = digitalRead(SOS_BUTTON_PIN);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > DEBOUNCE_MS) {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == LOW) {
        pressCount++;
        lastPressTime = millis();
      }
    }
  }

  lastButtonState = reading;

  if (pressCount > 0 && (millis() - lastPressTime > PRESS_WINDOW_MS)) {
    evaluatePresses();
    pressCount = 0;
  }
}

void evaluatePresses() {
  if (pressCount == 2) {
    silentSOS();
  } else if (pressCount == 3) {
    loudSOS();
  }
}

// ---------------- SOS Modes ----------------
void silentSOS() {
  oledState = OLED_SILENT_SENDING;
  updateOLED();

  alertSent = sendEmailAlert(false);

  oledState = alertSent ? OLED_EMAIL_SENT : OLED_EMAIL_FAILED;
  updateOLED();
  delay(2000);

  oledState = OLED_READY;
  updateOLED();
}

void loudSOS() {
  oledState = OLED_LOUD_SENDING;
  updateOLED();

  digitalWrite(BUZZER_PIN, HIGH);

  alertSent = sendEmailAlert(true);

  oledState = alertSent ? OLED_EMAIL_SENT : OLED_EMAIL_FAILED;
  updateOLED();
  delay(2000);

  digitalWrite(BUZZER_PIN, LOW);

  oledState = OLED_READY;
  updateOLED();
}

// ---------------- Email Templates ----------------
String buildEmailSubject(bool loud) {
  return loud ? "\xF0\x9F\x94\xB4 SHUROKKHA \xE2\x80\x93 Urgent Emergency Alert"
              : "\xF0\x9F\x9F\xA1 SHUROKKHA \xE2\x80\x93 Silent Emergency Alert";
}

String buildEmailBody(bool loud, double lat, double lng) {
  String body = "Dear Emergency Contact,\n\n";
  body += "This is an automated emergency alert generated by the SHUROKKHA Personal Safety System.\n\n";

  if (loud) {
    body += "A Loud SOS has been activated. The user may be in immediate danger and requires urgent assistance.\n\n";
  } else {
    body += "A Silent SOS has been activated by the user. The user may be in a situation where they cannot communicate openly and may require immediate assistance.\n\n";
  }

  body += "Current Location:\nhttps://maps.google.com/?q=";
  body += String(lat, 6);
  body += ",";
  body += String(lng, 6);
  body += "\n\n";

  if (loud) {
    body += "Please respond immediately or contact the nearest emergency service if necessary.\n\n";
  } else {
    body += "Please check on the user's safety as soon as possible.\n\n";
  }

  body += "This message was automatically generated by the SHUROKKHA Safety System.\n\n";
  body += "Regards,\n\nSHUROKKHA\nESP32-Based Personal Safety System\n\n";
  body += "----------------------------------------\n\n";
  body += "SHUROKKHA\nESP32-Based Personal Safety System\n\n";
  body += "This is an automatically generated email.\nPlease do not reply.";

  return body;
}

// ---------------- Wi-Fi / Email ----------------
bool connectWiFi(unsigned long timeoutMs) {
  Serial.println("Connecting to WiFi...");
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  unsigned long start = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - start < timeoutMs) {
    delay(300);
    Serial.print(".");
  }
  Serial.println();

  if (WiFi.status() == WL_CONNECTED) {
    Serial.print("WiFi connected, IP: ");
    Serial.println(WiFi.localIP());
    return true;
  }

  Serial.println("WiFi connection failed (network not in range or wrong password).");
  return false;
}

bool sendEmailAlert(bool loud) {
  if (WiFi.status() != WL_CONNECTED) {
    if (!connectWiFi(15000)) {
      return false;
    }
  }

  Session_Config config;
  config.server.host_name = SMTP_HOST;
  config.server.port = SMTP_PORT;
  config.login.email = SENDER_EMAIL;
  config.login.password = SENDER_APP_PASS;
  config.login.user_domain = "";

  SMTP_Message message;
  message.sender.name = "SHUROKKHA";
  message.sender.email = SENDER_EMAIL;
  message.subject = buildEmailSubject(loud);
  message.addRecipient("Emergency Contact", ALERT_RECIPIENT);

  String body = buildEmailBody(loud, activeLat(), activeLng());
  message.text.content = body.c_str();
  message.text.charSet = "utf-8";
  message.text.transfer_encoding = Content_Transfer_Encoding::enc_7bit;

  smtp.debug(0);

  if (!smtp.connect(&config)) {
    Serial.println("SMTP connect failed.");
    return false;
  }

  bool ok = MailClient.sendMail(&smtp, &message);
  if (ok) {
    Serial.println("Email sent successfully.");
  } else {
    Serial.print("Email send failed: ");
    Serial.println(smtp.errorReason());
  }

  smtp.closeSession();
  return ok;
}

// ---------------- OLED ----------------
void initializeOLED() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
    Serial.println(F("OLED init failed"));
    while (true) delay(10);
  }
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.display();
}

void drawScreen(const char* line1, const char* line2, const char* line3) {
  display.clearDisplay();

  const char* lines[3] = { line1, line2, line3 };
  int lineCount = 0;
  for (int i = 0; i < 3; i++) {
    if (lines[i] != nullptr && lines[i][0] != '\0') lineCount++;
  }

  int16_t x1, y1;
  uint16_t w, h;
  int lineHeight = 10;
  int blockHeight = lineCount * lineHeight;
  int startY = (SCREEN_HEIGHT - blockHeight) / 2;

  int row = 0;
  for (int i = 0; i < 3; i++) {
    if (lines[i] == nullptr || lines[i][0] == '\0') continue;
    display.getTextBounds(lines[i], 0, 0, &x1, &y1, &w, &h);
    int startX = (SCREEN_WIDTH - w) / 2;
    display.setCursor(startX, startY + row * lineHeight);
    display.print(lines[i]);
    row++;
  }

  display.display();
}

void updateOLED() {
  if (oledState == lastOledState) return;
  lastOledState = oledState;

  switch (oledState) {
    case OLED_BOOT:
      drawScreen("SHUROKKHA", "Initializing...");
      break;

    case OLED_CONNECTING_WIFI:
      drawScreen("SHUROKKHA", "Connecting WiFi...");
      break;

    case OLED_READY:
      drawScreen("SHUROKKHA", "Ready");
      break;

    case OLED_NO_GPS:
      drawScreen("SHUROKKHA", "Using Last Location");
      break;

    case OLED_SILENT_SENDING:
      drawScreen("SHUROKKHA", "Silent SOS", "Sending...");
      break;

    case OLED_LOUD_SENDING:
      drawScreen("SHUROKKHA", "LOUD SOS", "Sending...");
      break;

    case OLED_EMAIL_SENT:
      drawScreen("SHUROKKHA", "EMAIL SENT");
      break;

    case OLED_EMAIL_FAILED:
      drawScreen("SHUROKKHA", "EMAIL FAILED");
      break;
  }
}
