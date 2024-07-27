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

String displayButtonText = "";
uint64_t displayButtonTimeout = 0;

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
  display.print("XXXX");
  display.setCursor(0, 20);
  display.print("XXXX");
  display.setCursor(0, 30);
  display.print("XXXX");
  display.setCursor(0, 40);
  display.print("123456789012345678901");
  display.setCursor(0, 50);
  display.print("--------------------");
  display.display();
}

void setButtonText(String text, uint64_t timeout) {
  displayButtonText = text;

  if (timeout > 0) {
    displayButtonTimeout = millis() + timeout;
  } else {
    displayButtonTimeout = 0;
  }
}

void displayTimeout() {
  uint64_t now = millis();

  if (displayButtonTimeout > 0 && now > displayButtonTimeout) {
    displayButtonText = "";
    displayButtonTimeout = 0;
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
  display.print(displayButtonText);

  display.display();
}
