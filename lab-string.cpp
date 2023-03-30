#include <iostream>
#include <fstream>
using namespace std;

//sorry for the late submission. I kept getting errors and I didn't wanna copy from anyone so it took me a while to figure out the solution

int StringLenght(char* sentence);
char** ReadStudentsListFromFile(fstream &DATA, int &size);
void copyString(char arr[], char temp[]);
void PrintAllNames(char** studentsList, int& size);
int GetCharacterCount(char* myString, char c);

int main()
{
	fstream DATA;
	DATA.open("StudentsList.txt", ios::in);
	int size = 0;
	char** studentsList = ReadStudentsListFromFile(DATA, size);
	PrintAllNames(studentsList, size);

	system("pause");
}


int StringLenght(char* sentence)
{
	int count = 0;
	for(int i = 0; sentence[i] != '\0'; i++)
	{
		count++;
	}
	return count;
}

int GetCharacterCount(char* myString, char c)
{
	int count =0; 
	for(int i=0; myString[i] != '\0'; i++)
	{
		if(myString[i] == c)
		{
			count++;
		}
	}
	return count;
}


void copyString(char arr[], char temp[])
{
	int i;
	for (i = 0; temp[i] != '\0'; i++)
	{
		//arr[i] = temp[i];
		*(arr + i) = *(temp + i);
	}
	*(arr + i) = '\0';
}

char** ReadStudentsListFromFile(fstream &DATA, int &size)
{
	DATA>>size;
	char** list = new char*[size];
	char* temp = new char[50];

	for(int i=0; i<=size; i++)
	{
			DATA.getline(temp, 50);
			if(i != 0)
			{
				int length = StringLenght(temp);
				length++;
				//list[i-1] = new char[length];
				*(list + i -1) = new char[length];
				copyString(*(list + i -1), temp);
			}
	}
	delete[] temp;
	temp = 0;
	return list;
}

void PrintAllNames(char** studentsList, int& size)
{
	for(int i = 0; i<size; i++)
	{
		cout<<*(studentsList + i)<<endl;
	}
}