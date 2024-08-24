#include <Wire.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
// Buffer per memorizzare la stringa ricevuta
String receivedString = "";

void setup() {
  // Inizializza la comunicazione seriale per il monitor seriale
  Serial.begin(9600);
  lcd.begin(16,2);
  // Inizializza la comunicazione I2C come slave con indirizzo 8
  Wire.begin(8); 
  Wire.onReceive(receiveEvent);

  // Messaggio di avvio
  Serial.println("In attesa di dati I2C...");
  lcd.print("attesa dati");
}

void loop() {
  // Il loop rimane vuoto perché la ricezione dei dati è gestita dalla funzione receiveEvent()
}

// Funzione chiamata quando lo slave riceve dati
void receiveEvent(int howMany) {
  lcd.clear();
  receivedString = "";  // Resetta la stringa ricevuta

  // Leggi tutti i dati disponibili
  while (Wire.available()) {
    char c = Wire.read();
    receivedString += c;  // Costruisci la stringa
  }

  // Mostra la stringa ricevuta nel monitor seriale
  Serial.println("Dati ricevuti: " + receivedString);
  lcd.print(receivedString);
}
