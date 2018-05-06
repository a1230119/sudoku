#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sudoku.h"

#include <QHeaderView>
#include <QTableWidgetItem>
#include <vector>
#include <QString>
#include <QLabel>

using namespace std;

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
    //int ss[81]={8,0,5,3,2,0,4,1,7,2,0,3,1,7,5,8,6,9,1,9,7,6,8,4,5,0,3,3,1,9,0,5,8,6,7,4,4,2,6,0,9,1,3,5,8,5,7,8,4,3,0,1,9,2,7,5,4,9,1,3,2,0,6,6,8,2,5,4,0,9,3,1,9,3,1,8,6,2,7,0,5};
    for(int i = 0; i < 9; ++i)
    {
        for(int j = 0; j < 9; ++j)
        {
            //QString convert = QString::number(ss[i*9+j]);
            //ui->tableWidget->setItem(i, j, new QTableWidgetItem(convert));
        }
    }
    //ui->tableWidget->item(3,3)->text();

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
    vector<vector<int>> row_vector;
    vector<vector<int>> column_vector;
    vector<vector<int>> cells_vector;
    question.checknum(row_vector, column_vector, cells_vector);
    vector<int> result;
    if(firstZero == -1)//end condition
    {
        if(question.isCorrect())
        {
            answer = question;
            return true;
        }
        return false;
    }
    else
    {
        int row, col, cell;
        row = firstZero / 9;
        col = firstZero % 9;
        cell = (firstZero/27) * 3 + col / 3;
        result = question.findnum(row_vector[row], column_vector[col], cells_vector[cell]);
        for(int i = 0; i < result.size(); ++i)
        {
            question.setElement(firstZero, result.at(i));
            if(solve(question, answer))
                return true;
        }
        return false;
    }
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
    int ss[81]={8,6,5,3,2,0,4,1,7,2,4,3,1,7,5,8,6,9,1,9,7,6,8,4,5,2,3,3,1,9,2,5,8,6,7,4,4,2,6,7,9,1,3,5,8,5,7,8,4,3,6,1,9,2,7,5,4,9,1,3,2,8,6,6,8,2,5,4,7,9,3,1,9,3,1,8,6,2,7,4,5};
    Sudoku ques, ans;
    for(int i = 0; i < 81; ++i)
    {
        ques.setElement(i, ss[i]);
    }

    if(solve(ques, ans)){
        for(int i = 0; i < 9; ++i)
        {
            for(int j = 0; j < 9; ++j)
            {
                QString convert = QString::number(ss[i*9+j]);
                ui->tableWidget->setItem(i, j, new QTableWidgetItem(convert));
            }
        }
    }
    else
        ui->tableWidget->setItem(2, 3, new QTableWidgetItem("debug"));
}

void MainWindow::on_pushButton3_clicked()
{
    getkey();
}
