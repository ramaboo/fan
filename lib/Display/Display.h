#pragma once

#include <Arduino.h>

#define DISPLAY_TIMEOUT 2000

void displaySetup();
void displayLoop();

void setDebugText(String text, uint64_t timeout);

void debugDisplay();
