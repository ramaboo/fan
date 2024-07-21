#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define BUTTON_PIN 32
#define BUTTON_UP 1
#define BUTTON_DOWN 2
#define BUTTON_GO 3


#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SDA 16
#define SCL 17

#define R0 14
#define R1 12
#define R2 13
#define R3 15
#define R4 2
#define R5 33


#define I0 18
#define I1 39
#define I2 34
#define I3 35
#define I4 19
#define I5 21
#define I6 22
#define I7 23





Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


bool foobar = false;



void printInputs() {
  Serial.print("Inputs: ");
  Serial.print(digitalRead(I0));
  Serial.print(digitalRead(I1));
  Serial.print(digitalRead(I2));
  Serial.print(digitalRead(I3));
  Serial.print(digitalRead(I4));
  Serial.print(digitalRead(I5));
  Serial.print(digitalRead(I6));
  Serial.println(digitalRead(I7));
}


int readButton() {
  int buttonValue = analogRead(BUTTON_PIN);

  if (buttonValue >= 1500 && buttonValue <= 2000) {
   digitalWrite(R4, HIGH);
    digitalWrite(R5, HIGH);
    return BUTTON_UP;
  }

  if (buttonValue >= 2200 && buttonValue <= 2700) {
    digitalWrite(R4, LOW);
    digitalWrite(R5, LOW);
    return BUTTON_DOWN;
  }

  if (buttonValue >= 3100 && buttonValue <= 3600) {
    return BUTTON_GO;
  }

  return 0;
}

void drawDisplay() {
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);

  display.print("8-bit Bunny");
  display.setCursor(0, 10);

  if (foobar) {
    display.print("True");
  } else {
    display.print("False");
  }

  display.setCursor(0, 20);

  display.setCursor(0, 30);
  String result = String("Button: ") + readButton();
  display.print(result);

  display.display();
}



void setup() {
  Serial.begin(115200);

  Wire.begin(SDA, SCL);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();

  pinMode(R0, OUTPUT);
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(R3, OUTPUT);
  pinMode(R4, OUTPUT);
  pinMode(R5, OUTPUT);

  pinMode(I0, INPUT);
  pinMode(I1, INPUT);
  pinMode(I2, INPUT);
  pinMode(I3, INPUT);
  pinMode(I4, INPUT);
  pinMode(I5, INPUT);
  pinMode(I6, INPUT);
  pinMode(I7, INPUT);
}

void loop() {

  readButton();
  drawDisplay();
    printInputs();

  delay(100);


}


