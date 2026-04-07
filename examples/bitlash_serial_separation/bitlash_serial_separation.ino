//
// Bitlash Serial Separation Example (ESP32)
//
// Bitlash has no serial involvement. You control serial yourself.
// Feed commands via doCommand(). Capture output via setOutputHandler().
//

#include "bitlash.h"

// Redirect all Bitlash output to Serial
void bitlashOutput(byte c) {
    Serial.write(c);
}

void setup() {
    Serial.begin(115200);

    // Bitlash does NOT touch Serial — beginSerial is a no-op on ESP32
    initBitlash(0);

    // Route Bitlash output (print, banner, errors) to your Serial
    setOutputHandler(bitlashOutput);

    Serial.println("[APP] Bitlash is decoupled from serial.");
    Serial.println("[APP] Type a Bitlash command:");
}

void loop() {
    // Run background tasks only — serialAvailable() returns 0 on ESP32
    runBitlash();

    // You manage serial yourself, then pass commands to Bitlash
    if (Serial.available()) {
        String cmd = Serial.readStringUntil('\n');
        cmd.trim();
        if (cmd.length() > 0) {
            char buf[141];
            cmd.toCharArray(buf, sizeof(buf));
            doCommand(buf);
        }
    }
}
