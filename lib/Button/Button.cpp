#include <Arduino.h>
#include <OneButton.h>
#include <AnalogButtons.h>
#include <Display.h>
#include <Relay.h>
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


OneButton btnStop = OneButton(BUTTON_STOP, true, false);
OneButton btnStart = OneButton(BUTTON_START, true, false);
OneButton btnLight = OneButton(BUTTON_LIGHT, true, false);
OneButton btnMist = OneButton(BUTTON_MIST, true, false);
OneButton btnUser = OneButton(BUTTON_USER, true, false);
OneButton btnR1 = OneButton(BUTTON_R1, true, false);
OneButton btnR2 = OneButton(BUTTON_R2, true, false);

static void logEvent(const String &event) {
  Serial.println("Button: " + event);
  setDebugText(event, DISPLAY_TIMEOUT);
}

void upClick() {
  logEvent("Up Click");
  menuUpClick();
}

void downClick() {
  logEvent("Down Click");
  menuDownClick();
}

void goClick() {
  logEvent("Go Click");
  menuGoClick();
}

void goHold() {
  logEvent("Go Hold");
  menuGoHold();
}

AnalogButtons analogButtons(BUTTON_PIN, INPUT, 5, 255);

Button btnUp = Button(1750, &upClick);
Button btnDown = Button(2400, &downClick);
Button btnGo = Button(3400, &goClick, &goHold);

void stopClick() {
  logEvent("Stop Click");
  fanOff();
  pumpOff();
  lightOff();
}

void stopHold() {
  logEvent("Stop Hold");
  fanOff();
  pumpOff();
  lightOff();
  auxOff();
}

void startClick() {
  logEvent("Start Click");
  fanOn(getFanTimeout());
  auxOn();
}

void startHold() {
  logEvent("Start Hold");
  fanOn(getFanHoldTimeout());
  auxOn();
}

void lightClick() {
  logEvent("Light Click");
  lightToggle();
}

void mistClick() {
  logEvent("Mist Click");

  if (isMistOff()) {
    mistOn(getMistTimeout());
  } else {
    mistOff();
  }
}

void mistHold() {
  logEvent("Mist Hold");
  mistOn(getMistHoldTimeout());
}

void userClick() {
  logEvent("User Click");

  fanOn(getFanUserTimeout());
  mistOn(getMistUserTimeout());
}

void userHold() {
  logEvent("User Hold");
  fanOff();
}

void r1Click() {
  logEvent("R1 Click");

  if (isMistOff()) {
    mistOn(getMistRemoteTimeout());
  } else {
    mistOff();
  }
}

void r2Click() {
  logEvent("R2 Click");

  if (isFanOff()) {
    fanOn(getFanRemoteTimeout());
  } else {
    fanOff();
  }
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
  btnUser.attachLongPressStart(userHold);
  btnR1.attachClick(r1Click);
  btnR2.attachClick(r2Click);

  analogButtons.add(btnUp);
  analogButtons.add(btnDown);
  analogButtons.add(btnGo);
}

void debugAnalogButton() {
  int buttonValue = analogRead(BUTTON_PIN);

  Serial.print("Analog Button: ");
  Serial.println(buttonValue);

  setDebugText("Analog: " + String(buttonValue), 1000);
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

  if (digitalRead(BUTTON_R1) == LOW) {
    Serial.println("Button: R1");
  }

  if (digitalRead(BUTTON_R2) == LOW) {
    Serial.println("Button: R2");
  }

  debugAnalogButton();
}
