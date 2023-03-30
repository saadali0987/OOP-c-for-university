#include <iostream>
using namespace std;


class MyString
{
	//You can add your code here
	friend ostream& operator<<(ostream&, const MyString&);
	friend istream& operator>>(istream&, MyString&);
private:
	char* str;
	int lenght;	//not including the null char here
	//Add GetStringFromBuffer as static private member (helper)
	//Add Concatenate, CompareString as static private member (helper)
	//You can add your class members here
	static char* toLowerCase(char* string, int size)
	{
    	char* lowerCaseString = new char[size+1];
    
    	int i=0;
    	for(; string[i] != '\0'; i++)
    	{
        	if(string[i] >= 65 && string[i] <= 90)
        	{
            	lowerCaseString[i] = string[i] + 32;
        	}
        	else
        	{
            	lowerCaseString[i] = string[i];
        	}
    	}
    	lowerCaseString[i] = '\0';
    	return lowerCaseString;
	}
public:

	//-------------DO_NOT_CHANGE REGION starts below---------------------
	//Do not change the prototypes given below
	MyString operator+(const MyString);
	MyString& operator=(const MyString&);
	bool operator<(MyString);	//Comparison on the basis of ascii values
	//-------------End of DO_NOT_CHANGE REGION---------------------

	//Add your class members here	
	MyString()
	{
		lenght = 0;
		str = new char[1];
		str[0] = '\0';
	}
	MyString(const MyString& rhs)
	{
		lenght = rhs.lenght;
		str = new char[lenght+1];
		int i=0;
		for(; rhs.str[i] != '\0'; i++)
		{
			str[i] = rhs.str[i];
		}
		str[i] = '\0';
	}


	bool operator!()
	{
		if (lenght == 0)
		{
			return true;
		}
		return false;
	}
	
	void setStr(char* copy)
	{
		delete[] str;
		int count = 0;
		for (int i = 0; copy[i] != '\0'; i++)
		{
			count++;
		}
		str = new char[count + 1];
		lenght = count;

		int i = 0;
		for (; copy[i] != '\0'; i++)
		{
			str[i] = copy[i];
		}
		str[i] = '\0';
	}
	char& operator[](int index)
	{
		return str[index];
	}
	char* operator()(int start, int size)
	{
		char* temp = new char[size];
		int i=0;
		for(; i<size && str[start] != '\0'; i++, start++)
		{
			temp[i] = str[start];
		}
		temp[i] = '\0';

		return temp;
	}

	~MyString()
	{
		delete[] str;
	}
	
};

//--------------------------Add your code here----------------------
ostream& operator<<(ostream& cout, const MyString& str)
{
	cout << str.str;
	return cout;
}
istream& operator>>(istream& cin, MyString& str)
{
	delete[] str.str;
	int count = 0;
	char temp[50];
	cin >> temp;
	for (int i = 0; temp[i] != '\0'; i++)
	{
		count++;
	}
	str.str = new char[count + 1];
	int i = 0;
	for (; temp[i] != '\0'; i++)
	{
		str.str[i] = temp[i];
	}
	str.str[i] = '\0';
	str.lenght = count;
	return cin;
}

MyString& MyString::operator=(const MyString& rhs)
{
	if (this != &rhs)
	{
		lenght = rhs.lenght;
		delete[] str;
		str = new char[lenght + 1];
		int i = 0;
		for (; i < lenght; i++)
		{
			str[i] = rhs.str[i];
		}
		str[i] = '\0';
	}
	return *this;
}

MyString MyString::operator+(const MyString rhs)
{
	int size = lenght + rhs.lenght;
	char* buffer = new char[size + 1];
	int i = 0;
	for (; str[i] != '\0'; i++)
	{
		buffer[i] = str[i];
	}
	for (int j = 0; rhs.str[j] != '\0'; i++, j++)
	{
		buffer[i] = rhs.str[j];
	}
	buffer[i] = '\0';

	MyString temp;
	temp.setStr(buffer);
	return temp;
}
bool MyString::operator < (MyString rhs)
{
	int lengthLHS = 0;
	int lengthRHS = 0;
	for(int i=0; str[i] != '\0'; i++)
	{
		lengthLHS++;
	}
	for(int i=0; rhs.str[i] != '\0'; i++)
	{
		lengthRHS++;
	}
	
	char* lowerCaseLHS = toLowerCase(str, lengthLHS);
	char* lowerCaseRHS = toLowerCase(rhs.str, lengthRHS);

    int i=0;
    int s1 = 0;
    int s2 = 0;
	while(str[i] != '\0' && rhs.str[i] != '\0' && s1 == 0 && s2 == 0 )
	{
		if (lowerCaseLHS[i] > lowerCaseRHS[i])
		{
			s1 = 1;
		}
		else if(lowerCaseRHS[i] > lowerCaseLHS[i])
		{
			s2 = 1;
		}
		i++;
	}

	if(s1 == 1)
	{
		return false;
	}
	else if (s2 == 1)
	{
		return true;
	}
	else if (lengthLHS == lengthRHS && s1 == s2)
	{
		return false;
	}
	else if (lengthLHS > lengthRHS && s1 == s2)
	{
		return false;
	}
	else
	{
		return true;
	}
}





//-------------DO_NOT_CHANGE REGION starts below---------------------
int main()
{
	MyString str1, str2, str3, str4;	//Default constructor will make a string of lenght 0 but having null character (only) i.e. empty string

	if (!str1)
	{
		cout << "String 1 is Empty.\n";
		cout << "Str 1 = " << str1 << endl << endl << endl;
	}

	cout << "Enter String 1:\t";
	cin >> str1;


	cout << "Enter String 2:\t";
	cin >> str2;


	cout << "\n\n\nUser Entered:\n";
	cout << "String 1 = " << str1 << endl;
	cout << "String 2 = " << str2 << endl << endl << endl;

	// //What is following code testing?
	cout << "Before str1 = str1; str1 = " << str1 << endl;
	str1 = str1;
	cout << "After str1 = str1, str1 = " << str1 << endl << endl << endl;


	cout << "Before str4 = str3 = str1+str2\n";
	cout << "str1 = " << str1 << endl;
	cout << "str2 = " << str2 << endl;
	cout << "str3 = " << str3 << endl;
	cout << "str4 = " << str4 << endl;

	str4 = str3 = str1 + str2;


	cout << "\n\n\nAfter str4 = str3 = str1+str2\n";
	cout << "str1 = " << str1 << endl;
	cout << "str2 = " << str2 << endl;
	cout << "str3 = " << str3 << endl;
	cout << "str4 = " << str4 << endl;

	cout<<"\n\n\nEnter String 3:\t";
	cin >> str3;

	cout<<"\n\n\nEnter String 4:\t";
	cin >> str4;
	

	cout<<"\n\n\nstr3 = "<<str3<<endl;
	cout<<"str4 = "<<str4<<endl;

	if(str3 < str4)
		cout<<"String 3 is Less than String 4.\n";
	else
		cout<<"String 3 is NOT Less than String 4.\n";

	MyString str5 = str1 + str2;
	cout << "\n\n\nStr5:\t" << str5 << endl;
	cout << "Str5[7]:\t" << str5[7] << endl; //Function Call: str5.operator[](7).
	str5[7] = '$';

	cout << "\n\nStr5:\t" << str5 << endl;

	cout << "\n\n\nstr5(5, 10):\t" << str5(5, 10) << endl;// Substring of lenght 10 starting from index 5 . Function Call str5.operator()(5,10) Let the returned MyString or char* leak
}



