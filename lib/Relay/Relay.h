#pragma once

void relaySetup();

void cycleRelays();

void relayAllOn();
void relayAllOff();

void relayFanOn();
boolean isFanOn();
void relayFanOff();
boolean isFanOff();

void relayPumpOn();
boolean isPumpOn();
void relayPumpOff();
boolean isPumpOff();

void relayMistOn();
boolean isMistOn();
void relayMistOff();
boolean isMistOff();

void relayLightOn();
boolean isLightOn();
void relayLightOff();
boolean isLightOff();
void relayLightToggle();

void relayAuxOn();
boolean isAuxOn();
void relayAuxOff();
boolean isAuxOff();

String defaultRelayText();
