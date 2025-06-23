#ifndef IUSER_SERVICE_H
#define IUSER_SERVICE_H

#include <Arduino.h>

class IUserService {
public:
    virtual ~IUserService() = default; 
    virtual bool isUserValid(int userId) = 0;
    virtual String getUserName(int userId) = 0;
    virtual bool registerUser(int userId, const String& name, const String& semester) = 0;
    virtual void logAccess(int userId, const String& name) = 0;
    virtual void begin() = 0; 
};

#endif 
