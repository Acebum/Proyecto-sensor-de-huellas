#include "FirebaseService.h"
#include <time.h>

FirebaseService::FirebaseService(const char* host, const char* auth)
    : _host(host), _auth_token(auth) {}

void FirebaseService::begin() {
    _config.database_url = _host.c_str(); 
    _config.signer.tokens.legacy_token = _auth_token.c_str(); 
    Firebase.begin(&_config, &_auth);
    Firebase.reconnectWiFi(true);
}

bool FirebaseService::isUserValid(int userId) {
    String path = "/personas/usuario_" + String(userId);
    return Firebase.getString(_fbdo, path + "/nombre");
}

String FirebaseService::getUserName(int userId) {
    String path = "/personas/usuario_" + String(userId) + "/nombre";
    if (Firebase.getString(_fbdo, path)) {
        return _fbdo.stringData();
    }
    return "Desconocido";
}

bool FirebaseService::registerUser(int userId, const String& name, const String& semester) {
    String path = "/personas/usuario_" + String(userId);
    FirebaseJson json;
    json.set("nombre", name);
    json.set("semestre", semester);
    json.set("idHuella", userId);
    json.set("ultima_modificacion", getFormattedTimestamp());
    return Firebase.setJSON(_fbdo, path, json);
}

void FirebaseService::logAccess(int userId, const String& name) {
    time_t timestamp = time(nullptr);
    String path = "/registros_acceso/" + String(timestamp);
    FirebaseJson json;
    json.set("id_huella_leida", userId);
    json.set("nombre", name);
    json.set("timestamp", (int)timestamp);
    json.set("fecha_hora", getFormattedTimestamp());
    Firebase.setJSON(_fbdo, path, json);
}

String FirebaseService::getFormattedTimestamp() {
    time_t now = time(nullptr);
    struct tm* t = localtime(&now);
    if(t->tm_year < 100) return "NTP no sincronizado"; 
    char buffer[25];
    sprintf(buffer, "%02d/%02d/%04d %02d:%02d:%02d",
            t->tm_mday, t->tm_mon + 1, t->tm_year + 1900,
            t->tm_hour, t->tm_min, t->tm_sec);
    return String(buffer);
}
