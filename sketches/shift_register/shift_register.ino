int data_pin = 6;
int blank_pin = 5;
int latch_pin = 4;
int clock_pin = 3;
int clear_pin = 2;

int count = 0;
int i;

void setup() {
  // put your setup code here, to run once:
  pinMode(data_pin, OUTPUT);
  pinMode(blank_pin, OUTPUT);
  pinMode(latch_pin, OUTPUT);
  pinMode(clock_pin, OUTPUT);
  pinMode(clear_pin, OUTPUT);

  digitalWrite(blank_pin, LOW);
  digitalWrite(clear_pin, HIGH);
  digitalWrite(data_pin, LOW);
  digitalWrite(latch_pin, LOW);
  digitalWrite(clock_pin, LOW);
}

void pulse_pin(int pin){
  digitalWrite(pin, HIGH);
  delayMicroseconds(20);
  digitalWrite(pin, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  pulse_pin(clear_pin);

  digitalWrite(data_pin, HIGH);
  pulse_pin(clock_pin);
  digitalWrite(data_pin, LOW);

  for (i = 0; i < count; i++){
    pulse_pin(clock_pin);
  }

  pulse_pin(latch_pin);

  count = (count + 1) % 8;

  delay(500);

}
