//Variables............................................INICIALIZACION
const int AO_int = A7;
const int numReadings = 30;   // Numero de muestras
int readings[numReadings];
int readIndex = 0;
int total = 0;
int average = 0;

void setup() {
  Serial.begin(9600);
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

  if (readIndex >= numReadings) {
    readIndex = 0;
  }
  average = total / numReadings;
 
  Serial.println(average);
  delay(1);
}
