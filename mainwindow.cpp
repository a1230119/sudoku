#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sudoku.h"

#include <QHeaderView>
#include <QTableWidgetItem>
#include <vector>
#include <QString>
#include <QLabel>
#include <algorithm>
#include <QVector>

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

    for(int i = 0; i < 9; ++i)//initialize
    {
        for(int j = 0; j < 9; ++j)
        {
            ui->tableWidget->setItem(i, j, new QTableWidgetItem(""));
            ui->tableWidget->item(i, j)->setTextAlignment(Qt::AlignCenter);
        }
    }
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

void MainWindow::changeNum(int array[])
{
    srand(time(NULL));
    int a = rand()%9 + 1;
    int b = rand()%9 + 1;
    if(a != b)
    {
        for(int i = 0; i < 81; ++i)
        {
            if(array[i] == a)
                array[i] = b;
            else if(array[i] == b)
                array[i] = a;
        }
    }
}

void MainWindow::changeRowCol(int array[])
{
    srand(time(NULL));
    int a = rand()%3;
    int b = rand()%3;
    int c = rand()%2;
    int temp[27];
    if(a != b)
    {
        if(c == 0)//change row
        {
            for(int i = 0; i < 27; ++i)
            {
                temp[i] = array[a*27+i];
                array[a*27+i] = array[b*27+i];
                array[b*27+i] = temp[i];
            }
        }
        else//change column
        {
            for(int i = 0; i < 9; ++i)
            {
                for(int j = 0; j < 3; ++j)
                {
                    temp[i*3+j] = array[a*3+i*9+j];
                    array[a*3+i*9+j] = array[b*3+i*9+j];
                    array[b*3+i*9+j] = temp[i*3+j];
                }
            }
        }
    }
}

vector<int> MainWindow::randIndex()
{
    vector<int> init, result;
    for(int i = 0; i < 81; ++i)
    {
        init.push_back(i + 1);
    }
    srand(time(NULL));
    random_shuffle(init.begin(), init.end());//產生不重複亂數
    int r = rand()%20 + 40;
    for(int i = 0; i < r; ++i)//取前面r個亂數
        result.push_back(init.at(i));
    sort(result.begin(), result.end());
    return result;
}

void MainWindow::on_pushButton1_clicked()//generate
{
    int generate_map[81] = {0};
    int a[81] = {5, 4, 6, 9, 2, 7, 8, 1, 3, 2, 7, 3, 6, 8, 1, 9, 5, 4, 9, 8, 1, 3, 4, 5, 6, 7, 2, 6, 9, 5, 7, 1, 2, 4, 3, 8, 1, 2, 8, 4, 6, 3, 5, 9, 7, 7, 3, 4, 8, 5, 9, 1, 2, 6, 3, 6, 7, 1, 9, 8, 2, 4, 5, 8, 5, 9, 2, 3, 4, 7, 6, 1, 4, 1, 2, 5, 7, 6, 3, 8, 9};
    int b[81] = {3, 8, 9, 1, 4, 5, 6, 2, 7, 2, 4, 7, 9, 8, 6, 3, 5, 1, 6, 5, 1, 7, 2, 3, 9, 8, 4, 9, 3, 5, 2, 6, 7, 4, 1, 8, 8, 6, 2, 4, 9, 1, 5, 7, 3, 7, 1, 4, 5, 3, 8, 2, 6, 9, 5, 9, 8, 6, 1, 4, 7, 3, 2, 4, 7, 3, 8, 5, 2, 1, 9, 6, 1, 2, 6, 3, 7, 9, 8, 4, 5};
    int c[81] = {9, 2, 3, 8, 1, 6, 4, 7, 5, 6, 4, 5, 9, 2, 7, 1, 3, 8, 8, 1, 7, 3, 5, 4, 6, 2, 9, 7, 9, 8, 4, 6, 3, 2, 5, 1, 5, 6, 4, 2, 8, 1, 3, 9, 7, 2, 3, 1, 7, 9, 5, 8, 6, 4, 4, 8, 9, 6, 7, 2, 5, 1, 3, 3, 5, 2, 1, 4, 9, 7, 8, 6, 1, 7, 6, 5, 3, 8, 9, 4, 2};
    //int d[81]
    vector<int> rnd = randIndex();
    int k = 0;
    srand(time(NULL));
    switch (rand()%3)
    {
    case 0:
        changeNum(a);
        changeRowCol(a);
        for(int i = 0; i < Sudoku::sudokuSize; ++i)
        {
            if(k < rnd.size())
                if(i == rnd.at(k))
                {
                    generate_map[i] = 0;
                    ++k;
                }
                else
                    generate_map[i] = a[i];
        }
        break;
    case 1:
        changeNum(b);
        changeRowCol(b);
        for(int i = 0; i < Sudoku::sudokuSize; ++i)
        {
            if(k < rnd.size())
                if(i == rnd.at(k))
                {
                    generate_map[i] = 0;
                    ++k;
                }
                else
                    generate_map[i] = b[i];
        }
        break;
    case 2:
        changeNum(c);
        changeRowCol(c);
        for(int i = 0; i < Sudoku::sudokuSize; ++i)
        {
            if(k < rnd.size())
                if(i == rnd.at(k))
                {
                    generate_map[i] = 0;
                    ++k;
                }
                else
                    generate_map[i] = c[i];
        }
        break;
    default:
        changeNum(a);
        changeRowCol(a);
        for(int i = 0; i < Sudoku::sudokuSize; ++i)
        {
            if(k < rnd.size())
                if(i == rnd.at(k))
                {
                    generate_map[i] = 0;
                    ++k;
                }
                else
                    generate_map[i] = a[i];
        }
        break;
    }

    for(int i = 0; i < 9; ++i)
    {
        for(int j = 0; j < 9; ++j)
        {
            if(generate_map[i*9+j] != 0)
            {
                QString str = QString::number(generate_map[i*9+j]);
                ui->tableWidget->setItem(i, j, new QTableWidgetItem(str));
                QTableWidgetItem *item = ui->tableWidget->item(i, j);
                item->setTextAlignment(Qt::AlignCenter);
                item->setFlags(Qt::NoItemFlags);
                item->setBackgroundColor(QColor(136, 217, 245));
            }
        }
    }
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
