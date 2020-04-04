

//Botones..............................................INICIALIZACION
bool Standby = false;
float T_on;
int DIN1 = A0;
int Dstate1 = 0;
int V1;


void setup() {
  pinMode(DIN1, INPUT);
  Serial.begin(9600);
  //Interrupcion TIMER1.......................................CONFIG
  cli();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;
  OCR1A = 12499;
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (0 << CS12) | (1 << CS11) | (0 << CS10);
  TIMSK1 |= (1 << OCIE1A);
  sei(); // allow interrupts
}

//Interrupcion 1 Segundo..................................OPERATIVO
ISR(TIMER1_COMPA_vect) {
  if (Standby == true) {
    T_on = T_on + 0.01;
  }
  if (T_on >= 2.0) {   // tiempo en segundos con decimales si quieres menos cambiar el valor despues de >=
    T_on = 0.0;
    Standby = false;
  }
}

void loop() {

  Dstate1 = digitalRead(DIN1);

  if (Standby == false) {      //Colocar dentro los botones
    if (Dstate1 == HIGH) {
      Standby = true;
      T_on = 0.0;
      V1 = V1 + 1;
    }
  }
  Serial.println(V1);
}
