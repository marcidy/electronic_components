#include <Wire.h>


byte chip = 0xE8;           // Chip address set by A0-A3 1011 0110
int out = 0;                // global to hold data read from chip
byte led_state = 0x55;      // state for LED PWM registers


// set_()
// sets register reg with byte data
byte set_(byte reg, byte data) {
    Wire.beginTransmission(chip);
    Wire.write(reg);
    Wire.write(data);
    return (Wire.endTransmission());
}


// set_()
// sets the register address only, used by read_()
byte set_(byte reg) {
    Wire.beginTransmission(chip);
    Wire.write(reg);
    return (Wire.endTransmission());
}


// read_()
// wraps reading Wire
void read_(byte reg) {
    set_(reg);

    Wire.requestFrom(chip, byte(1));
    while (Wire.available()) {
        out = Wire.read();  //should be a buffer but doesn't matter right now.
    }
}


// setup()
// Start Serial communication and initialize i2c bus
// Configure TLC59116 chip
void setup() {
    Serial.begin(9600);
    Wire.begin();

    set_(0x00, 0x00);  // Mode 1 
    set_(0x01, 0x20);  // Mode 2 group blinking
    set_(0x12, 0xFF);  // GRPPWM
    set_(0x13, 0x0F);  // GRPFREQ

    // Set LED PWM register
    set_(0x15, led_state);

    delay(200);

    // Check error registers
    Serial.println("__Errors__");
    read_(0x1D);
    Serial.print(out, HEX);
    read_(0x1E);
    Serial.println(out, HEX);
}

// loop()
//  Do nothing
void loop() {
    exit(0);
}
