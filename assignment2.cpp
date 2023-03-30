#include <iostream>
#include <fstream>
using namespace std;

int** InputMatrix(fstream& fin, int& rows, int& cols);
void OutputMatrix(int** matrix, const int& ROWS, const int& COLS);
void deleteMatrix(int** matrix, const int& ROWS);
int** AddMatrix(int** matrixA, int** matrixB, const int& ROWS, const int& COLS);
int** TransposeMatrix(int** matrix, const int& ROWS, const int& COLS);
bool IsSymmetric(int** matrix, const int& ROWS, const int& COLS);
void InterchangeRows(int** matrix, const int& ROWS, const int& COLS );
void InterchangeRows( int*& row1, int*& row2 );



int main(){
    fstream DATA;
    DATA.open("Input.txt", ios::in);         
    if (!DATA) 
    {                        
        cout<<"File doesn’t exist.";          
    }
    else
    {
        int rowsA = 0, colsA = 0;
        int rowsB = 0, colsB = 0;
        int rowsC = 0, colsC = 0;

        int** matrixA = InputMatrix(DATA, rowsA, colsA);
        int** matrixB = InputMatrix(DATA, rowsB, colsB);
        int** matrixC = InputMatrix(DATA, rowsC, colsC);

        cout<<"Matrix A = \n";
        OutputMatrix(matrixA, rowsA, colsA);
        cout<<"Matrix B = \n";
        OutputMatrix(matrixB, rowsB, colsB);
        cout<<"Matrix C = \n";
        OutputMatrix(matrixC, rowsC, colsC);

        int** result = NULL;
        cout<<"A + B =  \n";
        if(rowsA == rowsB && colsA == colsB)
        {
            result = AddMatrix(matrixA, matrixB, rowsA, colsA);
            OutputMatrix(result, rowsA, colsA);
            deleteMatrix(result, rowsA);
        }
        else
        {
            cout<<"Addition not possible\n\n";
        }

        cout<<"A + C = \n";
        if(rowsA == rowsC && colsA == colsC)
        {
            result = AddMatrix(matrixA, matrixC, rowsA, colsA);
            OutputMatrix(result, rowsA, colsA);
            deleteMatrix(result, rowsA);
        }
        else
        {
            cout<<"Addition not possible\n\n";
        }

        cout<<"transpose of A = \n";
        result = TransposeMatrix(matrixA, rowsA, colsA);
        OutputMatrix(result, rowsA, colsA);
        deleteMatrix(result, rowsA);

        cout<<"transpose of C = \n";
        result = TransposeMatrix(matrixC, rowsC, colsC);
        OutputMatrix(result, colsC, rowsC);
        deleteMatrix(result, rowsC);

        if(IsSymmetric(matrixA, rowsA, colsA)){
            cout<<"matrix A is symmetric"<<endl<<endl;
        }
        else
        {
            cout<<"matrix A is not symmetric"<<endl<<endl;

        }
        if(IsSymmetric(matrixB, rowsB, colsB)){
            cout<<"matrix B is symmetric"<<endl<<endl;
        }
        else
        {
            cout<<"matrix B is not symmetric"<<endl<<endl;

        }

        cout<<"Interchanging Rows of Matrix A:\nrow1: 1\nrow2: 3\n\nAfter Interchanging Rows Matrix A=\n";          

        InterchangeRows(matrixC, rowsC, colsC);
        OutputMatrix(matrixC, rowsC, colsC);
            
        
        
        deleteMatrix(matrixA, rowsA);
        deleteMatrix(matrixB, rowsB);
        deleteMatrix(matrixC, rowsC);

        matrixA = NULL;
        matrixB = NULL;
        matrixC = NULL;

    }

}




int** InputMatrix(fstream& DATA, int& rows, int& cols){
    DATA>>rows;
    DATA>>cols;
    int** matrix = new int*[rows];
    for(int** iPtr = matrix; iPtr < matrix + rows; iPtr++)
    {
        *iPtr = new int[cols];
    }

    for(int** iPtr = matrix; iPtr < matrix + rows; iPtr++)
    {
        for(int* jPtr = *iPtr; jPtr < *iPtr + cols; jPtr++)
        {
            DATA>>*jPtr;
        }
    }
    return matrix;
}

void OutputMatrix(int** matrix, const int& ROWS, const int& COLS)
{
    for(int** iPtr = matrix; iPtr < matrix + ROWS; iPtr++)
    {
        for(int* jPtr = *iPtr; jPtr < *iPtr + COLS; jPtr++)
        {
            cout<<*jPtr<<"  ";
        }
        cout<<endl;
    }
    cout<<endl;
}

void deleteMatrix(int** matrix, const int& ROWS)
{
    for(int i=0; i<ROWS; i++)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
}

int** AddMatrix(int** matrixA, int** matrixB, const int& ROWS, const int& COLS)
{
    int** result = new int*[ROWS];
    for(int** iPtr = result; iPtr < result + ROWS; iPtr++ )
    {
        *iPtr = new int[COLS];
    }

    int** iPtr = result;
    int**aPtr = matrixA;
    int**bPtr = matrixB;
    for(; iPtr < result + ROWS; iPtr++, aPtr++, bPtr++ )
    {
        for(int* jPtr = *iPtr, *ajPtr = *aPtr, *bjPtr = *bPtr; jPtr < *iPtr + COLS; jPtr++, ajPtr++, bjPtr++)
        {
            *jPtr = *ajPtr + *bjPtr;
        }
    }

    return result;
}

int** TransposeMatrix(int** matrix, const int& ROWS, const int& COLS)
{
    int** result = new int*[COLS];
    for(int i=0; i < COLS; i++)
    {
        *(result + i) = new int[ROWS];
    }
    
    for(int i=0; i < ROWS; i++)
    {
        for(int j=0; j < COLS; j++)
        {
            *(*(result + j) + i) = *(*(matrix + i) + j);
        }
    }

    return result;
}

bool IsSymmetric(int** matrix, const int& ROWS, const int& COLS)
{
    if(ROWS != COLS)
        return false;



    int** transposed = TransposeMatrix(matrix, ROWS, COLS);
    bool symmetric = true;

    for(int i = 0; i < ROWS; i++)
    {
        for(int j=0; j< COLS; j++)
        {
            if(transposed[i][j] != matrix[i][j])
            {
                symmetric = false;
            }
        }
    }

    

    deleteMatrix(transposed, COLS);
    return symmetric;
}


void InterchangeRows(int** matrix, const int& ROWS, const int& COLS )
{
    int row1 = 1;
    int row2 = 2;

    InterchangeRows(*(matrix + row1 -1), *(matrix + row2 - 1));


}

void InterchangeRows( int*& row1, int*& row2 )
{
    int* temp = row2;
    row2 = row1;
    row1 = temp;
}

