#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class ToolsBox;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    ToolsBox* _box;
};

#endif // MAINWINDOW_H
