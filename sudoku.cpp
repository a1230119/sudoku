#include "sudoku.h"
#include <vector>

using namespace std;

Sudoku::Sudoku()
{
    for(int i = 0; i < sudokuSize; ++i)
        map[i] = 0;
}

Sudoku::Sudoku(const int init_map[])
{
    for(int i = 0; i < sudokuSize; ++i)
        map[i] = init_map[i];
}

void Sudoku::setMap(const int set_map[])
{
    for(int i = 0; i < sudokuSize; ++i)
        map[i] = set_map[i];
}

int Sudoku::getElement(int index)
{
    return map[index];
}

void Sudoku::setElement(int index, int value)
{
    map[index] = value;
}

int Sudoku::getFirstZeroIndex()
{
    for(int i = 0; i < sudokuSize; ++i)
        if(map[i] == 0)
            return i;
    return -1;
}

bool Sudoku::isCorrect()
{
    bool check_result;
    int check_arr[9];
    int location;
    for(int i = 0; i < sudokuSize; i += 9)//check rows
    {
        for(int j = 0; j < 9; ++j)
            check_arr[j] = map[i + j];
        check_result = checkUnity(check_arr);
        if(check_result == false)
            return false;
    }
    for(int i = 0; i < 9; ++i)//check column
    {
        for(int j = 0; j < 9; ++j)
            check_arr[j] = map[i + j * 9];
        check_result = checkUnity(check_arr);
        if(check_result == false)
            return false;
    }

    for(int i = 0; i < 9; ++i)//check cells
    {
        for(int j = 0; j < 9; ++j)
        {
            location = 27*(i/3) + 3*(i%3) +9*(j/3) + (j%3);
            check_arr[j] = map[location];
        }
        check_result = checkUnity(check_arr);
        if(check_result == false)
            return false;
    }
    return true;
}

bool Sudoku::checkUnity(int arr[])
{
    int arr_unity[9];
    for(int i = 0; i < 9; ++i)
        arr_unity[i]=0;
    for(int i = 0; i < 9; ++i)
        ++arr_unity[arr[i] - 1];
    for(int i = 0; i < 9; ++i)
        if(arr_unity[i] != 1)
            return false;
    return true;
}

void Sudoku::checknum(std::vector<std::vector<int> >& rows, std::vector<std::vector<int> >& columns, std::vector<std::vector<int> >& cells)//每一列/行/九宮格可填哪些數字
{    
    bool check[9];

    for(int i = 0; i < 9; ++i)//ckeck rows
    {
        vector<int> row;
        int value;
        for(int j = 0; j < 9; ++j)//initialize check[9]
            check[j] = false;//false -> 都可以填(check[i]代表數字i+1)
        for(int j = 0; j < 9; ++j)
        {
            value = map[9 * i + j];
            if(value > 0)
                check[value - 1] = true;
        }
        for(int j = 0; j < 9; ++j)
            if(!check[j])
                row.push_back(j + 1);
        rows.push_back(row);
    }
    for(int i = 0; i < 9; ++i)//ckeck columns
    {
        vector<int> col;
        int value;
        for(int j = 0; j < 9; ++j)
            check[j] = false;
        for(int j = 0; j < 9; ++j)
        {
            value = map[i + 9 * j];
            if(value > 0)
                check[value - 1] = true;
        }
        for(int j = 0; j < 9; ++j)
            if(!check[j])
                col.push_back(j + 1);
        columns.push_back(col);
    }
    for(int i = 0; i < 9; ++i)//ckeck cells
    {
        vector<int> cell;
        int value;
        for(int j = 0; j < 9; ++j)
            check[j] = false;
        for(int j = 0; j < 9; ++j)
        {
            value = map[27*(i/3) + 3*(i%3) +9*(j/3) + (j%3)];
            if(value > 0)
                check[value - 1] = true;
        }
        for(int j = 0; j < 9; ++j)
            if(!check[j])
                cell.push_back(j+1);
        cells.push_back(cell);
    }
}

std::vector<int> Sudoku::findnum(std::vector<int>& row, std::vector<int>& column, std::vector<int>& cell)
{
    vector<int> result;
    bool checkrow[9], checkcolumn[9], checkcells[9];
    for(int i = 0; i < 9; ++i)
    {
        checkrow[i] = true;//true->不可填
        checkcolumn[i] = true;
        checkcells[i] = true;
    }
    for(int i = 0; i < row.size(); ++i)
        checkrow[row[i] - 1]=false;
    for(int i = 0; i < column.size(); ++i)
        checkcolumn[column[i] - 1]=false;
    for(int i = 0; i < cell.size(); ++i)
        checkcells[cell[i] - 1]=false;
    for(int i = 0; i < 9; ++i)
        if(!checkrow[i] && !checkcolumn[i] && !checkcells[i])
            result.push_back(i + 1);
    return result;
}
