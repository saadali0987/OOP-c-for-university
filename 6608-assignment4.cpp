#include <iostream>
#include<math.h>
using namespace std;

class ComplexNumber
{
    private:
        int real;
        int imaginary;
    
    public:
        ComplexNumber(int r = 0, int i = 0);
	    void Input();
        void Output();
        bool IsEqual(ComplexNumber a);
        ComplexNumber Conjugate();
        ComplexNumber Add(ComplexNumber a);
        ComplexNumber Subtract(ComplexNumber a);
        ComplexNumber Multiplication(ComplexNumber a);
        float Magnitude();
};

int main()
{
    ComplexNumber c1;
    ComplexNumber c2;
    c1.Input();
    c1.Output();
    cout<<endl;
    cout<<c1.Magnitude();
    c2.Input();
    c2.Output();

    cout<<c2.Magnitude();
    c1.IsEqual(c2);
    ComplexNumber c3 = c1.Add(c2);
    c3.Output();
    c3 = c1.Subtract(c2);
    c3.Output();
    c3 = c1.Multiplication(c2);
    c3.Output();
}
























void ComplexNumber::Input()
{
    cout<<"Enter Real\t";
    cin>>real;
    cout<<"Enter Imaginary\t";
    cin>>imaginary;
}

ComplexNumber::ComplexNumber(int r, int i)
{
    real = r;
    imaginary = i;
}

void ComplexNumber::Output()
{
    if(imaginary < 0)
        cout<<real<<imaginary<<"i";
    else
        cout<<real<<"+"<<imaginary<<"i";
}

bool ComplexNumber::IsEqual(ComplexNumber a)
{   
    if(real != a.real || imaginary != a.imaginary)
        return false;
    return true;
}

ComplexNumber ComplexNumber::Conjugate()
{
    return ComplexNumber(real, imaginary*-1);
}

ComplexNumber ComplexNumber::Add(ComplexNumber a)
{
    return ComplexNumber(real + a.real, imaginary + a.imaginary);
}
ComplexNumber ComplexNumber::Subtract(ComplexNumber a)
{
    return ComplexNumber(real - a.real, imaginary - a.imaginary);
}
ComplexNumber ComplexNumber::Multiplication(ComplexNumber a)
{
    return ComplexNumber((real*a.real)+(imaginary*a.imaginary*-1), (real * a.imaginary) + (imaginary * a.real));
}
float ComplexNumber::Magnitude()
{
    return sqrt(real*real + imaginary*imaginary);
}