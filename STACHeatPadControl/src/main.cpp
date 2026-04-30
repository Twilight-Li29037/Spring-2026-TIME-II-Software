#include <Arduino.h>

int resistorPin = A1;
int raw = 0;
const float Vin = 5;
const float R1  = 3300;

#define HEATPAD_PIN 5

void setup() {
  pinMode(HEATPAD_PIN, OUTPUT);
  digitalWrite(HEATPAD_PIN, LOW);
  Serial.println(F("Heatpad pin set to LOW"));

  Serial.begin(9600);
  delay(200);
  Serial.println(F("Heatpad and Thermistor Control"));
}

float readResistor(int pin){
  delay(10);
  int sum = 0;
  (void)analogRead(pin);
  for (uint8_t i = 0; i < 20; i++) { sum += analogRead(pin); delay(2); }
  raw = sum / 20;

  if (raw < 3 || raw > 1020) { Serial.println(F("ADC out of range")); return 0; }

  float Vout = (raw / 1023.0f) * Vin;
  float R2   = R1 * (Vout / (Vin - Vout));

  Serial.print(F("Raw ADC: ")); Serial.println(raw);
  Serial.print(F("Vout: ")); Serial.println(Vout);

  delay(200);
  return R2;
}

void handleHeatPads(float reading, int pin, bool allowHeat, unsigned long nowMs){
  if (!allowHeat) {
    Serial.println(F("Heating not allowed"));
    return;
  }

  if (reading > 5000) {
    Serial.println(F("Starting heating"));
    digitalWrite(HEATPAD_PIN, HIGH);
    delay(30000);
    digitalWrite(HEATPAD_PIN, LOW);
    Serial.println(F("Heating stopped"));
  } else {
    Serial.println(F("Reading not above threshold, no heating"));
  }
}

void loop() {
  unsigned long nowMs = millis();
  Serial.print(F("Loop start at millis: ")); Serial.println(nowMs);
  float reading = readResistor(resistorPin);
  handleHeatPads(reading, resistorPin, true, nowMs);
  
  // Assuming NTC thermistor: R25=10000, beta=3950, T25=298.15K
  float T0 = 298.15; // 25C in Kelvin
  float R25 = 10000.0;
  float beta = 3950.0;
  float tempK = 1.0 / (1.0/T0 + (1.0/beta) * log(reading / R25));
  float tempC = tempK - 273.15;
  
  Serial.print("Resistance: "); Serial.print(reading); Serial.println(" ohms");
  Serial.print("Temperature: "); Serial.print(tempC); Serial.println(" C");
  delay(100);
}
