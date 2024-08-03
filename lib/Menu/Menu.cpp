#include <Arduino.h>
#include <Preferences.h>

#define NUM_ITEMS 9
#define MAX_TIMEOUT 10800

Preferences prefs;

struct menuStruct {
  String title;
  const char* key;
  int32_t timeout;
  int32_t defaultTimeout;
  int32_t increment;
  boolean display;
};

menuStruct menuItems[NUM_ITEMS] = {
  {"8-BIT BUNNY", "bunny", 0, 0, 0, false},
  {"Fan", "fan", 0, 3600, 60, true},
  {"Mist", "mist", 0, 300, 10, true},
  {"Fan User", "fan_user", 0, 300, 10, true},
  {"Mist User", "mist_user", 0, 90, 10, true},
  {"Fan Hold", "fan_hold", 0, 3600, 60, true},
  {"Mist Hold", "mist_hold", 0, 600, 10, true},
  {"Fan Remote", "fan_remote", 0, 1800, 60, true},
  {"Mist Remote", "mist_remote", 0, 300, 10, true},
};

uint8_t menuIndex = 0;

uint64_t getFanTimeout() {
  return menuItems[1].timeout * 1000;
}

uint64_t getMistTimeout() {
  return menuItems[2].timeout * 1000;
}

uint64_t getFanUserTimeout() {
  return menuItems[3].timeout * 1000;
}

uint64_t getMistUserTimeout() {
  return menuItems[4].timeout * 1000;
}

uint64_t getFanHoldTimeout() {
  return menuItems[5].timeout * 1000;
}

uint64_t getMistHoldTimeout() {
  return menuItems[6].timeout * 1000;
}

uint64_t getFanRemoteTimeout() {
  return menuItems[7].timeout * 1000;
}

uint64_t getMistRemoteTimeout() {
  return menuItems[8].timeout * 1000;
}

void debugMenu() {
  Serial.println("Menu: Debug");

  for (uint8_t i = 0; i < NUM_ITEMS; i++) {
    Serial.print(menuItems[i].title);
    Serial.print(": ");
    Serial.println(menuItems[i].timeout);
  }
}

void menuGoClick() {
  menuIndex = menuIndex + 1;
  if (menuIndex >= NUM_ITEMS) {
    menuIndex = 0;
  }
}

void menuReset() {
  Serial.println("Menu: Reset");

  prefs.clear();

  for (uint8_t i = 0; i < NUM_ITEMS; i++) {
    menuItems[i].timeout = menuItems[i].defaultTimeout;
    prefs.putInt(menuItems[i].key, menuItems[i].defaultTimeout);
  }
}

void menuGoHold() {
  menuReset();
}

void menuUpClick() {
  menuItems[menuIndex].timeout = menuItems[menuIndex].timeout + menuItems[menuIndex].increment;

  if (menuItems[menuIndex].timeout > MAX_TIMEOUT) {
    menuItems[menuIndex].timeout = MAX_TIMEOUT;
  }

  prefs.putInt(menuItems[menuIndex].key, menuItems[menuIndex].timeout);
}

void menuDownClick() {
  menuItems[menuIndex].timeout = menuItems[menuIndex].timeout - menuItems[menuIndex].increment;

  if (menuItems[menuIndex].timeout < 0) {
    menuItems[menuIndex].timeout = 0;
  }

  prefs.putInt(menuItems[menuIndex].key, menuItems[menuIndex].timeout);
}

int32_t getTimeout(menuStruct item) {
  return prefs.getInt(item.key, item.defaultTimeout);
}

void menuLoad() {
  Serial.println("Menu: Load");

  for (uint8_t i = 0; i < NUM_ITEMS; i++) {
    menuItems[i].timeout = getTimeout(menuItems[i]);
  }
}

void menuSetup() {
  Serial.println("Menu: Setup");

  prefs.begin("app");
  menuLoad();
}

String secondsToTime(int32_t seconds) {
  int32_t hours = seconds / 3600;
  int32_t minutes = (seconds % 3600) / 60;
  int32_t secs = seconds % 60;

  char buffer [10];
  sprintf(buffer, "%02d:%02d:%02d", hours, minutes, secs);
  return String(buffer);
}

String menuTitleText() {
  return menuItems[menuIndex].title;
}

String menuValueText() {
  if (menuItems[menuIndex].display) {
    return secondsToTime(menuItems[menuIndex].timeout);
  } else {
    return "";
  }
}

