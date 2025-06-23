#ifndef FINGERPRINT_MANAGER_H
#define FINGERPRINT_MANAGER_H

#include <Adafruit_Fingerprint.h>

class FingerprintManager {
public:
    FingerprintManager(HardwareSerial& serial);
    bool begin();
    int findFinger();
    bool enrollFinger(int id);
    bool deleteFinger(int id);

private:
    Adafruit_Fingerprint _finger;
    uint8_t getFingerprintEnroll(int id);
};

#endif 
