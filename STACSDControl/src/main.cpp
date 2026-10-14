#include <Arduino.h>
#include <Servo.h>
#include <SD.h>
#include <SPI.h>

File testFile;
const int chipSelect = 5;  
unsigned long count = 0;
bool sdReady = false;

void setup() {
  Serial.begin(9600);
  delay(1000);

  Serial.println("Initializing SD card...");

  sdReady = SD.begin(chipSelect);

  if (!sdReady) {
    Serial.println("SD initialization failed. Check CS, wiring, and format.");
    return;
  }

  Serial.println("SD card initialized.");
}

void loop() {
  if (!sdReady) {
    Serial.println("Loop running, but SD card is not initialized.");
    delay(3000);
    return;
  }

  testFile = SD.open("LOOPTEST.txt", FILE_WRITE);

  if (testFile) {
    testFile.print("Hello World! Count: ");
    testFile.println(count);
    testFile.close();  // Also flushes buffered data to the card

    Serial.print("File written and closed. Count: ");
    Serial.println(count);
    count++;
  } else {
    Serial.println("Failed to open LOOPTEST.txt.");
  }

  delay(1000);
}


