#include <Arduino.h>
#include <Display.h>

#define R0 14
#define R1 12
#define R2 13 // Unused
#define R3 15
#define R4 2
#define R5 33

#define RELAY_FAN R1
#define RELAY_PUMP R0
#define RELAY_MIST R3
#define RELAY_LIGHT R5
#define RELAY_AUX R4

#define RELAY_CYCLE_DELAY_TIME 5000

#define DISPLAY_TIMEOUT 2000

void relayFanOn() {
  Serial.println("Relay: Fan On");
  digitalWrite(RELAY_FAN, HIGH);
}

boolean isFanOn() {
  return digitalRead(RELAY_FAN) == HIGH;
}

void relayFanOff() {
  Serial.println("Relay: Fan Off");
  digitalWrite(RELAY_FAN, LOW);
}

boolean isFanOff() {
  return digitalRead(RELAY_FAN) == LOW;
}

void relayPumpOn() {
  Serial.println("Relay: Pump On");
  digitalWrite(RELAY_PUMP, HIGH);
}

boolean isPumpOn() {
  return digitalRead(RELAY_PUMP) == HIGH;
}

void relayPumpOff() {
  Serial.println("Relay: Pump Off");
  digitalWrite(RELAY_PUMP, LOW);
}

boolean isPumpOff() {
  return digitalRead(RELAY_PUMP) == LOW;
}

void relayLightOn() {
  Serial.println("Relay: Light On");
  digitalWrite(RELAY_LIGHT, HIGH);
}

boolean isLightOn() {
  return digitalRead(RELAY_LIGHT) == HIGH;
}

void relayLightOff() {
  Serial.println("Relay: Light Off");
  digitalWrite(RELAY_LIGHT, LOW);
}

boolean isLightOff() {
  return digitalRead(RELAY_LIGHT) == LOW;
}

void relayLightToggle() {
  Serial.println("Relay: Light Toggle");
  digitalWrite(RELAY_LIGHT, !digitalRead(RELAY_LIGHT));
}

void relayMistOn() {
  Serial.println("Relay: Mist On");
  digitalWrite(RELAY_MIST, HIGH);
}

boolean isMistOn() {
  return digitalRead(RELAY_MIST) == HIGH;
}

void relayMistOff() {
  Serial.println("Relay: Mist Off");
  digitalWrite(RELAY_MIST, LOW);
}

boolean isMistOff() {
  return digitalRead(RELAY_MIST) == LOW;
}

void relayAuxOn() {
  Serial.println("Relay: Aux On");
  digitalWrite(RELAY_AUX, HIGH);
}

boolean isAuxOn() {
  return digitalRead(RELAY_AUX) == HIGH;
}

void relayAuxOff() {
  Serial.println("Relay: Aux Off");
  digitalWrite(RELAY_AUX, LOW);
}

boolean isAuxOff() {
  return digitalRead(RELAY_AUX) == LOW;
}

void relayAllOn() {
  Serial.println("Relay: All On");
  digitalWrite(R0, HIGH);
  digitalWrite(R1, HIGH);
  digitalWrite(R2, HIGH);
  digitalWrite(R3, HIGH);
  digitalWrite(R4, HIGH);
  digitalWrite(R5, HIGH);
}

void relayAllOff() {
  Serial.println("Relay: All Off");
  digitalWrite(R0, LOW);
  digitalWrite(R1, LOW);
  digitalWrite(R2, LOW);
  digitalWrite(R3, LOW);
  digitalWrite(R4, LOW);
  digitalWrite(R5, LOW);
}

void cycleRelays() {
  Serial.println("Relay 0 (Pump): On");
  digitalWrite(R0, HIGH);
  delay(RELAY_CYCLE_DELAY_TIME);
  Serial.println("Relay 0 (Pump): Off");
  digitalWrite(R0, LOW);
  delay(RELAY_CYCLE_DELAY_TIME);
  Serial.println("Relay 1 (Fan): On");
  digitalWrite(R1, HIGH);
  delay(RELAY_CYCLE_DELAY_TIME);
  Serial.println("Relay 1 (Fan): Off");
  digitalWrite(R1, LOW);
  delay(RELAY_CYCLE_DELAY_TIME);
  Serial.println("Relay 2 (Unused): On");
  digitalWrite(R2, HIGH);
  delay(RELAY_CYCLE_DELAY_TIME);
  Serial.println("Relay 2 (Unused): Off");
  digitalWrite(R2, LOW);
  delay(RELAY_CYCLE_DELAY_TIME);
  Serial.println("Relay 3 (Mist): On");
  digitalWrite(R3, HIGH);
  delay(RELAY_CYCLE_DELAY_TIME);
  Serial.println("Relay 3 (Mist): Off");
  digitalWrite(R3, LOW);
  delay(RELAY_CYCLE_DELAY_TIME);
  Serial.println("Relay 4 (Light): On");
  digitalWrite(R4, HIGH);
  delay(RELAY_CYCLE_DELAY_TIME);
  Serial.println("Relay 4 (Light): Off");
  digitalWrite(R4, LOW);
  delay(RELAY_CYCLE_DELAY_TIME);
  Serial.println("Relay 5 (Aux): On");
  digitalWrite(R5, HIGH);
  delay(RELAY_CYCLE_DELAY_TIME);
  Serial.println("Relay 5 (Aux): Off");
  digitalWrite(R5, LOW);
  delay(RELAY_CYCLE_DELAY_TIME);
}

void relaySetup() {
  Serial.println("Relay: Setup");
  pinMode(R0, OUTPUT);
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(R3, OUTPUT);
  pinMode(R4, OUTPUT);
  pinMode(R5, OUTPUT);
}

String defaultRelayText() {
  String fan = digitalRead(RELAY_FAN) == HIGH ? "X" : "O";
  String pump = digitalRead(RELAY_PUMP) == HIGH ? "X" : "O";
  String light = digitalRead(RELAY_LIGHT) == HIGH ? "X" : "O";
  String mist = digitalRead(RELAY_MIST) == HIGH ? "X" : "O";
  String aux = digitalRead(RELAY_AUX) == HIGH ? "X" : "O";

  return "F" + fan + " P" + pump + " L" + light + " M" + mist + " A" + aux;
}
