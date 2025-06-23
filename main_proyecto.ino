#include <WiFi.h>
#include <time.h>
#include "AccessController.h"
#include "FirebaseService.h"
#include "FingerprintManager.h"
#include "SerialUIManager.h"

#define WIFI_SSID "APONTE MENDEZ"
#define WIFI_PASSWORD "FAMILIAAPOMEN"
#define FIREBASE_HOST "https://registro-mecacueva-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "k7J3gBmKzVMzTwshHrVGyPvsOXvQvuIlG8ksI9D5"

#define PIN_RELE 12
#define PIN_FP_RX 16 
#define PIN_FP_TX 17 


HardwareSerial fingerSerial(2); 

FingerprintManager fingerprintManager(fingerSerial);
FirebaseService firebaseService(FIREBASE_HOST, FIREBASE_AUTH);
SerialUIManager uiManager;

AccessController accessController(fingerprintManager, firebaseService, uiManager, PIN_RELE);

void setup() {
    Serial.begin(115200);
    fingerSerial.begin(57600, SERIAL_8N1, PIN_FP_TX, PIN_FP_RX);

    
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Conectando a WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\n WiFi conectado");

    
    configTime(-4 * 3600, 0, "pool.ntp.org");
    
 
    firebaseService.begin();
    if (!fingerprintManager.begin()) {
        Serial.println(" No se encontró el sensor de huellas. Verifique conexiones.");
        while (true) delay(1000); 
    }
    
    accessController.begin();

    accessController.run();
}

void loop() {

    vTaskDelay(pdMS_TO_TICKS(1000)); 
}