#ifndef SERIAL_UI_MANAGER_H
#define SERIAL_UI_MANAGER_H

#include <Arduino.h>

class SerialUIManager {
public:
    void showMenu();
    void showMessage(const String& message, bool newLine = true);
    int promptForId();
    String promptForString(const char* prompt);
};

#endif 
