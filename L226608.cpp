#include <iostream>
#include <fstream>
#include <string>
#include <limits>

using namespace std;

void displayArray(int* arr, int size);
int* readDataFromFile(fstream &DATA, int &size);
void bubbleSort(int* arr, int size);
void mergeArrays(int* arr1, int* arr2, int* arr3, int size1, int size2, int size3);



int main(){
    //bubble sort
    cout<<"----------------------------------------Bubble Sort Result---------------------------------"<<endl<<endl;
    fstream DATA;                   
    DATA.open("Data1.txt", ios::in);         
    if (!DATA) 
    {                        
        cout<<"File doesn’t exist.";          
    }
    else 
    {
        //assuming 3 test cases in the file
        for(int i=0; i<3; i++)
        {
            cout<<"Test case "<<i+1<<":"<<endl;
            int size = 0;
            int* arr = readDataFromFile(DATA, size);
            if(arr)
            {
                cout<<"Array before sorting: ";
                displayArray(arr, size);
                cout<<endl;
                bubbleSort(arr, size);
                cout<<"Sorted Array: "<<endl;
                displayArray(arr, size);
            }
            cout<<endl<<endl;
            delete[] arr;
        }
    } 
DATA.close();  


    //merge arrays
    cout<<"----------------------------------------Merge Arrays Result-----------------------------------"<<endl<<endl;
    DATA.open("Data2.txt", ios::in);         
    if (!DATA) 
    {                            
        cout<<"File doesn’t exist.";          
    }
    else
    {
        //assuming 3 test cases in the file
        for(int i=0; i<3; i++)
        {
            cout<<"Test case "<<i+1<<":"<<endl;
            //initialization of arrays dynamically;
            int size1 = 0;
            int* arr1 = readDataFromFile(DATA,size1);

            int size2 = 0;
            int* arr2 = readDataFromFile(DATA, size2);

            int size3 = size2 +size1;
            int *arr3 = NULL;
            arr3 = new int[size3];

            cout<<"Array 1: ";
            displayArray(arr1, size1);

            cout<<endl<<"Array 2: ";
            displayArray(arr2, size2);
            cout<<endl<<endl;
            
            mergeArrays(arr1, arr2, arr3, size1, size2, size3);

            cout<<"Sorted Merged Array: "<<endl;
            displayArray(arr3, size3);
            cout<<endl<<endl<<endl;

            delete[] arr1;
            delete[] arr2;   
            delete[] arr3;   
        }
    }
    DATA.close();  
}


void displayArray(int* arr, int size){
    for(int* ptr = arr; ptr < arr + size; ptr++)
    {
        cout<<*ptr<<" ";
    }
    cout<<endl;
}

int* readDataFromFile(fstream &DATA, int &size){
    DATA>>size;
    if(size < 0)
    {
        cout<<"Error:            Array Size should be greater than zero."<<endl<<endl;
        string line;
        getline(DATA, line);
        DATA.ignore(numeric_limits<streamsize>::max(), '\n');
        return NULL;
    }
    else
    {
        //dynamic allocation of array
        int *arr = NULL;
        arr = new int[size];
        for(int* ptr = arr; ptr < arr + size; ptr++)
        {
            DATA>>*ptr        ;
        }
        return arr;
    }
}

void bubbleSort(int* arr, int size){
    int counter = 1;
    for(int i=0; i<size; i++)
    {
        for(int* ptrr = arr; ptrr < arr + size - counter; ptrr++)
        {
            if(*ptrr >= *(ptrr + 1))
            {
                swap(*ptrr, *(ptrr + 1));
            }
        }
        counter++;
    }
}

void mergeArrays(int* arr1, int* arr2, int* arr3, int size1, int size2, int size3){
    int index1 = 0;
    int index2 = 0;
    int index3 = 0;
            while(index1 < size1 && index2 < size2)
            {
                if(*(arr1 + index1) <= *(arr2 + index2))
                {
                    *(arr3 + index3) = *(arr1 + index1);
                    index3++;
                    index1++;
                }
                else
                {
                    *(arr3 + index3) = *(arr2 + index2);
                    index3++;
                    index2++;
                }
            }
            while(index1 < size1)
            {
                *(arr3 + index3) = *(arr1 + index1);
                index3++;
                index1++;
            }
            while(index2 < size2)
            {
                *(arr3 + index3) = *(arr2 + index2);
                index3++;
                index2++;
            }
}

 