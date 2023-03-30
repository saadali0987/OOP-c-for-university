#include <iostream>
using namespace std;

//main functions
 int* InputArray(int& size);
 void OutputArray(int* myArray, const int& size);
 int* CompressArray(int* originalArr, int& size);
 int* Intersection(int* setA, int& size1, int* setB, int& size2, int& size3);

 //helper functions
 bool foundBefore(int* arr, int value, int index);
 int numberOfUniqueElements(int* arr, int size);
 int findNumberOfCommonElements(int* arr1, int* arr2, int size1, int size2);
 bool isCommon(int* arr2, int size2, int value);


int main(){
    int size = 0;
    int* arr = InputArray(size);
    OutputArray(arr, size);
    int* newCompressedArray = CompressArray(arr, size);
    int compressedArraySize = numberOfUniqueElements(arr, size);
    cout<<"Array after compression: ";
    OutputArray(newCompressedArray, compressedArraySize);


    delete[] arr;
    delete[] newCompressedArray;

    cout<<endl<<"--------------------------------------------"<<endl;

    int size1 = 0;
    int* arr1 = InputArray(size1);
    int size2 = 0;
    int* arr2 = InputArray(size2);
    int size3 = findNumberOfCommonElements(arr1, arr2, size1, size2);
    int* intersectionArray = Intersection(arr1, size1, arr2, size2, size3); 
    cout<<"A: ";
    OutputArray(arr1, size1);
    cout<<"B: ";
    OutputArray(arr2, size2);
    cout<<"A intersection B = ";
    OutputArray(intersectionArray, size3);

    delete[] arr1;
    delete[] arr2;
    delete[] intersectionArray;
}


int* InputArray(int& size)
{
    cout<<"Enter size of array: ";
    cin>>size;
    int* arr = new int[size];

    cout<<"Enter "<<size<<" elements: "<<endl;
    for(int* ptr = arr; ptr < arr + size; ptr++)
    {
        cin>>*ptr;
    }

    return arr;
 }

 void OutputArray(int* myArray, const int& size)
 {
    for(int* ptr = myArray; ptr < myArray + size; ptr++)
    {
        cout<<*ptr<<" ";
    }
    cout<<endl;
 }

 bool foundBefore(int* arr, int value, int index)
 {
    bool found = false;
    for(int i=0; i < index; i++)
    {
        if(*(arr + i) == value)
        {
            found = true;
        }
    }
    return found;
 }

 int numberOfUniqueElements(int* arr, int size)
 {
    int count = 0;
    for(int i=0; i<size; i++)
    {
        if(foundBefore(arr, *(arr + i), i) == false)
        {
            count++;
        }
    }
    return count;
 }

  int* CompressArray(int* originalArr, int& size)
  {
    int compressedSize = numberOfUniqueElements(originalArr, size);
    cout<<compressedSize<<endl;
    int* compressedArray = new int[compressedSize];
    
    int index = 0;
    for(int i=0; i<size; i++)
    {
        if(foundBefore(originalArr, *(originalArr + i), i) == false)
        {
            *(compressedArray + index) =  *(originalArr + i);
            index++;
        }
    }
    return compressedArray;
 }

 int findNumberOfCommonElements(int* arr1, int* arr2, int size1, int size2)
 {
    int count = 0;
    for(int i=0; i<size1; i++)
    {
        for(int j=0; j<size2; j++)
        {
            if(*(arr1 + i) == *(arr2 + j))
            {
                count++;
                break;
            }
        }
    }
    return count;
}

bool isCommon(int* arr2, int size2, int value)
{
    bool found = false;
    for(int i=0; i<size2; i++)
    {
        if(arr2[i] == value)
        {
            found = true;
        }
    }
    return found;
}

int* Intersection(int* setA, int& size1, int* setB, int& size2, int& size3)
{
    int* arr3 = new int[size3];
    int index =0;
    for(int j=0; j<size1; j++)
    {
        if(isCommon(setB, size2, setA[j]) == true)
        {
            *(arr3 + index) = *(setA + j);
            index++;
        }
    }
    return arr3;
}