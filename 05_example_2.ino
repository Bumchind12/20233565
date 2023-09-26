#define LED_PIN 7

#define LED_BLINKS 5

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_PIN, 0);
  delay(1000);
  
  for (int i = 0; i <= LED_BLINKS; i++) {
    digitalWrite(LED_PIN, 0);
    delay(100);
    digitalWrite(LED_PIN, 1);
    delay(100);
  }
  while(1) {
    digitalWrite(LED_PIN, 1);
  }
}
