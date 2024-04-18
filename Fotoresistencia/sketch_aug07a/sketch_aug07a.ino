#include <DHT.h>
#include <DHT_U.h>

// PINES DIGITALES
int LED_ROJO = 3;
int PIN_DHT11 = 2;

// PINES ANALÓGICOS
//int PIN_FOTOSENSOR = 8;
const int PIN_FOTOSENSOR = A0;
#define PIN_FOTOSENSOR A0

// LCD
//LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7);

// OTRAS VARIABLES
int TEMPERATURA;
int HUMEDAD;
int PWD;
int LIGHT;

DHT dht(PIN_DHT11, DHT11);

void setup() {
  Serial.begin(9600);
  // DHT11
  dht.begin();
  // LED
  pinMode(3, OUTPUT);
  // LDR
  pinMode(PIN_FOTOSENSOR, INPUT);
  // LCD
  /*
  lcd.setBacklightPin(3, POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.begin(16, 2);
  lcd.clear();
  */
}

void loop() {
  // DHT11
  TEMPERATURA = dht.readTemperature();
  HUMEDAD = dht.readHumidity();
  Serial.print("T");
  Serial.print(TEMPERATURA);
  Serial.print(" H");
  Serial.print(HUMEDAD);

  // FOTORESISTENCIA
  LIGHT = analogRead(PIN_FOTOSENSOR);
  //LIGHT = digitalRead(PIN_FOTOSENSOR);
  Serial.print( " L");
  Serial.println(LIGHT);
  //PWD = map(LIGHT, 0, 1023, 0, 255);
  //Serial.println(PWD);
  //analogWrite(LED_ROJO, PWD);
  
   if(LIGHT > 200) {
    digitalWrite(LED_ROJO, HIGH);
  } else {
    digitalWrite(LED_ROJO, LOW);
  }
  /*
  lcd.setCursor(0, 0);
  lcd.print("Hola, han pasado");
  lcd.setCursor(0 ,1);
  lcd.print(millis() / 1000);
  lcd.print(" seg.");
  */
  delay(500);
}
