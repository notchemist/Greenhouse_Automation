#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

const int umiditaPin = A0;
const int lucePin = A1;
const int temperaturaEsternaPin = A2;
const int umiditaEsternaPin = A3;
const int pompaPin = 10;
const int dhtPin = 11;

const int sogliaUmiditaTerreno = 30;
const int sogliaLuce = 500;

LiquidCrystal_I2C lcd(0x27, 20, 4);
DHT dht(dhtPin, DHT11);

void setup() {
  lcd.begin(20, 4);
  lcd.print("Serra Domotizzata");
  
  dht.begin();

  pinMode(pompaPin, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  int umiditaTerreno = analogRead(umiditaPin);
  umiditaTerreno = map(umiditaTerreno, 0, 1023, 0, 100);
  
  int luce = analogRead(lucePin);
  
  int temperaturaEsterna = analogRead(temperaturaEsternaPin);
  temperaturaEsterna = map(temperaturaEsterna, 0, 1023, -40, 125);
  
  int umiditaEsterna = analogRead(umiditaEsternaPin);
  umiditaEsterna = map(umiditaEsterna, 0, 1023, 0, 100);
  
  float temperaturaInterna = dht.readTemperature();
  float umiditaInterna = dht.readHumidity();
  
  if (umiditaTerreno < sogliaUmiditaTerreno) {
    digitalWrite(pompaPin, HIGH);
  } else {
    digitalWrite(pompaPin, LOW);
  }
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Umidita Terreno: ");
  lcd.print(umiditaTerreno);
  lcd.print("%");
  
  lcd.setCursor(0, 1);
  lcd.print("Luce: ");
  lcd.print(luce);
  
  lcd.setCursor(0, 2);
  lcd.print("Temp Esterna: ");
  lcd.print(temperaturaEsterna);
  lcd.print("C");
  
  lcd.setCursor(0, 3);
  lcd.print("Umid Esterna: ");
  lcd.print(umiditaEsterna);
  lcd.print("%");
  
  Serial.print("Umidita Terreno: ");
  Serial.print(umiditaTerreno);
  Serial.print("%, Luce: ");
  Serial.print(luce);
  Serial.print(", Temp Esterna: ");
  Serial.print(temperaturaEsterna);
  Serial.print("C, Umid Esterna: ");
  Serial.print(umiditaEsterna);
  Serial.print("%, Temp Interna: ");
  Serial.print(temperaturaInterna);
  Serial.print("C, Umid Interna: ");
  Serial.print(umiditaInterna);
  Serial.println("%");
  
  delay(60000);
}
