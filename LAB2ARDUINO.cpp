#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

/* ================= OLED ================= */
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

/* ================= JOYSTICK ================= */
#define JOY_X A0
#define JOY_Y A1
#define JOY_BTN 2

/* ================= DHT ================= */
#define DHT_TYPE DHT22
DHT dht1(3, DHT_TYPE);
DHT dht2(4, DHT_TYPE);
DHT dht3(5, DHT_TYPE);
DHT dht4(6, DHT_TYPE);

/* ===== DHT CACHE ===== */
float t1, t2, t3, t4;
float h1, h2, h3, h4;
unsigned long lastDHTread = 0;

/* ================= PHOTO ================= */
const float GAMMA = 0.7;
const float RL10 = 50;

/* ================= LAMPS ================= */
#define L_RED   9
#define L_GREEN 10
#define R_GREEN   7
#define R_RED 12

/* ================= UI ================= */
enum Screen {
  MENU_MAIN,
  MENU_SENSORS,
  PANEL_MAIN,
  GRAPH_DHT,
  GRAPH_PHOTO
};

Screen currentScreen = MENU_MAIN;
int menuIndex = 0;

/* ================= GRAPH ================= */
#define GRAPH_X 0
#define GRAPH_Y 16
#define GRAPH_W 128
#define GRAPH_H 48

int graphXpos = 1;
unsigned long lastGraphUpdate = 0;

/* ================= LUX ================= */
float getluxL() {
  int a = analogRead(A2);
  float v = a / 1024.0 * 5.0;
  float r = 2000 * v / (1 - v / 5);
  return pow(RL10 * 1e3 * pow(10, GAMMA) / r, (1 / GAMMA));
}

float getluxR() {
  int a = analogRead(A3);
  float v = a / 1024.0 * 5.0;
  float r = 2000 * v / (1 - v / 5);
  return pow(RL10 * 1e3 * pow(10, GAMMA) / r, (1 / GAMMA));
}

float luxL() { return getluxL(); }
float luxR() { return getluxR(); }

/* ================= SETUP ================= */
void setup() {
  pinMode(JOY_BTN, INPUT_PULLUP);

  pinMode(L_RED, OUTPUT);
  pinMode(L_GREEN, OUTPUT);
  pinMode(R_RED, OUTPUT);
  pinMode(R_GREEN, OUTPUT);

  dht1.begin();
  dht2.begin();
  dht3.begin();
  dht4.begin();

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(SSD1306_WHITE);
}

/* ================= DHT UPDATE ================= */
void updateDHT() {
  if (millis() - lastDHTread < 2000) return;
  lastDHTread = millis();

  t1 = dht1.readTemperature();
  t2 = dht2.readTemperature();
  t3 = dht3.readTemperature();
  t4 = dht4.readTemperature();

  h1 = dht1.readHumidity();
  h2 = dht2.readHumidity();
  h3 = dht3.readHumidity();
  h4 = dht4.readHumidity();
}

/* ================= DATA ================= */
float avgTemp() {
  return (t1 + t2 + t3 + t4) / 4.0;
}

float avgHum() {
  return (h1 + h2 + h3 + h4) / 4.0;
}

int avgLight() {
  return (luxL() + luxR()) / 2;
}

/* ================= LAMPS ================= */
void updateLamps() {
  float tL = (t1 + t2) / 2.0;
  float hL = (h1 + h2) / 2.0;
  float tR = (t3 + t4) / 2.0;
  float hR = (h3 + h4) / 2.0;

  if (luxL() < 1000) {
    digitalWrite(L_GREEN, (tL > 0 && hL < 50));
    digitalWrite(L_RED,   !(tL > 0 && hL < 50));
  } else {
    digitalWrite(L_RED, LOW);
    digitalWrite(L_GREEN, LOW);
  }

  if (luxR() < 1000) {
    digitalWrite(R_GREEN, (tR > 0 && hR < 50));
    digitalWrite(R_RED,   !(tR > 0 && hR < 50));
  } else {
    digitalWrite(R_RED, LOW);
    digitalWrite(R_GREEN, LOW);
  }
}

/* ================= DRAW ================= */
void drawMenu(const char* title, const char* items[], int count) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print(title);
  for (int i = 0; i < count; i++) {
    display.setCursor(0, 16 + i * 10);
    display.print(i == menuIndex ? "> " : "  ");
    display.print(items[i]);
  }
  display.display();
}

void drawMainPanel() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Main Panel");

  display.setCursor(0, 16);
  display.print("Temp: ");
  display.print(avgTemp(), 1);
  display.print(" C");

  display.setCursor(0, 26);
  display.print("Hum: ");
  display.print(avgHum(), 1);
  display.print(" %");

  display.setCursor(0, 36);
  display.print("Light: ");
  display.print(avgLight());
  display.print(" lux");

  display.display();
}

void drawGraphFrame(const char* title) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print(title);
  display.drawRect(GRAPH_X, GRAPH_Y, GRAPH_W, GRAPH_H, SSD1306_WHITE);
  graphXpos = 1;
  display.display();
}

void drawGraphPoint(float v, float minV, float maxV) {
  v = constrain(v, minV, maxV);
  int y = map(v, minV, maxV, GRAPH_Y + GRAPH_H - 1, GRAPH_Y + 1);
  display.drawPixel(graphXpos++, y, SSD1306_WHITE);
  display.display();
  if (graphXpos >= GRAPH_W - 1) {
    graphXpos = 1;
    display.fillRect(GRAPH_X + 1, GRAPH_Y + 1,
                     GRAPH_W - 2, GRAPH_H - 2, SSD1306_BLACK);
    display.drawRect(GRAPH_X, GRAPH_Y, GRAPH_W, GRAPH_H, SSD1306_WHITE);
  }
}

/* ================= LOOP ================= */
void loop() {
  updateDHT();
  updateLamps();

  int y = analogRead(JOY_Y);
  int x = analogRead(JOY_X);

  if (y < 300) { menuIndex--; delay(200); }
  if (y > 700) { menuIndex++; delay(200); }

  if (digitalRead(JOY_BTN) == LOW) {
    delay(200);
    if (currentScreen == MENU_MAIN)
      currentScreen = (menuIndex == 0) ? PANEL_MAIN : MENU_SENSORS;
    else if (currentScreen == MENU_SENSORS)
      currentScreen = (menuIndex == 0) ? GRAPH_DHT : GRAPH_PHOTO;
    menuIndex = 0;
  }

  if (x < 300 || x > 700) {
    currentScreen = MENU_MAIN;
    menuIndex = 0;
    delay(300);
  }

  if (currentScreen == MENU_MAIN) {
    const char* items[] = {"Main panel", "Sensors"};
    menuIndex = constrain(menuIndex, 0, 1);
    drawMenu("Menu", items, 2);
  }

  if (currentScreen == MENU_SENSORS) {
    const char* items[] = {"DHT", "Photores"};
    menuIndex = constrain(menuIndex, 0, 1);
    drawMenu("Sensors", items, 2);
  }

  if (currentScreen == PANEL_MAIN) {
    drawMainPanel();
    delay(500);
  }

  static Screen last = MENU_MAIN;
  if (currentScreen != last &&
     (currentScreen == GRAPH_DHT || currentScreen == GRAPH_PHOTO))
    drawGraphFrame(currentScreen == GRAPH_DHT ? "Temp graph" : "Light graph");
  last = currentScreen;

  if (currentScreen == GRAPH_DHT || currentScreen == GRAPH_PHOTO) {
    if (millis() - lastGraphUpdate > 2000) {
      lastGraphUpdate = millis();
      drawGraphPoint(
        currentScreen == GRAPH_DHT ? avgTemp() : avgLight(),
        currentScreen == GRAPH_DHT ? 0 : 0,
        currentScreen == GRAPH_DHT ? 80 : 2000
      );
    }
  }
}
