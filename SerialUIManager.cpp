#include "SerialUIManager.h"

void SerialUIManager::showMenu() {
    Serial.println("\n===================================");
    Serial.println("?? MEN� DE CONTROL DE ACCESO");
    Serial.println("===================================");
    Serial.println("1. Registrar nueva huella");
    Serial.print("? Esperando huella o comando: ");
}

void SerialUIManager::showMessage(const String& message, bool newLine) {
    if (newLine) {
        Serial.println(message);
    } else {
        Serial.print(message);
    }
}

int SerialUIManager::promptForId() {
    showMessage("\n?? Escribe el ID para el registro (1-254):", false);
    while (Serial.available() == 0) { delay(100); }
    String input = Serial.readStringUntil('\n');
    return input.toInt();
}

String SerialUIManager::promptForString(const char* prompt) {
    showMessage(prompt);
    while (Serial.available() == 0) { delay(100); }
    String input = Serial.readStringUntil('\n');
    input.trim();
    return input;
}
