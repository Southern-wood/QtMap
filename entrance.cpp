#include "entrance.h"
#include "ui_entrance.h"
#include <fstream>
#include <iostream>
#include <string>


entrance::entrance(QDialog *parent) : QDialog(parent), ui(new Ui::entrance) {
  ui->setupUi(this);
}

int entrance::status() { return authenticated; }

entrance::~entrance() { delete ui; }

bool entrance::authenticateUser(const std::string &username,
                                const std::string &password, bool root) {
  std::ifstream file;
  if (root) {
    file.open("E:/C++/Qtmap/map/admin.txt");
  } else {
    file.open("E:/C++/Qtmap/map/user.txt");
  }

  std::string storedUsername, storedPassword;
  while (file >> storedUsername >> storedPassword) {
    if (storedUsername == username && storedPassword == password) {
      return true;
    }
  }
  file.close();
  return false;
}

void entrance::on_root_clicked() {
  username = ui->usernameText->toPlainText().toStdString();
  password = ui->passwordText->toPlainText().toStdString();
  if (authenticateUser(username, password, true)) {
    authenticated = 1;
  }
  ui->passwordText->clear();
  this->done(true);
}

void entrance::on_user_clicked() {
  username = ui->usernameText->toPlainText().toStdString();
  password = ui->passwordText->toPlainText().toStdString();
  if (authenticateUser(username, password, false)) {
    authenticated = 2;
  }
  ui->passwordText->clear();
  this->done(true);
}
