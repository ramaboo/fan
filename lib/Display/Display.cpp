#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Relay.h>
#include <System.h>
#include <Menu.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SDA 16
#define SCL 17

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

String displayDebugText = "";
uint64_t displayDebugTimeout = 0;

void displaySetup() {
  Serial.println("Display: Setup");
  Wire.begin(SDA, SCL);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.cp437(true);
  display.clearDisplay();
  display.display();
}

void debugDisplay() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("8-bit Bunny");
  display.setCursor(0, 10);
  display.print("123456789012345678901");
  display.display();
}

void setDebugText(String text, uint64_t timeout) {
  displayDebugText = text;

  if (timeout > 0) {
    displayDebugTimeout = millis() + timeout;
  } else {
    displayDebugTimeout = 0;
  }
}

void displayTimeout() {
  uint64_t now = millis();

  if (displayDebugTimeout > 0 && now > displayDebugTimeout) {
    displayDebugText = "";
    displayDebugTimeout = 0;
  }
}

void displayLoop() {
  displayTimeout();
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, 0);
  display.print(menuTitleText());

  display.setCursor(0, 10);
  display.print(menuValueText());

  display.drawFastHLine(0, 20, 128, SSD1306_WHITE);

  display.setCursor(0, 24);
  display.print(defaultFanText());

  display.setCursor(0, 33);
  display.print(defaultMistText());

  display.setCursor(0, 42);
  display.print(defaultRelayText());

  display.drawFastHLine(0, 52, 128, SSD1306_WHITE);

  display.setCursor(0, 56);
  display.print(displayDebugText);

  display.display();
}
