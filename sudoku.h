#ifndef SUDOKU_H
#define SUDOKU_H

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
    static const int sudokuSize = 81;

private:
    void checknum();//確認有哪些數字可以被填入
    bool checkUnity(int arr[]);
    int map[sudokuSize];
};

#endif // SUDOKU_H
