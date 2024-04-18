#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

#include <DHT.h>
#include <DHT_U.h>

// PINES DIGITALES
int LED_ROJO = 3;
int PIN_DHT11 = 2;

// PINES ANALÓGICOS
const int PIN_FOTOSENSOR = A0;
//#define PIN_FOTOSENSOR A0

// LCD
LiquidCrystal_I2C lcd (0x27, 2, 1, 0, 4, 5, 6, 7);

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
  lcd.setBacklightPin(3, POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.begin(16, 2);
  lcd.clear();
}

void loop() {  
  // DHT11
  TEMPERATURA = dht.readTemperature();
  HUMEDAD = dht.readHumidity();
  Serial.print("T");
  Serial.print(TEMPERATURA);
  Serial.print(" H");
  Serial.print(HUMEDAD);
  // LCD
  lcd.setCursor(0, 1);
  lcd.print("T:");
  lcd.print(TEMPERATURA);
  lcd.print("C");
  lcd.print(" H:");
  lcd.print(HUMEDAD);
  lcd.print("%");

  // FOTORESISTENCIA
  LIGHT = analogRead(PIN_FOTOSENSOR);
  Serial.print( " L");
  Serial.println(LIGHT);  
  if(LIGHT > 200) {
    digitalWrite(LED_ROJO, HIGH);
    // LCD
    lcd.setCursor(0, 0);
    lcd.print("DARK  MODE");
  } else {
    digitalWrite(LED_ROJO, LOW);
    // LCD
    lcd.setCursor(0, 0);
    lcd.print("LIGHT MODE");
  }
  
  delay(500);
}
