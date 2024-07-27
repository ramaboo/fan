#include <Arduino.h>
#include <OneButton.h>
#include <AnalogButtons.h>
#include <Display.h>
#include <System.h>
#include <Menu.h>

#define I0 18
#define I1 39
#define I2 34
#define I3 35
#define I4 19
#define I5 21 // Unused
#define I6 22
#define I7 23

#define BUTTON_STOP I0
#define BUTTON_START I1
#define BUTTON_LIGHT I2
#define BUTTON_MIST I3
#define BUTTON_USER I4
#define BUTTON_R1 I7
#define BUTTON_R2 I6

#define BUTTON_PIN 32

#define DISPLAY_TIMEOUT 2000

#define MIST_HOLD_TIMEOUT 10000

#define ON HIGH
#define OFF LOW

OneButton btnStop = OneButton(BUTTON_STOP, true, false);
OneButton btnStart = OneButton(BUTTON_START, true, false);
OneButton btnLight = OneButton(BUTTON_LIGHT, true, false);
OneButton btnMist = OneButton(BUTTON_MIST, true, false);
OneButton btnUser = OneButton(BUTTON_USER, true, false);
OneButton btnR1 = OneButton(BUTTON_R1, true, false);
OneButton btnR2 = OneButton(BUTTON_R2, true, false);

void upClick() {
  Serial.println("Button Up: Click");
  setButtonText("Up Click", DISPLAY_TIMEOUT);
  menuUpClick();
}

void downClick() {
  Serial.println("Button Down: Click");
  setButtonText("Down Click", DISPLAY_TIMEOUT);
  menuDownClick();
}

void goClick() {
  Serial.println("Button Go: Click");
  setButtonText("Go Click", DISPLAY_TIMEOUT);
  menuGoClick();
}

void goHold() {
  Serial.println("Button Go: Hold");
  setButtonText("Go Hold", DISPLAY_TIMEOUT);
  menuGoHold();
}

AnalogButtons analogButtons(BUTTON_PIN, INPUT, 5, 100);

// With USB cable connected to the computer, the button values are:
Button btnUpConnected = Button(1900, &upClick);
Button btnDownConnected = Button(2500, &downClick);
Button btnGoConnected = Button(3450, &goClick, &goHold);

// Without USB cable:
Button btnUp = Button(1550, &upClick);
Button btnDown = Button(2300, &downClick);
Button btnGo = Button(3300, &goClick, &goHold);

void stopClick() {
  Serial.println("Button Stop: Click");
  setButtonText("Stop Click", DISPLAY_TIMEOUT);
  fanOff();
  pumpOff();
  lightOff();
  mistOff();
}

void stopHold() {
  Serial.println("Button Stop: Hold");
  setButtonText("Stop Hold", DISPLAY_TIMEOUT);
  fanOff();
  pumpOff();
  lightOff();
  mistOff();
  auxOff();
}

void startClick() {
  Serial.println("Button Start: Click");
  setButtonText("Start Click", DISPLAY_TIMEOUT);
  fanOn(getFanTimeout());
  auxOn();
}

void startHold() {
  Serial.println("Button Start: Hold");
  setButtonText("Start Hold", DISPLAY_TIMEOUT);
  fanOn(getFanHoldTimeout());
  auxOn();
}

void lightClick() {
  Serial.println("Button Light: Click");
  setButtonText("Light Click", DISPLAY_TIMEOUT);
  lightToggle();
}

void mistClick() {
  Serial.println("Button Mist: Click");
  setButtonText("Mist Click", DISPLAY_TIMEOUT);
  mistOn(getMistTimeout());
}

void mistHold() {
  Serial.println("Button Mist: Hold");
  setButtonText("Mist Hold", DISPLAY_TIMEOUT);
  mistOn(getMistHoldTimeout());
}

void userClick() {
  Serial.println("Button User: Click");
  setButtonText("User Click", DISPLAY_TIMEOUT);
  // TODO
}

void r1Click() {
  Serial.println("Button R1: Click");
  setButtonText("R1 Click", DISPLAY_TIMEOUT);
  // TODO
}

void r2Click() {
  Serial.println("Button R2: Click");
  setButtonText("R2 Click", DISPLAY_TIMEOUT);
  // TODO
}

void buttonSetup() {
  Serial.println("Button: Setup");
  btnStop.attachClick(stopClick);
  btnStop.attachLongPressStart(stopHold);
  btnStart.attachClick(startClick);
  btnStart.attachLongPressStart(startHold);
  btnLight.attachClick(lightClick);
  btnMist.attachClick(mistClick);
  btnMist.attachLongPressStart(mistHold);
  btnUser.attachClick(userClick);
  btnR1.attachClick(r1Click);
  btnR2.attachClick(r2Click);

  analogButtons.add(btnUpConnected);
  analogButtons.add(btnDownConnected);
  analogButtons.add(btnGoConnected);
  analogButtons.add(btnUp);
  analogButtons.add(btnDown);
  analogButtons.add(btnGo);
}

void debugSystemButton() {
  int buttonValue = analogRead(BUTTON_PIN);

  Serial.print("Button: ");
  Serial.println(buttonValue);
}

void buttonLoop() {
  btnStop.tick();
  btnStart.tick();
  btnLight.tick();
  btnMist.tick();
  btnUser.tick();
  btnR1.tick();
  btnR2.tick();
  analogButtons.check();
}

void debugInputs() {
  Serial.print("Inputs: ");
  Serial.print(digitalRead(I0));
  Serial.print(digitalRead(I1));
  Serial.print(digitalRead(I2));
  Serial.print(digitalRead(I3));
  Serial.print(digitalRead(I4));
  Serial.print(digitalRead(I5));
  Serial.print(digitalRead(I6));
  Serial.println(digitalRead(I7));

  if (digitalRead(BUTTON_STOP) == LOW) {
    Serial.println("Button: Stop");
  }

  if (digitalRead(BUTTON_START) == LOW) {
    Serial.println("Button: Start");
  }

  if (digitalRead(BUTTON_LIGHT) == LOW) {
    Serial.println("Button: Light");
  }

  if (digitalRead(BUTTON_MIST) == LOW) {
    Serial.println("Button: Mist");
  }

  if (digitalRead(BUTTON_USER) == LOW) {
    Serial.println("Button: User");
  }

  if (digitalRead(BUTTON_R2) == LOW) {
    Serial.println("Button: R2");
  }

  if (digitalRead(BUTTON_R1) == LOW) {
    Serial.println("Button: R1");
  }
}
