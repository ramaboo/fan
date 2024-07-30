#include <Arduino.h>
#include <Display.h>
#include <Button.h>
#include <Relay.h>
#include <System.h>
#include <Menu.h>

#define LOOP_DELAY 5

void setup() {
  systemSetup();
  menuSetup();
  displaySetup();
  buttonSetup();
  relaySetup();
  menuLoad();
}

void loop() {
  buttonLoop();
  systemLoop();
  displayLoop();
  delay(LOOP_DELAY);
  //debugInputs();
}


