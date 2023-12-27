#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Qwidget>
#include "Graph.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void displayOption(int auther);
    ~MainWindow();

private slots:
    void on_visualzation_clicked();

    void on_matrix_clicked();

    void on_list_clicked();

    void on_neighbour_clicked();

    void on_dijistra_clicked();

    void on_addCity_clicked();

    void on_removeCity_clicked();

    void on_addroad_clicked();

    void on_removeRoad_clicked();

private:
    Ui::MainWindow *ui;
    Graph *g;
};
#endif // MAINWINDOW_H
