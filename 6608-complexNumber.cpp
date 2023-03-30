#include <iostream>
#include <math.h>
using namespace std;


class ComplexNumber
{
private:
	int* real;
	int* imaginary;
public:	
	ComplexNumber(int r=0, int i=0)
    {
        real = new int(r);
        imaginary = new int(i);        
    }
	~ComplexNumber()
    {
        cout<<"deleted"<<endl;
    }
	void Input()
    {
        cout<<"Enter real:\t";
        cin>>*real;
        cout<<"Enter imaginary:\t";
        cin>>*imaginary;
    }
	void Output()
    {
        if(*imaginary < 0)
            cout<<*real<<*imaginary<<"i\n";
        else
            cout<<*real<<"+"<<*imaginary<<"i\n";
    }
	bool IsEqual(ComplexNumber x)
    {
        if(*real == *x.real && *imaginary == *x.imaginary)
            return true;
        else
            return false;
    }
	ComplexNumber Conjugate()
    {
        return ComplexNumber(*real, *imaginary*-1);
    }
	ComplexNumber Add(ComplexNumber x)
    {
        ComplexNumber add(*real+*x.real, *imaginary+*x.imaginary);
        return add;
    }
	ComplexNumber Subtract(ComplexNumber x)
    {
        ComplexNumber subtract(*real-*x.real, *imaginary-*x.imaginary);
        return subtract;
    }
	ComplexNumber Multiplication(ComplexNumber x)
    {
        ComplexNumber multiply((*real * *x.real)+(*imaginary * *x.imaginary*-1), (*real * *x.imaginary) + (*imaginary * *x.real));
        return multiply;
    }
	float Magnitude()
    {
       return sqrt(*real * *real + *imaginary * *imaginary);
    }
};



int main()
{
    ComplexNumber c1;
    ComplexNumber c2;

    cout<<"Enter c1:\n";
    c1.Input();
    cout<<endl;

    cout<<"Enter c2:\n";
    c2.Input();
    cout<<endl;


    cout<<"c1 = ";
    c1.Output();
    cout<<endl;

    cout<<"c2 = ";
    c2.Output();
    cout<<endl;

    if(c1.IsEqual(c2))
        cout<<"c1 is equal to c2\n";
    else
        cout<<"c1 is not equal to c2\n";

    cout<<"Conjugate of c1 :\t";
    c1.Conjugate().Output();

    cout<<"Conjugate of c2 :\t";
    c2.Conjugate().Output();

    cout<<"c1 + c2:\t";
    c1.Add(c2).Output();

    cout<<"c1 - c2:\t";
    c1.Subtract(c2).Output();

    cout<<"c1 x c2:\t";
    c1.Multiplication(c2).Output();

    cout<<"Magnitue of c1 = "<<c1.Magnitude()<<endl;

    cout<<"Magnitue of c2 = "<<c2.Magnitude()<<endl;


}