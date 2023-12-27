#include "mainwindow.h"
#include "entrance.h"
#include "loginError.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    entrance login;
    login.setWindowTitle("地图网络图分析系统");
    loginError log;
    log.setWindowTitle("登录失败");
    int killed = 0;
    do {
        killed = !login.exec();
        if (killed) break;
    } while (!login.status() && log.Error());
    if (killed) return 0;

    MainWindow w;
    w.displayOption(login.status());
    w.show();
    a.exec();
    return 0;
}
