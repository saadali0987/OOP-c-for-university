#include <iostream>
using namespace std;

inline int** AllocateMemory(int& rows, int& cols);
inline void InputMatrix(int** matrix, const int& rows, const int& cols);
inline void DisplayMatrix(int** matrix, const int& rows, const int& cols);
inline void DisplayArray(int* arr, const int& size);
inline void DeallocateMemory(int** matrix, const int& rows);
int* MaxOfColumn(int** arr, const int& rows, const int& cols);


int main(){ 
    int rows =0 , cols =0;
    int** matrix = AllocateMemory(rows, cols);
    InputMatrix(matrix, rows, cols);
    DisplayMatrix(matrix, rows, cols);
    int* maxCols = MaxOfColumn(matrix, rows, cols);
    DisplayArray(maxCols, cols);
    delete[] maxCols;
    maxCols = NULL;
    DeallocateMemory(matrix, rows);
}


inline int** AllocateMemory(int& rows, int& cols)
{
    cout<<"Enter number of rows: ";
    cin>>rows;
    cout<<"Enter number of columns: ";
    cin>>cols;
    int** matrix = new int*[rows];
    for(int i=0; i<rows;i++)
    {
        *(matrix + i) = new int[cols];
    }
    return matrix;
}

inline void InputMatrix(int** matrix, const int& rows, const int& cols)
{
    cout<<"Enter elemens of the matrix: "<<endl;
    for(int i=0; i<rows;i++)
    {
        for(int j=0; j<cols;j++)
        {
            cin>>*(*(matrix + i) + j);
        }
    }
}

inline void DisplayMatrix(int** matrix, const int& rows, const int& cols)
{
    cout<<"The matrix is: "<<endl;
    for(int i=0; i<rows;i++)
    {
        for(int j=0; j<cols;j++)
        {
            cout<<*(*(matrix + i) + j)<<" ";
        }
        cout<<endl;
    }
}

inline void DeallocateMemory(int** matrix, const int& rows)
{
    for(int i=0; i<rows; i++)
    {
        delete[] *(matrix + i);
    }
    delete[] matrix;
    matrix = NULL;
}

int* MaxOfColumn(int** arr, const int& rows, const int& cols){
    int* maxCols = new int[cols];
    int index = 0;
    int max;
    for(int i=0; i<cols; i++){
        max = arr[0][i];
        for(int j=0; j<rows;j++){
            if(arr[j][i] > max){
                max = arr[j][i];
            }
        }
        maxCols[index] = max;
        index++;
    }

    return maxCols;
}

inline void DisplayArray(int* arr, const int& size){
    for(int i=0; i<size;i++){
        cout<<arr[i]<<" ";
    }
}