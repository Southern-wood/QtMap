#include "Login.h"
#include <fstream>
#include <iostream>

bool LoginModule::authenticateUser(const std::string& username, const std::string& password) {
  std::ifstream file("E:/C++/map/user.txt");

  std::string storedUsername, storedPassword;
  file >> storedUsername >> storedPassword;
  file.close();

  if (storedUsername == username && storedPassword == password) {
    return true;
  }
  return false;
}




