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
    std::vector<int> findnum(std::vector<int>& row, std::vector<int>& column, std::vector<int>& cells);
    static const int sudokuSize = 81;
    static std::vector<int> row_vector[9];
    static std::vector<int> column_vector[9];
    static std::vector<int> cells_vector[9];

private:
    bool checkUnity(int arr[]);
    void checknum();//確認有哪些數字可以被填入
    int map[sudokuSize];

};

#endif // SUDOKU_H
