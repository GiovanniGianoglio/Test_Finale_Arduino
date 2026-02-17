const int trigPin = 12;
const int echoPin = 11;
const int ledPin = 10; // Pin PWM per modulare la luminosità

unsigned long ultimoTempo = 0; // Per gestire la stampa ogni secondo

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // 1. Misurazione della distanza
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long durata = pulseIn(echoPin, HIGH);  // Misurazione del tempo di ritorno dell'eco e conversione in mm
  float distanza = (durata * 0.343) / 2; // Misurazione del tempo di ritorno dell'eco e conversione in mm

  // 2. Logica del LED
  int luminosita;

  if (distanza >= 500) {
    // Caso 1: Più lontano di 500mm -> Piena potenza
    luminosita = 255; 
  } 
  else if (distanza <= 100) {
    // Caso 2: Più vicino di 100mm -> Spento
    luminosita = 0;
  } 
  else {
    // Caso 3: Tra 100 e 500mm -> Proporzionale
    // Mappiamo la distanza (100-500) sulla luminosità PWM (0-255)
    luminosita = map(distanza, 100, 500, 0, 255);
  }

  analogWrite(ledPin, luminosita);

  // 3. Stampa su Serial Monitor ogni 1000ms (1 secondo)
  if (millis() - ultimoTempo >= 1000) {
    Serial.print("Distanza: ");
    Serial.print(distanza);
    Serial.print(" mm | Intensità LED: ");
    Serial.println(luminosita);
    ultimoTempo = millis();
  }
}
