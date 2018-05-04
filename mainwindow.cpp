#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sudoku.h"

#include <QHeaderView>
#include <QTableWidgetItem>
#include <vector>
#include <QString>
#include <QDebug>
#include <QLabel>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->pushButton1->setStyleSheet("QPushButton{ background-color: rgb(65, 97, 123); color: white; border-radius: 10px; border: 2px groove gray; border-style: outset; } QPushButton:hover{ background-color: white; color: rgb(65, 97, 123); } QPushButton:pressed{ background-color: rgb(91, 167, 226); border-style: inset; } ");
    ui->pushButton2->setStyleSheet("QPushButton{ background-color: rgb(65, 97, 123); color: white; border-radius: 10px; border: 2px groove gray; border-style: outset; } QPushButton:hover{ background-color: white; color: rgb(65, 97, 123); } QPushButton:pressed{ background-color: rgb(91, 167, 226); border-style: inset; } ");
    ui->pushButton3->setStyleSheet("QPushButton{ background-color: rgb(65, 97, 123); color: white; border-radius: 10px; border: 2px groove gray; border-style: outset; } QPushButton:hover{ background-color: white; color: rgb(65, 97, 123); } QPushButton:pressed{ background-color: rgb(91, 167, 226); border-style: inset; } ");
    //QTableWidgetItem * prop = new QTableWidgetItem();
    //prop->setTextAlignment(Qt::AlignRight);
    //ui->tableWidget->item(2,3)->setTextAlignment(Qt::AlignCenter);
    for(int i = 0; i < 9; ++i)
    {
        for(int j = 0; j < 9; ++j)
        {
            ui->tableWidget->setItem(i, j, new QTableWidgetItem(""));
        }
    }
    ui->tableWidget->item(3,3)->text();

    connect(ui->pushButton1, SIGNAL(clicked(bool)), this, SLOT(on_pushButton1_clicked()));
    connect(ui->pushButton2, SIGNAL(clicked(bool)), this, SLOT(on_pushButton2_clicked()));
    connect(ui->pushButton3, SIGNAL(clicked(bool)), this, SLOT(on_pushButton3_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::solve(Sudoku question, Sudoku &answer)
{
    int firstZero;
    firstZero = question.getFirstZeroIndex();
    if(firstZero == -1)//end condition
    {
        if(question.isCorrect())
        {
            answer = question;
            return true;
        }
        return false;
    }
    //else
    //{

    //}
}

void MainWindow::getkey(){
    QString str = ui->tableWidget->item(3,4)->text();
    ui->label->setText(str);
}

void MainWindow::on_pushButton2_clicked()
{
    //solve();
}

void MainWindow::on_pushButton1_clicked()
{

}

void MainWindow::on_pushButton3_clicked()
{
    getkey();
}
