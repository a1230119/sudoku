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
    ui->pushButton4->setStyleSheet("QPushButton{ background-color: rgb(65, 97, 123); color: white; border-radius: 10px; border: 2px groove gray; border-style: outset; } QPushButton:hover{ background-color: white; color: rgb(65, 97, 123); } QPushButton:pressed{ background-color: rgb(91, 167, 226); border-style: inset; } ");
    //QTableWidgetItem * prop = new QTableWidgetItem();
    //prop->setTextAlignment(Qt::AlignRight);
    //ui->tableWidget->item(2,3)->setTextAlignment(Qt::AlignCenter);

    for(int i = 0; i < 9; ++i)//initialize
    {
        for(int j = 0; j < 9; ++j)
        {
            ui->tableWidget->setItem(i, j, new QTableWidgetItem(""));
            ui->tableWidget->item(i, j)->setTextAlignment(Qt::AlignCenter);
        }
    }

    connect(ui->pushButton1, SIGNAL(clicked(bool)), this, SLOT(on_pushButton1_clicked()));
    connect(ui->pushButton2, SIGNAL(clicked(bool)), this, SLOT(on_pushButton2_clicked()));
    connect(ui->pushButton3, SIGNAL(clicked(bool)), this, SLOT(on_pushButton3_clicked()));
    connect(ui->pushButton4, SIGNAL(clicked(bool)), this, SLOT(on_pushButton4_clicked()));
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


void MainWindow::on_pushButton1_clicked()//generate
{

}

void MainWindow::on_pushButton2_clicked()//solve
{
    int map[81],init_map[81];
    for(int i = 0; i < 9; ++i)
    {
        for(int j = 0; j < 9; ++j)
        {
            QString str = ui->tableWidget->item(i, j)->text();
            int num = str.toInt();
            map[i * 9 + j] = num;
            init_map[i * 9 + j] = num;
        }
    }
    Sudoku ques, ans;
    //ques.setMap(set_map);
    for(int i = 0; i < 81; ++i)
    {
        ques.setElement(i, map[i]);
    }
    if(solve(ques, ans)){
        for(int i = 0; i < 9; ++i)
        {
            for(int j = 0; j < 9; ++j)
            {
                QString str = QString::number(ans.getElement(i * 9 + j));
                if(init_map[i * 9 + j] == 0)
                {
                    ui->tableWidget->setItem(i, j, new QTableWidgetItem(str));
                    ui->tableWidget->item(i, j)->setTextAlignment(Qt::AlignCenter);
                }
            }
        }
    }
    else
    {
        ui->label->setText("Unsolvable!!");
    }
}

void MainWindow::on_pushButton3_clicked()//clear
{
    for(int i = 0; i < 9; ++i)//initialize
    {
        for(int j = 0; j < 9; ++j)
        {
            ui->tableWidget->setItem(i, j, new QTableWidgetItem(""));
        }
    }
}

void MainWindow::on_pushButton4_clicked()//set by player
{
    for(int i = 0; i < 9; ++i)
    {
        for(int j = 0; j < 9; ++j)
        {
            if(ui->tableWidget->item(i, j)->text() != "")
            {
                QTableWidgetItem *item = ui->tableWidget->item(i, j);
                item->setFlags(Qt::NoItemFlags);
                item->setBackgroundColor(QColor(136, 217, 245));
            }
        }
    }
}
