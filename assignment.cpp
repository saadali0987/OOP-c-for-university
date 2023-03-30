#include <iostream>
#include <fstream>
#include <string>
#include <limits>

using namespace std;




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
            DATA>>size;
            //checking for size
            if(size < 0)
            {
                cout<<"Error:            Array Size should be greater than zero."<<endl<<endl;
                string line;
                getline(DATA, line);
                DATA.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else
            {
                //dynamic allocation of array
                int *arr = NULL;
                arr = new int[size];
                for(int* ptr = arr; ptr < arr + size; ptr++)
                {
                    DATA>>*ptr;
                }
                cout<<"Array before sorting: ";
                for(int* ptr = arr; ptr < arr + size; ptr++)
                {
                    cout<<*ptr<<" ";
                }
                cout<<endl;
                //bubble sort algorithm
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
                cout<<"Sorted Array: "<<endl;
                for(int* ptr = arr; ptr < arr + size; ptr++)
                {
                    cout<<*ptr<<" ";
                }
                cout<<endl<<endl;
                delete[] arr;
            }
            
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
            DATA>>size1;
            int *arr1 = NULL;
            arr1 = new int[size1];
            for(int* ptr = arr1; ptr < arr1 + size1; ptr++)
            {
                DATA>>*ptr;
            }
            int size2 = 0;
            DATA>>size2;
            int *arr2 = NULL;
            arr2 = new int[size2];
            for(int* ptr = arr2; ptr < arr2 + size2; ptr++)
            {
                DATA>>*ptr;
            }
            int size3 = size2 +size1;
            int *arr3 = NULL;
            arr3 = new int[size3];

            cout<<"Array 1: ";
            for(int* ptr = arr1; ptr < arr1 + size1; ptr++)
            {
                cout<<*ptr<<" ";
            }
            cout<<endl<<"Array 2: ";
            for(int* ptr = arr2; ptr < arr2 + size2; ptr++)
            {
                cout<<*ptr<<" ";
            }
            cout<<endl<<endl;

            //algorithm for merging
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
            cout<<"Sorted Merged Array: "<<endl;
            for(int* ptrr = arr3; ptrr < arr3 + size3; ptrr++)
            {
                cout<<*ptrr<<" ";
            }
            cout<<endl<<endl<<endl;
            delete[] arr1;
            delete[] arr2;   
            delete[] arr3;   
        }
    }
    DATA.close();  
}