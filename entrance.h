#ifndef ENTRANCE_H
#define ENTRANCE_H

#include <string>
#include <QWidget>
#include <QDialog>

namespace Ui {
class entrance;
}

class entrance : public QDialog
{
    Q_OBJECT

public:
    explicit entrance(QDialog *parent = nullptr);
    static bool authenticateUser(const std::string& username, const std::string& password, bool root);
    int status();
    ~entrance();

private slots:
    void on_root_clicked();
    void on_user_clicked();


private:
    Ui::entrance *ui;
    std::string username, password;
    int authenticated = 0;
};

#endif // ENTRANCE_H
