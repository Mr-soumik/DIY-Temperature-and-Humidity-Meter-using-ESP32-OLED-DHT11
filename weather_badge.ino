#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

float temperature = 0;
float humidity = 0;
unsigned long lastRead = 0;
int animFrame = 0;
unsigned long lastAnim = 0;

void bootAnimation() {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  for (int i = 0; i <= 10; i++) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(20, 20);
    display.println("TechTadka360");
    display.drawRect(20, 35, i * 9, 10, SSD1306_WHITE);
    display.display();
    delay(80);
  }
  delay(400);
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(10, 20);
  display.println("Weather");
  display.setCursor(25, 40);
  display.println("Badge");
  display.display();
  delay(1200);
}

void drawColdFace(int cx, int cy) {
  display.fillCircle(cx, cy, 14, SSD1306_WHITE);
  display.fillCircle(cx - 5, cy - 3, 2, SSD1306_BLACK);
  display.fillCircle(cx + 5, cy - 3, 2, SSD1306_BLACK);
  display.drawLine(cx - 6, cy + 6, cx + 6, cy + 6, SSD1306_BLACK);
  int shake = (animFrame % 2 == 0) ? 0 : 1;
  display.drawLine(cx - 20 + shake, cy - 10, cx - 16 + shake, cy - 4, SSD1306_WHITE);
  display.drawLine(cx + 16 - shake, cy - 10, cx + 20 - shake, cy - 4, SSD1306_WHITE);
}

void drawHappyFace(int cx, int cy) {
  display.fillCircle(cx, cy, 14, SSD1306_WHITE);
  display.fillCircle(cx - 5, cy - 3, 2, SSD1306_BLACK);
  display.fillCircle(cx + 5, cy - 3, 2, SSD1306_BLACK);
  display.drawLine(cx - 6, cy + 5, cx, cy + 8, SSD1306_BLACK);
  display.drawLine(cx, cy + 8, cx + 6, cy + 5, SSD1306_BLACK);
}

void drawHotFace(int cx, int cy) {
  display.fillCircle(cx, cy, 14, SSD1306_WHITE);
  display.fillCircle(cx - 5, cy - 3, 2, SSD1306_BLACK);
  display.fillCircle(cx + 5, cy - 3, 2, SSD1306_BLACK);
  display.drawLine(cx - 6, cy + 7, cx + 6, cy + 3, SSD1306_BLACK);
  int drop = animFrame % 3;
  display.fillCircle(cx + 16, cy - 6 + drop * 4, 2, SSD1306_WHITE);
}

void drawFace() {
  int cx = 30;
  int cy = 44;
  if (temperature < 20) drawColdFace(cx, cy);
  else if (temperature <= 28) drawHappyFace(cx, cy);
  else drawHotFace(cx, cy);
}

void drawReadings() {
  display.setTextSize(1);
  display.setCursor(58, 5);
  display.println("TechTadka360");
  display.drawLine(0, 15, 128, 15, SSD1306_WHITE);

  display.setTextSize(2);
  display.setCursor(60, 22);
  display.print(temperature, 1);
  display.println("C");

  display.setTextSize(1);
  display.setCursor(60, 42);
  display.print("Hum: ");
  display.print(humidity, 0);
  display.println("%");

  display.setCursor(0, 56);
  if (temperature < 20) display.println("COLD");
  else if (temperature <= 28) display.println("NICE");
  else display.println("HOT");
}

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  dht.begin();
  bootAnimation();
}

void loop() {
  if (millis() - lastRead > 2000) {
    float t = dht.readTemperature();
    float h = dht.readHumidity();
    if (!isnan(t)) temperature = t;
    if (!isnan(h)) humidity = h;
    lastRead = millis();
  }

  if (millis() - lastAnim > 400) {
    animFrame++;
    lastAnim = millis();
  }

  display.clearDisplay();
  drawFace();
  drawReadings();
  display.display();
  delay(50);
}
