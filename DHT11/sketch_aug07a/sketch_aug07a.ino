#include <DHT.h>
#include <DHT_U.h>

int LED_ROJO = 3;

int SENSOR = 2;
int TEMPERATURA;
int HUMEDAD;

DHT dht(SENSOR, DHT11);

void setup() {
  Serial.begin(9600);
  // DHT11
  dht.begin();
  // LED
  pinMode(3, OUTPUT);
}

void loop() {
  TEMPERATURA = dht.readTemperature();
  HUMEDAD = dht.readHumidity();
  Serial.print("T");
  Serial.print(TEMPERATURA);
  Serial.print(" H");
  Serial.println(HUMEDAD);
  if(HUMEDAD > 60) {
    digitalWrite(3, HIGH);
  } else {
    digitalWrite(3, LOW);
  }
  delay(500);
}
