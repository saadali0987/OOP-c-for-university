

#include<iostream>
#include<fstream>
using namespace std;


class Helper
{
public:
	static int StringLenght( char* str )
	{
		//Write Yourself
		// This function should return lenght of str
        int length = 0;
        for(int i=0; str[i] != '\0'; i++)
        {
            length++;
        }
        return length;
	}
	static void StringCopy(char*& dest, char*& src){
//Deep Copies src into dest.
        int i=0;
        for(; src[i] != '\0'; i++)
        {
            dest[i] = src[i];
        }
        dest[i] = '\0';
	}
	static char* GetStringFromBuffer(char* str)
	{
		//Write Yourself
		//This function should allocate required memory on heap, 
		//copy string in this memory using StringCopy and return newly created cstring.
        int length = StringLenght(str);
        char* output = new char[length+1];
        
        int i=0;
        for(; str[i] != '\0'; i++)
        {
            output[i] = str[i];
        }
        output[i] = '\0';
        return output;
	}
};

class Car
{
private:
	static int totalCars;	// initialize it to zero yourself
	int model;	
	char* make;
	char* name;
	char* color;
public:
	Car()
	{
		model = 0;
		color = make = name = 0;
		++totalCars;
	}
	//Write Getter of totalCars yourself
    static int GetTotalCars()
    {
        return totalCars;
    }
	
	void ReadDataFromFile(ifstream& fin)
	{
		char temp[20];

		fin>>model;
		fin>>temp;
        
		//This is how we call static functions without object		
		make = Helper::GetStringFromBuffer(temp);
        fin>>temp;
        name = Helper::GetStringFromBuffer(temp);
        fin>>temp;
        color = Helper::GetStringFromBuffer(temp);
		
		//Set rest of the values yourself.
	}
	void PrintListView()
	{
		cout<<model<<" "<<make<<" "<<name<<" "<<color<<endl;
	}
	void PrintDetailView()
	{	
		cout<<"Model:\t"<<model<<endl;
		cout<<"Make:\t"<<make<<endl;
		cout<<"Name:\t"<<name<<endl;
		cout<<"color:\t"<<color<<endl;

	}
	~Car()
	{		
		cout << "Destroying ";
		PrintListView();
		totalCars--;
		delete[] name;
		delete[] make;
		delete[] color;
	}
	void Input()
	{	
        cout<<"enter model\t";
        cin>>model;
        int size;	
        char temp[30];
        char* ptr = temp;
        cout<<"Enter make\t";
        cin>>temp;
        size = Helper::StringLenght(temp);
        make = new char[size+1];
        Helper::StringCopy(make,ptr);
        cout<<"Enter name\t";
        cin>>temp;
        size = Helper::StringLenght(temp);
        name = new char[size+1];
        Helper::StringCopy(name,ptr);
        cout<<"Enter color\t";
        cin>>temp;
        size = Helper::StringLenght(temp);
        color = new char[size+1];
        Helper::StringCopy(color,ptr);
		//Do not consume one extra byte on heap
		//Use only one temp buffer
	}

};


Car* ReadDataFromFile(char* fileName)
{
	ifstream fin;
	int totalCars = 0;
	char buffer[80];

	fin.open(fileName);
	if (fin.is_open())
	{
		fin >> totalCars;
		fin.getline(buffer, 80, '\n');	//We are not saving comment
		Car* carsList = new Car[totalCars];
		int count = 0;
		while (count < 4)
		{
			
			carsList[count].ReadDataFromFile(fin);
			count++;
		}
		return carsList;
	}
	else
	{
		return 0;
	}
}
int Car::totalCars = 0;
int main()
{
	// //Comment all the code. Then uncomment it line by line. 
	// //Implement/add functionality for uncommented line. 
	// //Execute and verify result with output.
    char name[20] = "CarsData.txt";

	Car* carsList = ReadDataFromFile(name);
	int count = 0;
	if (carsList != 0)
	{
		
		count = Car::GetTotalCars();	//Calling static function
		cout << "aTotal Number of Cars in System:\t" << count << endl;
		
		//Test one Print at a time.
		// cout << "\nCars List:\n\n";
		// {
		// 	for (int i = 0; i < count ; i++)
		// 	{				
		// 		carsList[i].PrintListView();
		// 	}			
		// }
		//Comment above printing and Test Printing 2
		cout << "\nCars List:\n\n";
		{
			Car temp = carsList[0];
			temp.PrintListView();
			
			for (int i = 1; i < count ; i++)
			{				
				temp = carsList[i];
				temp.PrintListView();
			}			
		}
		if(carsList)
			delete[] carsList;
	}

	
	cout << "Total Number of Cars in System:\t" << Car::GetTotalCars() << endl << endl << endl;

	Car testCar;	
	testCar.Input(); // Take car data from user
	testCar.PrintDetailView();
		
	cout << "Total Number of Cars in System:\t" << testCar.GetTotalCars() << endl << endl << endl;
}

