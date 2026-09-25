#include <Arduino.h>
#include <Servo.h>

Servo servo1;

const int SERVO_PIN = 3;
// Nominal estimates, not measured calibration:
// ES3004 travel is approximately 145 degrees over 700–2300 microseconds.
// Define 1003 microseconds as our relative zero position.
// Replace CAL_TRAVEL_DEG with the measured travel between these pulse widths.
const int CAL_START_US = 1003;
const int CAL_END_US = 1997;
const float CAL_TRAVEL_DEG = 90.0f;
const int SWEEP_DEG = 90;
const int STEP_DELAY_MS = 15;

// Absolute target relative to our defined zero, not an additional rotation.
// All servos passed here use the shared calibration constants above.
void moveToAngle(Servo &servo, float angle) {
  angle = constrain(angle, 0.0f, CAL_TRAVEL_DEG);
  int pulse = CAL_START_US
      + (angle / CAL_TRAVEL_DEG) * (CAL_END_US - CAL_START_US)
      + 0.5f;
  servo.writeMicroseconds(pulse);
}

void setup() {
  Serial.begin(115200);
  servo1.attach(SERVO_PIN, 700, 2300);
  moveToAngle(servo1, 0);
  delay(1000);  // allow time to reach the starting position.
  Serial.println("Servo ready");
}

void loop() {
  Serial.println("Sweeping forward approximately 90 degrees");
  for (int angle = 0; angle <= SWEEP_DEG; angle++) {
    moveToAngle(servo1, angle);
    delay(STEP_DELAY_MS);
  }
  delay(1000);

  Serial.println("Sweeping back");
  for (int angle = SWEEP_DEG; angle >= 0; angle--) {
    moveToAngle(servo1, angle);
    delay(STEP_DELAY_MS);
  }
  delay(1000);
}
