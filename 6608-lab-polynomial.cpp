#include <iostream>
using namespace std;


class Polynomial
{
    friend ostream& operator<<(ostream&, const Polynomial&);
    friend Polynomial operator+(int n, Polynomial& poly);

private:
int totalTerms;//Total terms in a Polynomial
int* coeff;//to save array of coefficients
int* exp; //to save array of exponents


bool searchBefore(int* arr, int index, int value)
{
    for(int i=index-1; i >= 0; i--)
    {
        if(arr[i] == value)
        {
            return true;
        }
    }
    return false;
}

    public:
        Polynomial(int nterms, int* nCoeff, int* nExp)
        {
            totalTerms = nterms;
            coeff = new int[totalTerms];
            exp = new int[totalTerms];

            for(int i=0;i<totalTerms; i++)
            {
                coeff[i] = nCoeff[i];
                exp[i] = nExp[i];    
            }
        }
        Polynomial(const Polynomial& rhs)
        {
            totalTerms = rhs.totalTerms;
            coeff = new int[totalTerms];
            exp = new int[totalTerms];

            for(int i=0;i<totalTerms; i++)
            {
                coeff[i] = rhs.coeff[i];
                exp[i] = rhs.exp[i];    
            }

        }
        bool operator!()
        {
            if( totalTerms == 1 && exp[0] == 0 && coeff[0] == 0)
            {
                return true;
            }
            return false;
        }       
        bool operator!=(const Polynomial& rhs)
        {
            if (totalTerms != rhs.totalTerms)
            {
                return true;
            }

            for(int i=0; i<totalTerms; i++)
            {
                if(exp[i] != rhs.exp[i] || coeff[i] != rhs.coeff[i])
                {
                    return true;
                }
            }
            return false;
        }
        Polynomial operator+(const Polynomial& rhs)
        {
            /*The way this works is that i spread the coeffitants and exponents of both polys in 2 arrays, coe and ex, in an ordered manner(lhs first and then rhs). I iterate over the arrays and for each exponent, i first seach backwards to see if it's appearing for the first time and if so, I start iterating forward and for each match of that exponent, I add their respective coefficants. At the end, I store the result(both the resultant coefficant and exponent) in a new array. If no match if found, result gets added to the new array with coefficant unchanged. After all this is done, I do some refactoring with the arrays to remove any extra space. Then i create a new poly object with the new data and return it*/
            int numOfTerms = totalTerms + rhs.totalTerms;
            int* coe = new int[numOfTerms];
            int* ex = new int[numOfTerms];

            int* tempcoe = new int[numOfTerms];
            int* tempex = new int[numOfTerms];

            int i=0;
            for(; i<totalTerms; i++)
            {
                coe[i] = coeff[i];
                ex[i] = exp[i];
            }
            for(int j=0; j<rhs.totalTerms; j++, i++)
            {
                coe[i] = rhs.coeff[j];
                ex[i] = rhs.exp[j];
            }

            int index=0;
            for(int j=0; j<numOfTerms; j++)
            {
                if(!searchBefore(ex, j, ex[j]))
                {
                    bool found = false;
                    for(int k=j+1; k<numOfTerms; k++)
                    {
                        if(ex[j] == ex[k])
                        {
                            coe[j] = coe[j] + coe[k];
                            tempcoe[index] = coe[j];
                            tempex[index] = ex[j];
                            index++;
                            found = true;
                        }
                    }
                    if(found == false)
                    {
                        tempcoe[index] = coe[j];
                        tempex[index] = ex[j];
                        index++;
                    }
                }
            }

            int size = index;
            delete[] coe;
            delete[] ex;

            coe = new int[size];
            ex = new int[size];

            for(int k=0; k<size;k++)
            {
                coe[k] = tempcoe[k];
                ex[k] = tempex[k];
            }
            delete[] tempcoe;
            delete[] tempex;

            int counter = 0;
            for(int i=0; i<=size-1;i++)
            {  
                for(int j=0; j<size -1 - counter; j++)
                {
                    if(ex[j] < ex[j+1])
                    {
                        int temp = ex[j];
                        ex[j] = ex[j+1];
                        ex[j+1] = temp;

                        temp = coe[j];
                        coe[j] = coe[j+1];
                        coe[j+1] = temp;
                    }
                }
                counter++;
            }

            Polynomial newPoly(size, coe, ex);
            delete[] coe;
            delete[] ex;
            return newPoly;
            
        }
        Polynomial& operator++()
        {
            for(int i=0; i<totalTerms; i++)
            {
                coeff[i] = coeff[i] + 1;
            }
            return *this;
        }
        Polynomial operator++(int n)
        {
            Polynomial temp = *this;
            for(int i=0; i<totalTerms; i++)
            {
                coeff[i] = coeff[i] + 1;
            }
            return temp;
        }
        ~Polynomial()
        {
            if(coeff)
                delete[] coeff;
            if(exp)
                delete[] exp;
        }
        Polynomial& operator=(const Polynomial& rhs)
        {
            if(this != &rhs)
            {
                totalTerms = rhs.totalTerms;
                coeff = new int[totalTerms];
                exp = new int[totalTerms];
                for(int i=0; i<totalTerms; i++)
                {
                    coeff[i] = rhs.coeff[i];
                    exp[i] = rhs.exp[i];
                }
            }
            return *this;
        }
};

Polynomial operator+(int n, Polynomial& poly)
{
    Polynomial newPoly = poly;
    for(int i=0; i<newPoly.totalTerms; i++)
    {
        if(newPoly.exp[i] == 0)
        {
            newPoly.coeff[i] = newPoly.coeff[i] + n;
            break;
        }
    }
    return newPoly;
}
ostream& operator<<(ostream& cout, const Polynomial& poly)
{
    for(int i=0; i< poly.totalTerms; i++)
    {
        //If not last term, print "term +"
        if(i != poly.totalTerms-1)
        {

            //if coeff greater than 1, print coeff
            if(poly.coeff[i] > 1)
            {
                //if exp greate than 1, print exp
                if(poly.exp[i] > 1)
                {
                    cout<<poly.coeff[i]<<"x^"<<poly.exp[i]<<" + ";
                }
                //if exp equal to 1, no need to print exp
                else if(poly.exp[i] == 1)
                {
                    cout<<poly.coeff[i]<<"x + ";
                }
                //if exp equal to 0, just print the coeff;
                else
                {
                    cout<<poly.coeff[i]<<" + ";
                }
            }
            //if coeff equal to 1, no need to print coeff
            else if( poly.coeff[i] == 1)
            {
                if(poly.exp[i] > 1)
                {
                    cout<<"x^"<<poly.exp[i]<<" + ";
                }
                else if(poly.exp[i] == 1)
                {
                    cout<<"x + ";
                }
                else
                {
                    cout<<"1 + ";
                }
            }
            //if coeff equal to zero, just print zero for the whole term
            else
            {
                cout<<"0";
            }
        }
        //if last term, print 
        else
        {
            if(poly.coeff[i] > 1)
            {
                if(poly.exp[i] > 1)
                {
                    cout<<poly.coeff[i]<<"x^"<<poly.exp[i];
                }
                else if(poly.exp[i] == 1)
                {
                    cout<<poly.coeff[i]<<"x";
                }
                else
                {
                    cout<<poly.coeff[i];
                }
            }
            else if(poly.coeff[i] == 1)
            {
                if(poly.exp[i] > 1)
                {
                    cout<<"x^"<<poly.exp[i];
                }
                else if(poly.exp[i] == 1)
                {
                    cout<<"x";
                }
                else
                {
                    cout<<"1";
                }
            }
            else
            {
                cout<<"";
            }
        }
    }
    return cout;
}

int main()
{
	int coeff_P1[] = {1,2,5};	//Coefficients for Polynomial P1
	int exp_P1[] = {4,2,0};	//Exponents for Polynomial P1

	int coeff_P2[] = {4,3};	//Coefficients for Polynomial P2
	int exp_P2[] = {6,2};	//Exponents for Polynomial P2

	Polynomial P1(3, coeff_P1, exp_P1);//Creates P1 with 3 terms (P1 = 1x^4 + 2x^2 + 5x^0 )
	Polynomial P2(2, coeff_P2, exp_P2);//Creates P2 with 2 terms (P2 = 4x^6 + 3x^2)

	cout<<"P1 = "<<P1<<endl; //Prints P1 = x^4+2x^2+5
	cout<<"P2 = "<<P2<<endl; //Prints P2 = 4x^6+3x^2


    if(!P1)
        cout<<"P1 is zero"<<endl;/*if polynomial has only 1 term and its coeff and exp are zero. i.e. if p1 = 0.*/
        
    if(P1 != P2)
        cout<<"P1 is Not Equal to P2"<<endl; 

	Polynomial P3 = P1+P2;	//Adds P1 and P2 and saves result in P3.You may consume extra space for resultant Polynomial in Add function 
	cout<<"P3 = "<<P3<<endl;	//Prints P3 = 4x^6+x^4+5x^2+5

    //fix the assignment operator!!!------------------------------------------------------------------------------
    P3 = 2 + P1; //Assume P1 already has a constant term, add 2 in it. 
    cout<<"P3 = "<<P3<<endl;	
    cout<<++P1<<endl;//adds 1 in all the coefficient.
    cout<<P1<<endl;
    cout<<P1++<<endl; //adds 1 in all the coefficient.
    cout<<P1<<endl;
}

