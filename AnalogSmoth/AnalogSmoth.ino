#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2);

//Variables............................................INICIALIZACION
const int AO_int = A0;
const int numReadings = 30;   // Numero de muestras
int readings[numReadings];
int readIndex = 0;
int total = 0;
int average = 0;

void setup() {
  Serial.begin(9600);
  //LCD.........................................................CONFIG
  lcd.init();
  lcd.clear ();
  lcd.home ();
  lcd.print("Volt:");
  lcd.setCursor(0, 1);
  lcd.setBacklight(HIGH);

  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
}

void loop() {
  total = total - readings[readIndex];
  readings[readIndex] = analogRead(AO_int);
  total = total + readings[readIndex];
  readIndex = readIndex + 1;

  if (readIndex >= numReadings) {
    readIndex = 0;
  }
  average = total / numReadings;
  //LCD.........................................................Operativo
  lcd.print(average);
  lcd.print("  ");
  lcd.setCursor(0, 1);

  //Transmision.........................................................Operativo

  Serial.print(analogRead(AO_int));
  Serial.print(",");
  Serial.println(average);
  delay(1);
}
