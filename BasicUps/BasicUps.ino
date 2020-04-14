int voltage_1_raw;
float voltage_1;
int voltage_2_raw;
float voltage_2;
int voltage_3_raw;
float voltage_3;

const float voltage_1_max = 5.5;
const float voltage_1_min = 1.0;

const float voltage_2_max = 5.5;
const float voltage_2_min = 1.0;

const float voltage_3_max = 5.5;
const float voltage_3_min = 1.0;


bool UPS = false;

void setup() {
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  delay(2000);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);

}

void loop() {

  voltage_1_raw = analogRead(A5);
  voltage_1 = voltage_1_raw * (5.0 / 1023.0);
  voltage_1 = voltage_1 * 10.0;
  voltage_2_raw = analogRead(A6);
  voltage_2 = voltage_2_raw * (5.0 / 1023.0);
  voltage_2 = voltage_2 * 10.0;
  voltage_3_raw = analogRead(A7);
  voltage_3 = voltage_3_raw * (5.0 / 1023.0);
  voltage_3 = voltage_3 * 10.0;

  Serial.print(voltage_1);

  Serial.print(",");
  Serial.print(voltage_2);

  Serial.print(",");
  Serial.println(voltage_3);

  if (voltage_3 > voltage_3_min) {
    digitalWrite(2, HIGH);
    digitalWrite(4, LOW);
  }
  if (voltage_3 < voltage_3_min) {
    digitalWrite(2, LOW);
    digitalWrite(4, HIGH);
  }
  if (voltage_1 < voltage_1_min) {
    digitalWrite(3, HIGH);
  } else {
    digitalWrite(3, LOW);
  }
}
