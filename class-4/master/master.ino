#include <Wire.h>

byte MASTER_ADDRESS = 0x05;

void setup() {
    Wire.begin(MASTER_ADDRESS);
    Serial.begin(9600);
}

void loop() {
    byte addr = 0x00;
    bool ya_heard;

    for(addr=0x00; addr<=0xFF; addr++) {
        Wire.beginTransmission(addr);
        Wire.write("YO!");
        Wire.endTransmission();

        Wire.requestFrom(addr, 0x01);
        delay(50);

        while (Wire.available()) {
            char c = Wire.read();
            Serial.print(c);
            ya_heard = true;
        }
        if (ya_heard == true) {
            Serial.print("Found slave at ");
            Serial.println(addr, HEX);
        }
        ya_heard = false;

        if (addr == 0xFF) {
            delay(300);
        }

    }
}
