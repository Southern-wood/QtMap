#ifndef INPUT_H
#define INPUT_H

#include <QDialog>
#include <QList>
#include <QString>

namespace Ui {
class input;
}

class input : public QDialog
{
    Q_OBJECT

public:
    explicit input(QWidget *parent = nullptr);
    ~input();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::input *ui;
    QString text;

    friend class MainWindow;
};

#endif // INPUT_H
