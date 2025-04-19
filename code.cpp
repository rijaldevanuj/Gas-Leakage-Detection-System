#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD Setup
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Use 0x3F if 0x27 doesn't work

// Pin assignments
const int gasSensorPin = A0;         // MQ-2 analog output
const int buzzerSignalPin = 7;       // Signal pin of active buzzer
const int ledPin = 6;                // LED pin

const int threshold = 170;           // Gas detection threshold

void setup() {
  Serial.begin(9600);

  pinMode(gasSensorPin, INPUT);
  pinMode(buzzerSignalPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  digitalWrite(buzzerSignalPin, LOW); // Ensure buzzer is off
  digitalWrite(ledPin, LOW);          // LED off initially

  lcd.init();           // Initialize the LCD
  lcd.backlight();      // Turn on backlight

  lcd.setCursor(0, 0);
  lcd.print("Gas Detector Ready");
  delay(2000);
  lcd.clear();
}

void loop() {
  int gasValue = analogRead(gasSensorPin);

  // Display gas value
  lcd.setCursor(0, 0);
  lcd.print("Gas Level: ");
  lcd.print(gasValue);
  lcd.print("   ");  // Clear leftover characters

  Serial.print("Gas Level: ");
  Serial.print(gasValue);

  if (gasValue > threshold) {
    // Alert condition
    digitalWrite(buzzerSignalPin, HIGH);
    digitalWrite(ledPin, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("!! ALERT !!  ");
    Serial.println(" --> ⚠ Detected!");
  } else {
    // Safe condition
    digitalWrite(buzzerSignalPin, LOW);
    digitalWrite(ledPin, LOW);
    lcd.setCursor(0, 1);
    lcd.print("Safe Environment ");
    Serial.println(" --> Safe ✅");
  }

  delay(1000);
}
