#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// Definizione dei pin
const int umiditaPin = A0;     // Pin analogico per il sensore di umidità del terreno
const int lucePin = A1;        // Pin analogico per la fotoresistenza
const int temperaturaEsternaPin = A2;  // Pin analogico per il sensore di temperatura esterna
const int umiditaEsternaPin = A3;      // Pin analogico per il sensore di umidità esterna
const int pompaPin = 10;      // Pin digitale per la pompa di irrigazione
const int dhtPin = 11;        // Pin digitale per il sensore DHT

// Costanti per la soglia di umidità del terreno e la luce
const int sogliaUmiditaTerreno = 30;
const int sogliaLuce = 500;

// Oggetti per il display LCD e i sensori DHT
LiquidCrystal_I2C lcd(0x27, 20, 4);
DHT dht(dhtPin, DHT11);

void setup() {
  // Inizializzazione del display LCD
  lcd.begin(20, 4);
  lcd.print("Serra Domotizzata");
  
  // Inizializzazione del sensore DHT
  dht.begin();

  // Impostazione del pin della pompa come OUTPUT
  pinMode(pompaPin, OUTPUT);
  
  // Impostazione della velocità di trasmissione della porta seriale
  Serial.begin(9600);
}

void loop() {
  // Lettura dell'umidità del terreno
  int umiditaTerreno = analogRead(umiditaPin);
  umiditaTerreno = map(umiditaTerreno, 0, 1023, 0, 100); // Mappatura del valore letto in un range da 0 a 100
  
  // Lettura della luce
  int luce = analogRead(lucePin);
  
  // Lettura della temperatura esterna
  int temperaturaEsterna = analogRead(temperaturaEsternaPin);
  temperaturaEsterna = map(temperaturaEsterna, 0, 1023, -40, 125); // Mappatura del valore letto in un range da -40°C a 125°C
  
  // Lettura dell'umidità esterna
  int umiditaEsterna = analogRead(umiditaEsternaPin);
  umiditaEsterna = map(umiditaEsterna, 0, 1023, 0, 100); // Mappatura del valore letto in un range da 0 a 100
  
  // Lettura della temperatura e umidità interna
  float temperaturaInterna = dht.readTemperature();
  float umiditaInterna = dht.readHumidity();
  
  // Accensione/spegnimento della pompa in base all'umidità del terreno
  if (umiditaTerreno < sogliaUmiditaTerreno) {
    digitalWrite(pompaPin, HIGH); // Accendi la pompa
  } else {
    digitalWrite(pompaPin, LOW);  // Spegni la pompa
  }
  
  // Aggiornamento del display LCD
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
  
  // Trasmissione dei dati attraverso la porta seriale
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
  
  // Attendi 1 minuto prima di effettuare una nuova lettura
  delay(60000);
}
