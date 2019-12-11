int pinRelay = 36;

void setup() {
  // put your setup code here, to run once:
  pinMode(pinRelay,OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(pinRelay, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(pinRelay, LOW);
  pinMode(pinRelay,OUTPUT);
  delay(2000);
}

/*
  for (int brightness = 0; brightness < 255; brightness+=5) {
      analogWrite(2, brightness);
      delay(50);
  }

  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
  for (int brightness = 255; brightness > 0; brightness-=5) {
      analogWrite(2, brightness);
      delay(50);
  }*/
