#ifndef MAP_LOGIN_MODULE_H
#define MAP_LOGIN_MODULE_H
#include <string>

class LoginModule {
public:
  static bool authenticateUser(const std::string& username, const std::string& password);
};

#endif
