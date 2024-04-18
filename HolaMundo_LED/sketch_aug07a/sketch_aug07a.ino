void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);  // pin 13 como salida
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(13, HIGH); // pin 13 a nivel alto (1)
  delay(3000);            // demora de 1 seg.
  digitalWrite(13, LOW); // pin 13 a nivel alto (0)
  delay(1000);            // demora de 1 seg.
}
