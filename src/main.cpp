#include <Arduino.h>
#include <Display.h>
#include <Button.h>
#include <Relay.h>
#include <System.h>
#include <Menu.h>

#define LOOP_DELAY 5

void setup() {
  systemSetup();
  relaySetup();
  relayAllOff();
  auxOn();
  menuSetup();
  // menuReset();
  displaySetup();
  buttonSetup();
}

void loop() {
  buttonLoop();
  systemLoop();
  displayLoop();
  delay(LOOP_DELAY);
  // debugInputs();
}


