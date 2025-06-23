#ifndef FIREBASE_SERVICE_H
#define FIREBASE_SERVICE_H

#include "IUserService.h"
#include <FirebaseESP32.h>

class FirebaseService : public IUserService {
public:
    FirebaseService(const char* host, const char* auth);
    void begin() override;
    bool isUserValid(int userId) override;
    String getUserName(int userId) override;
    bool registerUser(int userId, const String& name, const String& semester) override;
    void logAccess(int userId, const String& name) override;

private:
    FirebaseData _fbdo;
    FirebaseAuth _auth;
    FirebaseConfig _config;
    String _host;
    String _auth_token;
    String getFormattedTimestamp();
};

#endif 
