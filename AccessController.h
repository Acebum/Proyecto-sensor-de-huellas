#ifndef ACCESS_CONTROLLER_H
#define ACCESS_CONTROLLER_H

#include <mutex>
#include <thread>
#include "FingerprintManager.h"
#include "IUserService.h"
#include "SerialUIManager.h"

class AccessController {
public:
    AccessController(FingerprintManager& fingerManager, IUserService& userService, SerialUIManager& uiManager, int relePin);
    void begin();
    void run();

private:
    void fingerScannerTask();
    void serialCommandTask();
    
    void processFoundFinger(int fingerId);
    void handleRegistration();

    FingerprintManager& _fingerManager;
    IUserService&       _userService;
    SerialUIManager&    _uiManager;
    
    int _relePin;
    std::mutex _mtx;
};

#endif 
