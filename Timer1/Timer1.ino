int tiempo;

void setup() {
  // Timer 0 is not usable for requested frequency.
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
 

  // TIMER 1 for interrupt frequency 1 Hz:
  cli(); // stop interrupts
  TCCR1A = 0; // set entire TCCR1A register to 0
  TCCR1B = 0; // same for TCCR1B
  TCNT1  = 0; // initialize counter value to 0
  // set compare match register for 1 Hz increments
  OCR1A = 62499; // = 16000000 / (256 * 1) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS12, CS11 and CS10 bits for 256 prescaler
  TCCR1B |= (1 << CS12) | (0 << CS11) | (0 << CS10);
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  sei(); // allow interrupts

}

void(* resetFunc) (void) = 0;

ISR(TIMER1_COMPA_vect) {
  tiempo = tiempo + 1;
  if (tiempo == 10) resetFunc();
}

void loop() {
  delay(1000);
  Serial.println(tiempo);
  digitalWrite(LED_BUILTIN, HIGH);
}
