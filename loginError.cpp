#include "loginError.h"
#include "ui_loginError.h"

loginError::loginError(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::loginError)
{
    ui->setupUi(this);
}

bool loginError::Error() {
    ui->textBrowser->hide();
    this->setGeometry(700, 400, 200, 48);
    this->exec();
    return true;
}

loginError::~loginError()
{
    delete ui;
}
