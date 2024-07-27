#include <Arduino.h>
#include <Display.h>
#include <Button.h>
#include <Relay.h>

uint64_t systemFanTimeout = 0;
uint64_t systemMistTimeout = 0;

void fanOn(uint64_t timeout) {
  Serial.println("System: Fan On");
  timeout = timeout + millis();

  systemFanTimeout = std::max(timeout, systemFanTimeout);
  relayFanOn();
}

void fanOff() {
  Serial.println("System: Fan Off");
  systemFanTimeout = 0;
  relayFanOff();
}

void pumpOn() {
  Serial.println("System: Pump On");
  relayPumpOn();
}

void pumpOff() {
  Serial.println("System: Pump Off");
  relayPumpOff();
}

void lightOn() {
  Serial.println("System: Light On");
  relayLightOn();
}

void lightOff() {
  Serial.println("System: Light Off");
  relayLightOff();
}

void lightToggle() {
  Serial.println("System: Light Toggle");
  relayLightToggle();
}

void mistOn(uint64_t timeout) {
  Serial.println("System: Mist On");
  timeout = timeout + millis();

  systemMistTimeout = std::max(timeout, systemMistTimeout);
  relayMistOn();
  relayPumpOn();
}

void mistOff() {
  Serial.println("System: Mist Off");
  systemMistTimeout = 0;
  relayMistOff();
}

void auxOn() {
  Serial.println("System: Aux On");
  relayAuxOn();
}

void auxOff() {
  Serial.println("System: Aux Off");
  relayAuxOff();
}

void systemTimeout() {
  uint64_t now = millis();
  if (systemFanTimeout > 0 && now > systemFanTimeout) {
    Serial.println("System: Fan Timeout");
    fanOff();
  }

  if (systemMistTimeout > 0 && now > systemMistTimeout) {
    Serial.println("System: Mist Timeout");
    mistOff();
    pumpOff();
  }
}

void systemLoop() {
  systemTimeout();
}

String defaultFanText() {
  String timeLeft;

  if (systemFanTimeout > 0) {
    timeLeft = String((systemFanTimeout - millis()) / 1000);
  } else {
    timeLeft = "Off";
  }

  return "Fan " + timeLeft;
}

String defaultMistText() {
  String timeLeft;

  if (systemMistTimeout > 0) {
    timeLeft = String((systemMistTimeout - millis()) / 1000);
  } else {
    timeLeft = "Off";
  }

  return "Mist " + timeLeft;
}

void systemSetup() {
  Serial.begin(115200);
  Serial.println("System: Setup");
  auxOn();
}

