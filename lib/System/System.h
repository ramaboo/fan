#pragma once

void systemSetup();
void systemLoop();

void fanOn(uint64_t timeout);
void fanOff();
void pumpOn();
void pumpOff();
void lightOn();
void lightOff();
void lightToggle();
void mistOn(uint64_t timeout);
void mistOff();
void auxOn();
void auxOff();

String defaultFanText();
String defaultMistText();
