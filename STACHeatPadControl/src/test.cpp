#include <Arduino.h>

/*
 * Heating Pad — Manual MOSFET Test
 *
 * Purpose:
 *   Test heater switching using Serial Monitor at 9600 baud.
 *   Send '1' to turn heating on; '0' to turn it off.
 *
 * Wiring & hardware: see https://www.tinkercad.com/things/6KzF1TdcLm3-mock-heat-pad-circuits?sharecode=92XF7HVEQEBEarcaOafHfM829VxFzkegQozWMfVBAaw
 * 
 */

const int HEATPAD_PIN = 5;

void setup() {
  pinMode(HEATPAD_PIN, OUTPUT);
  digitalWrite(HEATPAD_PIN, LOW);
  Serial.begin(9600);
  Serial.println("1 = ON, 0 = OFF");
}

void loop() {

  if (Serial.available()) {
    char command = Serial.read();

    if (command == '1') {
      digitalWrite(HEATPAD_PIN, HIGH);
      Serial.println("Heating ON");
    } else if (command == '0') {
      digitalWrite(HEATPAD_PIN, LOW);
      Serial.println("Heating OFF");
    }
  }
  /*
   digitalWrite(HEATPAD_PIN, HIGH);
   delay(3000);
   digitalWrite(HEATPAD_PIN,LOW);
   delay(10000);
   */
}