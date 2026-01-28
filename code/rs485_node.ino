#include <SoftwareSerial.h>

#define DE_RE 2
#define BUTON A0
#define LED 13

SoftwareSerial rs485(10, 11);

const char KART_ID = 'A';  // Diger arduino için:  ID = 'B'

void setup() {
  pinMode(DE_RE, OUTPUT);
  pinMode(BUTON, INPUT);
  pinMode(LED, OUTPUT);
  digitalWrite(DE_RE, LOW);

  rs485.begin(9600);
}

void loop() {
  if (digitalRead(BUTON) == HIGH) {
    digitalWrite(DE_RE, HIGH);
    delay(5);

    digitalWrite(LED, LOW);
    rs485.print(KART_ID);
    rs485.println(":LED_AC");

    delay(5);
    digitalWrite(DE_RE, LOW);
    delay(300);
  }

  if (rs485.available()) {
    String msg = rs485.readStringUntil('\n');

    if (msg.indexOf(":LED_AC") > 0) {
      if (msg.charAt(0) != KART_ID) {
        digitalWrite(LED, HIGH);
      }
    }
  }
}
