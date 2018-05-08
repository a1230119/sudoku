#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sudoku.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool solve(Sudoku question, Sudoku & answer);
    void changeNum(std::vector<int>& array);
    void changeRowCol(std::vector<int>& array);
    std::vector<int> randIndex();

private slots:
    void on_pushButton1_clicked();

    void on_pushButton2_clicked();

    void on_pushButton3_clicked();

    void on_pushButton4_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
