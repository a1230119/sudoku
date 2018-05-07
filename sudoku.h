#ifndef SUDOKU_H
#define SUDOKU_H

#include <vector>

class Sudoku
{
public:
    Sudoku();
    Sudoku(const int init_map[]);
    void setMap(const int set_map[]);
    int getElement(int index);
    void setElement(int index, int value);
    int getFirstZeroIndex();
    bool isCorrect();
    void checknum(std::vector<std::vector<int>>& rows, std::vector<std::vector<int>>& columns, std::vector<std::vector<int>>& cells);//確認有哪些數字可以被填入
    std::vector<int> findnum(std::vector<int>& row, std::vector<int>& column, std::vector<int>& cell);
    void generateQuestion();
    static const int sudokuSize = 81;

private:
    bool checkUnity(int arr[]);
    int map[sudokuSize];

};

#endif // SUDOKU_H
