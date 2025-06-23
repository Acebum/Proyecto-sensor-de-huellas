#include "AccessController.h"

AccessController::AccessController(FingerprintManager& fingerManager, IUserService& userService, SerialUIManager& uiManager, int relePin)
    : _fingerManager(fingerManager), _userService(userService), _uiManager(uiManager), _relePin(relePin) {}

void AccessController::begin() {
    pinMode(_relePin, OUTPUT);
    digitalWrite(_relePin, LOW);
    _uiManager.showMessage("Sistema de Control de Acceso Inicializado.");
}

void AccessController::run() {
    _uiManager.showMenu();
    std::thread scannerThread(&AccessController::fingerScannerTask, this);
    std::thread commandThread(&AccessController::serialCommandTask, this);
    
    scannerThread.detach();
    commandThread.detach();
}

void AccessController::fingerScannerTask() {
    while (true) {
        int fingerId = _fingerManager.findFinger();
        if (fingerId != -1) {
            std::lock_guard<std::mutex> lock(_mtx);
            processFoundFinger(fingerId);
            _uiManager.showMenu();
        }
        delay(200);
    }
}

void AccessController::serialCommandTask() {
    while (true) {
        if (Serial.available() > 0) {
            char option = Serial.read();
            if (option == '1') {
                std::lock_guard<std::mutex> lock(_mtx);
                handleRegistration();
                _uiManager.showMenu();
            }
        }
        delay(100);
    }
}

void AccessController::processFoundFinger(int fingerId) {
    _uiManager.showMessage("\n?? Huella reconocida. ID: " + String(fingerId));
    if (_userService.isUserValid(fingerId)) {
        String userName = _userService.getUserName(fingerId);
        _uiManager.showMessage("? Acceso Concedido.");
        _uiManager.showMessage("?? " + userName);
        _userService.logAccess(fingerId, userName);

        digitalWrite(_relePin, HIGH);
        delay(5000);
        digitalWrite(_relePin, LOW);
        _uiManager.showMessage("?? Puerta cerrada.");

    } else {
        _uiManager.showMessage("? Acceso Denegado. Usuario no en BBDD.");
        _uiManager.showMessage("??? Eliminando huella no autorizada del sensor...");
        if (_fingerManager.deleteFinger(fingerId)) {
            _uiManager.showMessage("Huella eliminada con �xito.");
        }
    }
    delay(2000);
}

void AccessController::handleRegistration() {
    _uiManager.showMessage("\n--- Proceso de Registro ---");
    int newId = _uiManager.promptForId();
    if (newId < 1 || newId > 254) {
        _uiManager.showMessage("ID inv�lido. Abortando.");
        return;
    }
    
    String name = _uiManager.promptForString("Ingrese el nombre:");
    String semester = _uiManager.promptForString("Ingrese el semestre:");
    
    if (_fingerManager.enrollFinger(newId)) {
        _uiManager.showMessage("? Huella guardada en el sensor.");
        if (_userService.registerUser(newId, name, semester)) {
            _uiManager.showMessage("? Usuario registrado en la base de datos.");
        } else {
            _uiManager.showMessage("? Error al registrar en la base de datos. Deshaciendo...");
            _fingerManager.deleteFinger(newId);
        }
    } else {
        _uiManager.showMessage("? Error al guardar la huella.");
    }
}
