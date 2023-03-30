#include <iostream>
#include <math.h>
using namespace std;

class ComplexNumber{

    private:
	    int* real;	//Integer will be saved on heap
	    int* imaginary;	//Data will be saved on heap
    public:
	    ComplexNumber(int r = 0, int i = 0)
        {
            real = new int(r);
            imaginary = new int(i);
            if(*imaginary<0)
                cout<<"Constructor called for complexNumber "<<*real<<*imaginary<<"i"<<endl;
            else
                cout<<"Constructor called for complexNumber "<<*real<<"+"<<*imaginary<<"i"<<endl;
        } 
	    ~ComplexNumber()
        {
            if(*imaginary<0)
                cout<<"destructor called for complexNumber "<<*real<<*imaginary<<"i"<<endl;
            else
                cout<<"destructor called for complexNumber "<<*real<<"+"<<*imaginary<<"i"<<endl;

            delete real;
            delete imaginary;
        }
	    void Input()
        {
            cout<<"Real:\t";
            cin>>*real;
            cout<<"Imaginary:\t";
            cin>>*imaginary;
        }
	    void Output()
        {
            if(*imaginary<0)
                cout<<*real<<*imaginary<<"i"<<endl;
            else
                cout<<*real<<"+"<<*imaginary<<"i"<<endl;
        }
	    float Magnitude()
        {
            float rSquared = *real * *real;
            float iSquared = *imaginary * *imaginary;
            return sqrt(rSquared + iSquared);
        }

};

int main()
{
    ComplexNumber c1;
    c1.Input();
    c1.Output();

    //cPtr does not implicitally calls the constructor
    ComplexNumber* cPtr;

    cPtr = new ComplexNumber(3,5);
    cPtr->Output();

    ComplexNumber arr[5];
    for(int i=0; i<5;i++)
    {
        arr[i].Input();
        cout<<arr[i].Magnitude()<<endl;
    }
    //no need to delete this array as it's on the stack and will get deleted by destructor


    int size;
    cout<<"Enter array size:\t";
    cin>>size;
    ComplexNumber* dynamicArr = new ComplexNumber[size];
    for(int i=0; i<size;i++)
    {
        dynamicArr[i].Input();
        dynamicArr[i].Output();
        cout<<dynamicArr[i].Magnitude()<<endl;
    }
    delete[] dynamicArr;
    dynamicArr = 0;
}