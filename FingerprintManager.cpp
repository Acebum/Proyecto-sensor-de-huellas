#include "FingerprintManager.h"

FingerprintManager::FingerprintManager(HardwareSerial& serial) : _finger(&serial) {}

bool FingerprintManager::begin() {
    return _finger.verifyPassword();
}

int FingerprintManager::findFinger() {
    if (_finger.getImage() != FINGERPRINT_OK) return -1;
    if (_finger.image2Tz() != FINGERPRINT_OK) return -1;
    if (_finger.fingerSearch() != FINGERPRINT_OK) return -1;
    
    return _finger.fingerID;
}

bool FingerprintManager::deleteFinger(int id) {
    return _finger.deleteModel(id) == FINGERPRINT_OK;
}

bool FingerprintManager::enrollFinger(int id) {
    Serial.println("\n?? Coloca un dedo para registrar...");
    while (_finger.getImage() != FINGERPRINT_OK);
    if (_finger.image2Tz(1) != FINGERPRINT_OK) {
        Serial.println("Error procesando imagen 1");
        return false;
    }
    
    Serial.println("? Retira el dedo...");
    delay(2000);
    while (_finger.getImage() != FINGERPRINT_NOFINGER);

    Serial.println("?? Coloca el mismo dedo nuevamente...");
    while (_finger.getImage() != FINGERPRINT_OK);
    if (_finger.image2Tz(2) != FINGERPRINT_OK) {
        Serial.println("Error procesando imagen 2");
        return false;
    }

    Serial.println("Creando modelo...");
    if (_finger.createModel() != FINGERPRINT_OK) {
        Serial.println("Error al crear modelo");
        return false;
    }
    
    Serial.print("Guardando modelo en ID: "); Serial.println(id);
    if (_finger.storeModel(id) != FINGERPRINT_OK) {
        Serial.println("Error al guardar modelo");
        return false;
    }

    return true;
}
