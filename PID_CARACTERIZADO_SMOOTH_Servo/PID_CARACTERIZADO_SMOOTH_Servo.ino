#include <PID_v1.h>
#include <Servo.h>

Servo myservo;
//Variables_In............................................INICIALIZACION
const int AI_int = A7;
const int numReadingsI = 30;   // Numero de muestras
int readingsI[numReadingsI];
int readIndexI = 0;
int totalI = 0;
int averageI = 0;
int Angulo = 0;

//Variables_Out............................................INICIALIZACION
const int AO_int = A0;
const int numReadingsO = 30;   // Numero de muestras
int readingsO[numReadingsO];
int readIndexO = 0;
int totalO = 0;
int averageO = 0;

double kp = 0.9 , ki = 3.8 , kd = 0.01;
double input = 0, output = 0, setpoint = 39;
PID myPID(&input, &output, &setpoint, kp, ki, kd, DIRECT);

void setup() {
  Serial.begin(9600); //initialize serial comunication
  myPID.SetMode(AUTOMATIC);   //set PID in Auto mode
  myPID.SetSampleTime(0.1);  // refresh rate of PID controller
  myPID.SetOutputLimits(0, 100);

  for (int thisReadingI = 0; thisReadingI < numReadingsI; thisReadingI++) {
    readingsI[thisReadingI] = 0;
  }

  for (int thisReadingO = 0; thisReadingO < numReadingsO; thisReadingO++) {
    readingsO[thisReadingO] = 0;
  }
  myservo.attach(9);
}
void loop() {

  totalI = totalI - readingsI[readIndexI];
  readingsI[readIndexI] = analogRead(AI_int);
  totalI = totalI + readingsI[readIndexI];
  readIndexI = readIndexI + 1;

  if (readIndexI >= numReadingsI) {
    readIndexI = 0;
  }
  averageI = totalI / numReadingsI;

  input = averageI;
  input = map(input, 0, 1023, 0, 100);
  myPID.Compute(); // calculate new output

  totalO = totalO - readingsO[readIndexO];
  readingsO[readIndexO] = output;
  totalO = totalO + readingsO[readIndexO];
  readIndexO = readIndexO + 1;

  if (readIndexO >= numReadingsO) {
    readIndexO = 0;
  }
  averageO = totalO / numReadingsO;

  Angulo = map(averageO, 0, 100, 0, 180);
  myservo.write(Angulo);

  Serial.print(setpoint);
  Serial.print(",");
  Serial.print(input);
  Serial.print(",");
  Serial.print(Angulo);
  Serial.println();
}
