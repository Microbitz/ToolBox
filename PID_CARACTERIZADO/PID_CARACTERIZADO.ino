#include <PID_v1.h>

//Variables............................................INICIALIZACION
const int AO_int = A0;
const int numReadings = 30;   // Numero de muestras
int readings[numReadings];
int readIndex = 0;
int total = 0;
int average = 0;


double kp = 0.4 , ki = 4.8 , kd = 0.01;
double input = 0, output = 0, setpoint = 50;
PID myPID(&input, &output, &setpoint, kp, ki, kd, DIRECT);

void setup() {
  Serial.begin(9600); //initialize serial comunication
  myPID.SetMode(AUTOMATIC);   //set PID in Auto mode
  myPID.SetSampleTime(0.1);  // refresh rate of PID controller
  myPID.SetOutputLimits(0, 100);

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

  input = average;
  input = map(input, 0, 1023, 0, 100);
  myPID.Compute(); // calculate new output

  Serial.print(setpoint);
  Serial.print(",");
  Serial.print(input);
  Serial.print(",");
  Serial.println(output);

}
