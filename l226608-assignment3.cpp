#include <iostream>
#include <fstream>
using namespace std;

//main function:
void StringConcatenate(char* &string1, char* string2);
char** StringTokens(char* string);
char** inverseStringTokens(char* string);
char* ReverseSentence(char* string);
int CompareString(char* string1, char* string2);
void sortedStudentNames(fstream &DATA);


//helper functions:
int stringLength(char* string);
int getNumberOfWords(char* string);
void copyString(char* string, char* copy, int start, int end);
void copyString(char* string, char* copy);
void output(char** string, int numOfWords);
void deallocate(char** string, int size);
char* toLowerCase(char* string, int size);
char* bubbleSort(char** string1, int size);
void DisplayStringList(char** list, int size);
char* input(fstream& DATA);




int main()
{
    fstream DATA;
    DATA.open("stringData.txt", ios::in);
    char* string1Ptr = 0;
    char* string2Ptr = 0;
    string1Ptr = input(DATA);
    string2Ptr = input(DATA);
    cout<<"\n\n\n";

    
    //string concatenation
    cout<<"Testing string concatenation\n\n";
    cout<<"string1:\t"<<string1Ptr<<"\n";
    cout<<"string2:\t"<<string2Ptr<<"\n";
    StringConcatenate(string1Ptr, string2Ptr);
    cout<<"After concatenation:\n";
    cout<<"string1:\t"<<string1Ptr<<"\n";
    cout<<"string2:\t"<<string2Ptr<<"\n";
    delete[] string2Ptr;
    string2Ptr = 0;
    cout<<"-------------------------------------------\n";

    //String tokens
    cout<<"Testing string tokens\n";
    int size = getNumberOfWords(string1Ptr);
    char** listOfWords = StringTokens(string1Ptr);
    cout<<"Tokens of String 1 are as follows:\n";
    output(listOfWords, size);
    deallocate(listOfWords, size);
    listOfWords = 0;
    cout<<"--------------------------------------------\n";

    //Inverse string tokens
    cout<<"Testing InverseStringTokens:\n";
    char** reversedListOfWords = inverseStringTokens(string1Ptr);
    cout<<"Tokens of the string in reverse order are as follows:\n";
    output(reversedListOfWords, 8);
    deallocate(reversedListOfWords, 8);
    reversedListOfWords = 0;
    cout<<"---------------------------------------------\n";

    //Reverse Sentence
    cout<<"Testing reverse sentence\n";
    char* reverse = ReverseSentence(string1Ptr);
    cout<<"original string1:\t"<<string1Ptr<<"\n";
    cout<<"reversed string1:\t"<<reverse<<"\n";
    cout<<"-----------------------------------------------\n";


    //sorted student list
    sortedStudentNames(DATA);
    

    delete[] string1Ptr;
    string1Ptr = 0;
    DATA.close();
}
























char* input(fstream& DATA)
{
    char buffer[80];
    DATA.getline(buffer, 80);
    int length = stringLength(buffer);
    char* input = new char[length];
    int i =0;
    for(; i<length-1;i++)
    {
        input[i] = buffer[i];
    }
    input[i] = '\0';
    return input;
}

int stringLength(char* string){
    int count = 0;
    for(int i=0; string[i] != '\0'; i++)
    {
        count++;
    }
    count++;
    return count;
}


void StringConcatenate(char* &string1Ptr, char* string2Ptr)
{
    //note: the length includes the space for null terminating character!
    int string1Length = stringLength(string1Ptr);
    int string2Length = stringLength(string2Ptr);


    char* concat = new char[string1Length + string2Length];
    char* temp = concat;
    //copying first sentence into concat

    if(string1Length != 1)     //length of 1 means just a null character so no need to copy, it would just add an extra space
    {
        for(int i=0; string1Ptr[i] != '\0'; i++)
        {
            *temp = string1Ptr[i];
            *temp++;
        }
        *temp = ' ';
        *temp++;
    }
    
    //copying second sentence into concat
    for(int i=0; string2Ptr[i] != '\0'; i++)
    {
        *temp = string2Ptr[i];
        *temp++;
    }
    *temp = '\0';

    string1Ptr = concat;
    //deallocation
    concat = 0;
    temp = 0;
}  

int getNumberOfWords(char* string)
{
    int words = 0;
    for(int i=0; string[i] != '\0'; i++)
    {
        if(string[i] == ' ')
        {
            words++;
        }
    }
    words++;
    return words;
}

void copyString(char* string, char* copy, int start, int end)
{
    int i = start;
    int j= 0;
    for(; i<end;start++, j++, i++)
    {
        string[j] = copy[i];
    }
    string[j] = '\0';
}


char** StringTokens(char* string)
{
    int size = getNumberOfWords(string);
    char** stringTokens = new char*[size];
    //m and n are indexes. m stays at the start of each word as n iterates over every letter of the word untill it reaches a space character. The size of the word is then calculated using n-m and the values of m and n are used to copy every word into stringTokens[k].
    int m = 0;
    int n = 0;
    int k = 0;   //to iterate stringTokens
    for(int i=0; string[i] != '\0'; i++)
    {
        if(string[i] == ' ')
        {
            int wordLength = (n-m) + 1;           // + 1 to accomodate for null character
            stringTokens[k] = new char[wordLength];
            copyString(stringTokens[k], string, m, n);
            k++;      
            n++;
            m = n;
        }else{
            n++;
        }
    }
    //the above loop will take care of every word except the last one because it ends with null character and not space so we have to take care of it explicitly
    int length = (n-m) + 1;
    stringTokens[k] = new char[length];
    copyString(stringTokens[k], string, m, n);

    return stringTokens;
}

void output(char** string, int numOfWords)
{
    for(int i=0; i<numOfWords; i++)
    {
        cout<<string[i]<<endl;
    }
}

void deallocate(char** string, int size)
{
    for(int i=0; i<size;i++)
    {
        delete[] string[i];
    }
    delete[] string;
}

char** inverseStringTokens(char* string)
{
    //getting the list of words from StringTokens function
    int size = getNumberOfWords(string);
    char** wordList = StringTokens(string);

    //allocating space for reversed list of the same size;
    char** reversedWordList = new char*[size];

    int wordListIndex = size-1;          //-1 because it is the last index;
    int length;
    //in this loop, first it gets length of word from wordList starting from last index, then it makes space at reversedWordList[i] of that length, and finally copies the word into it
    for(int i=0; i<size;i++)
    {
        length = stringLength(wordList[wordListIndex]);
        reversedWordList[i] = new char[length];
        copyString(reversedWordList[i], wordList[wordListIndex]);
        wordListIndex--;
    }

    deallocate(wordList, size);
    delete[] wordList;
    wordList = 0;
    return reversedWordList;
}

void copyString(char* string, char* copy)
{
    int i=0;
    for(; copy[i] != '\0'; i++)
    {
        string[i] = copy[i];
    }
    string[i] = '\0';
}

char* ReverseSentence(char* string)
{
    //getting the inversed list of words from inverseStringTokens function
    int size = getNumberOfWords(string);
    char** inverseWordList = inverseStringTokens(string);

    //get the length of each word and add it to get the length of the reversed sentence
    //note: stringLength function always give 1 more than actual length so spaces and null character are being taken care of already
    int length = 0;
    for(int i=0; i < size; i++)
    {
        length = length + stringLength(inverseWordList[i]);
    }

    char* reversedSentence = new char[length];
    reversedSentence[0] = '\0';          //to prevent garbage from showing up

    //concatenate each word from the inverseWordList to reversedSentence
    for(int i=0; i<size; i++)
    {
        StringConcatenate(reversedSentence, inverseWordList[i]);
    }

    deallocate(inverseWordList, size);
    inverseWordList = 0;
    return reversedSentence;
}


char* toLowerCase(char* string, int size)
{
    char* lowerCaseString = new char[size];
    
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
    lowerCaseString[size - 1] = '\0';
    return lowerCaseString;
}


int CompareString(char* string1, char* string2)
{
    int string1Length = stringLength(string1);
    int string2Length = stringLength(string2);


    char* lowerCaseString1 = toLowerCase(string1, string1Length);
    char* lowerCaseString2 = toLowerCase(string2, string2Length);

    int i=0;
    int s1 = 0;
    int s2 = 0;
    while(lowerCaseString1[i] != '\0' && lowerCaseString2[i] != '\0' && s1 == 0 && s2 == 0 )
    {
        if (lowerCaseString1[i] > lowerCaseString2[i])
        {
            s1 = 1;
        }
        else if(lowerCaseString2[i] > lowerCaseString1[i])
        {
            s2 = 1;
        }
        i++;
    }

    if(s1 == 1)
    {
        return 1;
    }
    else if (s2 == 1)
    {
        return -1;
    }
    else if (string1Length == string2Length && s1 == s2)
    {
        return 0;
    }
    else if (string1Length > string2Length && s1 == s2)
    {
        return 1;
    }
    else
    {
        return -1;
    }
}

void sortedStudentNames(fstream &DATA)
{
    int size; 
    DATA>>size;
    DATA.ignore();
    // char junk[90];
    // DATA.getline(junk, 90);
    char name[20];                   //acts as buffer to get each name
    char** listOfNames = new char*[size];

    //reading names from file to listOfNames
    int i=0;
    for(; i<size; i++)
    {
        DATA.getline(name, 20);
        int length = stringLength(name);               
        listOfNames[i] = new char[length];
        copyString(listOfNames[i], name);
    }

    cout<<"list of names before sorting:\n";
    DisplayStringList(listOfNames, size);
    bubbleSort(listOfNames, size);
    cout<<"---------------------\n";
    cout<<"List of names after sorting: \n";
    cout<<"---------------------\n";
    DisplayStringList(listOfNames, size);
}


char* bubbleSort(char** list, int size)
{
    int counter = 0;
    for(int i=0; i<=size-1;i++)
    {  
        for(int j=0; j<size -1 - counter; j++)
        {
            int compare = CompareString(list[j], list[j+1]);
            if(compare == 1)
            {
                char* temp = list[j];
                list[j] = list[j+1];
                list[j+1] = temp;
            }
        }
        counter++;
    }
}

void DisplayStringList(char** list, int size)
{
    for(int i=0; i<size; i++)
    {
        cout<<list[i]<<endl;
    }
}


    