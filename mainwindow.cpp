#include "mainwindow.h"
#include <QTileRules>
#include <QLabel>
#include <QImage>
// #include <Python.h>
#include <QProcess>
#include <QDialog>
#include <QTextEdit>
#include <windows.h>
#include "./ui_mainwindow.h"
#include "input.h"
#include "ui_input.h"
#include <iostream>
#include <string>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("地图网络的图分析");
    g = new Graph(ui->logInfo, ui->listWidget);
}

void MainWindow::displayOption(int authenticated) {
    if (authenticated == 2) {
        ui->addCity->hide();
        ui->removeCity->hide();
        ui->addroad->hide();
        ui->removeRoad->hide();
    }
    g->init();
    QStringList infoList;

    foreach (const QString &info, infoList) {
        ui->listWidget->addItem(info);
    }
}

MainWindow::~MainWindow()
{
    delete g;
    delete ui;
}

void MainWindow::on_visualzation_clicked()
{
    g->output();

    // 创建 QProcess 对象
    QProcess process;

    // 配置命令和参数
    QString program = "py";
    QStringList arguments;
    arguments << "E:\\C++\\QtMap\\map\\network.py";

    //设置进程选项，隐藏命令行窗口
    process.setCreateProcessArgumentsModifier([](QProcess::CreateProcessArguments *args) {
        args->flags |= CREATE_NO_WINDOW;
        args->startupInfo->dwFlags &= ~STARTF_USESTDHANDLES;
    });

    // 启动进程
    process.start(program, arguments);

    // 等待进程结束
    process.waitForFinished(-1);

    QPixmap p;
    p.load("E:\\C++\\QtMap\\map\\homo.png");
    QLabel *l = new QLabel();
    l->setPixmap(p);
    l->show();
}


void MainWindow::on_matrix_clicked()
{
    g->printAdjacencyMatrix();
    ui->logInfo->addItem("[成功] ： 邻接矩阵查询成功");
    ui->logInfo->scrollToBottom();
}


void MainWindow::on_list_clicked()
{
    g->printAdjacencyList();
    ui->logInfo->addItem("[成功] ： 邻接表查询成功");
    ui->logInfo->scrollToBottom();
}

// 对数据类型和参数的检验
void MainWindow::on_neighbour_clicked() {
    input * i = new input();
    i->ui->label->setText("请输入要查询的城市：");
    if (i->exec()) {
        QStringList s = (i->text).split(" ");
        // 如果用户传入了空字符串，则需要额外矫正
        int diff = (s[0].toStdString() == "" ? 1 : 0);
        if (s.size() - diff != 1) {
            ui->logInfo->addItem(QString::fromStdString("[错误] ： 参数个数不匹配，期望参数 1 个，实际参数 " + std::to_string(s.size() - diff) + " 个"));
        } else {
            g->printNeighbours(s[0].toStdString());
        }
    }
    ui->logInfo->scrollToBottom();
}


void MainWindow::on_dijistra_clicked()
{
    const int INF = 1e9;
    input *i = new input();
    i->ui->label->setText("请输入起始城市和终点城市");
    if (i->exec()) {
        QStringList s = (i->text).split(" ");
        int diff = (s[0].toStdString() == "" ? 1 : 0);
        if (s.size() - diff != 2) {
            ui->logInfo->addItem(QString::fromStdString("[错误] ： 参数个数不匹配，期望参数 2 个，实际参数 " + std::to_string(s.size() - diff) + " 个"));
        } else {
            ui->listWidget->clear();
            auto info = g->dijkstraShortestPath(s[0].toStdString(), s[1].toStdString());
            if (info.path.empty()) {
                if (!info.totalDistance) {
                    QString row = QString::fromStdString(s[0].toStdString() + "无法到达" + s[1].toStdString());
                    ui->logInfo->addItem("[消息] ： 导航无法进行");
                    ui->listWidget->addItem(row);
                }
                ui->logInfo->scrollToBottom();
                return;
            }
            ui->listWidget->addItem(QString::fromStdString("起始城市 ： " + info.path.front()));
            int n = info.path.size();
            for (int i = 0; i < n - 2; i++) {
                ui->listWidget->addItem(QString::fromStdString("经过 " + info.path[i + 1] + "  路程 ： " + std::to_string(info.distances[i])));
            }
            ui->listWidget->addItem(QString::fromStdString("到达 " + info.path.back() + "  路程 ： " + std::to_string(info.distances[n - 2])));
            ui->listWidget->addItem(QString::fromStdString("总路程 ： " + std::to_string(info.totalDistance)));
            ui->logInfo->addItem("[成功] ： 城市导航结束");
        }
    }
    ui->logInfo->scrollToBottom();
}


void MainWindow::on_addCity_clicked()
{
    input * i = new input();
    i->ui->label->setText("请输入要添加的城市：");
    if (i->exec()) {
        QStringList s = (i->text).split(" ");
        int diff = (s[0].toStdString() == "" ? 1 : 0);
        if (s.size() - diff != 1) {
            ui->logInfo->addItem(QString::fromStdString("[错误] ： 参数个数不匹配，期望参数 1 个，实际参数 " + std::to_string(s.size() - diff) + " 个"));
        } else {
            g->addCity(s[0].toStdString());
        }
    }
    ui->logInfo->scrollToBottom();
}


void MainWindow::on_removeCity_clicked()
{
    input * i = new input();
    i->ui->label->setText("请输入要删除的城市：");
    if (i->exec()) {
        QStringList s = (i->text).split(" ");
        int diff = (s[0].toStdString() == "" ? 1 : 0);
        if (s.size() - diff != 1) {
            ui->logInfo->addItem(QString::fromStdString("[错误] ： 参数个数不匹配，期望参数 1 个，实际参数 " + std::to_string(s.size() - diff) + " 个"));
        } else {
            g->removeCity(s[0].toStdString());
        }
    }
    ui->logInfo->scrollToBottom();
}


void MainWindow::on_addroad_clicked()
{
    input * i = new input();
    i->ui->label->setText("请输入道路两端的城市及道路长度：");
    if (i->exec()) {
        QStringList s = (i->text).split(" ");
        int diff = (s[0].toStdString() == "" ? 1 : 0);
        if (s.size() - diff != 3) {
            ui->logInfo->addItem(QString::fromStdString("[错误] ： 参数个数不匹配，期望参数 3 个，实际参数 " + std::to_string(s.size() - diff) + " 个"));
        } else {
            g->addRoad(s[0].toStdString(), s[1].toStdString(), s[2].toInt());
        }
    }
    ui->logInfo->scrollToBottom();
}


void MainWindow::on_removeRoad_clicked()
{
    input * i = new input();
    i->ui->label->setText("请输入需要删除道路的两个城市：");
    if (i->exec()) {
        QStringList s = (i->text).split(" ");
        int diff = (s[0].toStdString() == "" ? 1 : 0);
        if (s.size() - diff != 2) {
            ui->logInfo->addItem(QString::fromStdString("[错误] ： 参数个数不匹配，期望参数 2 个，实际参数 " + std::to_string(s.size() - diff) + " 个"));
        } else {
            g->removeRoad(s[0].toStdString(), s[1].toStdString());
        }
    }
    ui->logInfo->scrollToBottom();
}

