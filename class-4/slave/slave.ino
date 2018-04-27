#include <Wire.h>

byte SLAVE_ADDRESS = 0x0A;
byte MASTER_ADDRESS = 0x05;

void setup() {
    Wire.begin(SLAVE_ADDRESS);
    Wire.onReceive(ack);

    Serial.begin(9600);

    pinMode(6, OUTPUT);
    digitalWrite(6, LOW);
}

void loop() {
    delay(100);
}

void ack(int howMany) {
    while (1 <= Wire.available()) {
        char c = Wire.read();
        Serial.print(c);
    }
    set_pin();
    
    Wire.write(SLAVE_ADDRESS);
}

void set_pin(void) {

    Serial.println(digitalRead(6));
    Serial.println(digitalRead(6)==HIGH);
    if (digitalRead(6) == HIGH) {
        digitalWrite(6, LOW);
    } else {
        digitalWrite(6, HIGH);
    }
}
