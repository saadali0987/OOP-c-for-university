#include <iostream>
#include <fstream>
using namespace std;



class Helper{
    public:
        static int getLength(char* arr)
        {
            int count = 0;
            for(int i=0; arr[i] != '\0'; i++)
            {
                count++;
            }
            return count;
        }
        static void copyString(char* dest, char* src)
        {
            int i=0;
            for(; src[i] != '\0'; i++)
            {
                dest[i] = src[i];
            }
            dest[i] = '\0';
        }
        static void printSymbols(char symbol, int count)
        {
            for(int i=0; i<count; i++)
            {
                cout<<symbol;
            }
        }
        static void printSpaces(int count)
        {
            for(int i=0; i<count; i++)
            {
                cout<<" ";
            }
        }
        static void printSpaces(int count, int number)
        {
            int original = number;
            int digits = 0;
            while(number > 0)
            {
                number = number / 10;
                digits++;
            }
            int space = 0;
            if(original != 0)
                space = count - digits;
            else
                space = count - 1;
            for(int i=0; i<space; i++)
            {
                cout<<" ";
            }
        }
        static void printSpaces(char* arr, char* arr2)
        {
            int l1 = getLength(arr);
            int l2 = getLength(arr2);
            int totalLength = l1 + l2 + 1;
            int space = 22 - totalLength;
            for(int i=0; i<space; i++)
            {
                cout<<" ";
            }
        }
        static void printSpaces(char* arr, char* arr2, int n)
        {
            int l1 = getLength(arr);
            int l2 = getLength(arr2);
            int totalLength = l1 + l2 + 1;
            int space = n - totalLength;
            for(int i=0; i<space; i++)
            {
                cout<<" ";
            }
        }        
        static void printString(char* string)
        {
            for(int i=0; string[i] != '\0'; i++)
            {
                cout<<string[i];
            }
        }
};



class EvalReport
{
    friend void updateStatistics(EvalReport &student);
    friend void printDetailView(EvalReport* result);
    private:
        char rollNo[9];
        char* firstName;
        char* lastName;
        int* qMarks;
        int* aMarks;
        int total;
        static int* Total;
        static int* Mins;
        static int* Max;
        static int* Average;
        static int totalQuizzes;
        static int totalAssignments;

    public:
        EvalReport()
        {
            firstName = 0;
            lastName = 0;
            qMarks = 0;
            aMarks = 0;
            total = 0;
        }
        EvalReport(EvalReport &copy)
        {
            int length = Helper::getLength(copy.firstName);
            firstName = new char[length + 1];
            Helper::copyString(firstName, copy.firstName);
            
            length = Helper::getLength(copy.lastName);
            lastName = new char[length + 1];
            Helper::copyString(lastName, copy.lastName);

            Helper::copyString(rollNo, copy.rollNo);

            qMarks = new int[totalQuizzes];
            for(int i=0; i<totalQuizzes; i++)
            {
                qMarks[i] = copy.qMarks[i];
            }

            aMarks = new int[totalAssignments];
            for(int i=0; i<totalAssignments; i++)
            {
                aMarks[i] = copy.aMarks[i];
            }
            total = copy.total;
        }
        EvalReport& operator=(const EvalReport& copy) 
        {
            if (this == &copy) 
            {
                return *this;
            }

        
            delete[] firstName;
            delete[] lastName;
            delete[] qMarks;
            delete[] aMarks;

        
            total = copy.total;
            int j=0;
            for(; j<8; j++)
            {
                rollNo[j] = copy.rollNo[j];
            }
            rollNo[j] = '\0';

        
            int length = Helper::getLength(copy.firstName);
            firstName = new char[length + 1];
            
            length = Helper::getLength(copy.lastName);
            lastName = new char[length+1];

            qMarks = new int[totalQuizzes];
            aMarks = new int[totalAssignments];

        
            Helper::copyString(firstName, copy.firstName);

            Helper::copyString(lastName, copy.lastName);

            for(int i=0; i<totalQuizzes; i++)
            {
                qMarks[i] = copy.qMarks[i];
            }

            for(int i=0; i<totalAssignments; i++)
            {
                aMarks[i] = copy.aMarks[i];
            }
            return *this;
        }
        ~EvalReport()
        {
            delete[] firstName;
            firstName = 0;
            delete[] lastName;
            lastName = 0;
            delete[] qMarks;
            qMarks = 0;
            delete[] aMarks;
            aMarks = 0;
        }

        void readDataFromFile(fstream &DATA)
        {
            char temp[20];
            DATA>>temp;                                    //getting role number
            Helper::copyString(rollNo, temp);

            DATA>>temp;
            int length = Helper::getLength(temp);
            firstName = new char[length + 1];               //getting firstName
            Helper::copyString(firstName, temp);

            DATA>>temp;
            length = Helper::getLength(temp);
            lastName = new char[length + 1];                 //getting lastName
            Helper::copyString(lastName, temp);

            qMarks = new int[totalQuizzes];                  
            for(int i=0; i<totalQuizzes; i++)
            {
                DATA>>qMarks[i];                              //filling quiz marks array and updating the total marks;
                total = total + qMarks[i];
            }

            aMarks = new int[totalAssignments];
            for(int i=0; i<totalAssignments; i++)
            {
                DATA>>aMarks[i];                               //filling assignment marks array and updating the total marks;
                total = total + aMarks[i];
            }

        }
        int* getQmarks()
        {
            return qMarks;
        }
        int* getAmarks()
        {
            return aMarks;
        }
        static void setTotalQuizzes(int value)
        {
            totalQuizzes = value;
        }
        static void setTotalAssignments(int value)
        {
            totalAssignments = value;
        }
        static int getTotalQuizzes()
        {
            return totalQuizzes;
        }
        static int getTotalAssignments()
        {
            return totalAssignments;
        }
        static void setTotalMarks(int space)
        {
            Total = new int[space];
        }
        static void setTotalMarks(int value, int index)
        {
            Total[index] = value;
        }
        static int* getTotalMarks()
        {
            return Total;
        }
        static void setStatistics()
        {
            Max = new int[totalQuizzes + totalAssignments];
            Mins = new int[totalQuizzes + totalAssignments];
            Average = new int[totalQuizzes + totalAssignments];

            //assigning inital value
            for(int i=0; i<totalQuizzes+totalAssignments; i++)
            {
                Max[i] = 0;           
                Mins[i] = Total[i];
                Average[i] = 0;
            }
        }
        static int* getMax()
        {
            return Max;
        }
        static int* getMin()
        {
            return Mins;
        }
        static void setMax(int value, int index)
        {
            Max[index] = value;
        }
        static void setMin(int value, int index)
        {
            Mins[index] = value;
        }
        static void updateAverage(int value, int index, int count)
        {
            int divisor;
            if(count == 0)     //count of zero means its the first student, hence to calculate average, simply add the student marks 
            {                  // to initial average marks which is 0
                divisor = 1;
            }
            else
            {
                divisor = 2;
            }
            Average[index] = (Average[index] + value) / divisor;
        }
        static int* getAverage()
        {
            return Average;
        }
        char* getRoll()
        {
            return rollNo;
        }
        char* getFirstName()
        {
            return firstName;
        }
        char* getLastName()
        {
            return lastName;
        }
        int getTotal()
        {
            return total;
        }
        void printListView()
        {
            cout<<rollNo;
            Helper::printSpaces(8);

            Helper::printString(firstName);
            cout<<" ";
            Helper::printString(lastName);
            Helper::printSpaces(firstName, lastName);

            for(int j=0; j<totalQuizzes;j++)
            {
                cout<<qMarks[j];
                Helper::printSpaces(10, qMarks[j]);
            }

            for(int j=0; j<totalAssignments;j++)
            {
                cout<<aMarks[j];
                Helper::printSpaces(10, aMarks[j]);
            }

            cout<<total;
            cout<<"\n";
        }
};

int* EvalReport::Total = 0;
int* EvalReport::Mins = 0;
int* EvalReport::Max = 0;
int* EvalReport::Average = 0;
int EvalReport::totalQuizzes = 0;
int EvalReport::totalAssignments = 0;


void updateStatistics(EvalReport &student)
{
    static int count = 0;    //will be used to update average the first time          
    int i=0;     //track min, max, average arrays

    //updating statistics of quizzes
    for(int j=0; j<EvalReport::getTotalQuizzes(); i++, j++)
    {
        if(student.qMarks[j] > EvalReport::getMax()[i])         //checking for max
        {
            EvalReport::setMax(student.qMarks[j], i);       
        }

        if(student.qMarks[j] < EvalReport::getMin()[i])          //checking for min
        {
            EvalReport::setMin(student.qMarks[j], i);
        }
    
        EvalReport::updateAverage(student.qMarks[j], i, count);   //updating average
    }

    //updating statistics of assignments just like above
    for(int j=0; j<EvalReport::getTotalAssignments(); i++, j++)
    {
        if(student.aMarks[j] > EvalReport::getMax()[i])
        {
            EvalReport::setMax(student.aMarks[j], i);
        }

        if(student.aMarks[j] < EvalReport::getMin()[i])
        {
            EvalReport::setMin(student.aMarks[j], i);
        }
        EvalReport::updateAverage(student.aMarks[j],i, count);
    }

    count++;
}
EvalReport* ReadDataFromFile(char* fileName, int &totalStudents)
{
    fstream DATA;
    DATA.open(fileName, ios::in);

    DATA>>totalStudents;
    EvalReport* studentList = new EvalReport[totalStudents];

    int temp;
    DATA>>temp;
    EvalReport::setTotalQuizzes(temp);

    DATA>>temp;
    EvalReport::setTotalAssignments(temp);
    
    EvalReport::setTotalMarks(EvalReport::getTotalQuizzes() + EvalReport::getTotalAssignments());  //allocating space for totalMarks array

    //filling totalMarks array
    for(int i=0; i < EvalReport::getTotalQuizzes() + EvalReport::getTotalAssignments(); i++)
    {
        DATA>>temp;
        EvalReport::setTotalMarks(temp, i);
    }

    EvalReport::setStatistics();  //allocating space for statistics attributes(min, max, average) and initalizing them


    for(int i=0; i<totalStudents; i++)
    {
        studentList[i].readDataFromFile(DATA);   //getting data of student[i];
        updateStatistics(studentList[i]);        //updating statistics(min, max, average)
    }

    DATA.close();
    return studentList;
}

bool search(char* arr, char* keyWord)
{
    int arraySize = Helper::getLength(arr);
    int keyWordSize = Helper::getLength(keyWord);

    for (int i = 0; i <= arraySize - keyWordSize; i++) {
        int j;
        for (j = 0; j < keyWordSize; j++) {
            if (arr[i + j] != keyWord[j])
                break;
        }
        if (j == keyWordSize) {
            return true;
        }
    }
    return false;
}
EvalReport** searchStudentByKeyWord(char* keyWord, int totalStudents, EvalReport* studentList, int &matches)
{
    EvalReport** result = new EvalReport*[50];
    int index = 0;    //keeps track of result index;
    bool continueSearch;
    for(int i=0; i< totalStudents; i++)
    {
        continueSearch = true;
        char* roleNumber = studentList[i].getRoll();
        bool matched = search(roleNumber, keyWord);
        if(matched == true)
        {
            result[index] = new EvalReport();
            result[index] = &studentList[i];
            index++;
            matches++;
            continueSearch = false;
        }

        if(continueSearch == true)
        {
            char* firstName = studentList[i].getFirstName();
            bool matched = search(firstName, keyWord);
            if(matched == true)
            {
                result[index] = new EvalReport();
                result[index] = &studentList[i];
                index++;
                matches++;
                continueSearch = false;
            }
        }
        
        if(continueSearch == true)
        {
            char* lastName = studentList[i].getLastName();
            bool matched = search(lastName, keyWord);
            if(matched == true)
            {
                result[index] = new EvalReport();
                result[index] = &studentList[i];
                index++;
                matches++;
                continueSearch = false;
            }
        }
    }

    EvalReport** temp = new EvalReport*[matches];
    for(int j=0; j<matches; j++)
    {
        temp[j] = result[j];
    }
    delete[] result;
    result = temp;
    //matches = index-1;
    return result;
}
void SortListByTotal(EvalReport* studentList, int totalStudents)
{
    int counter = 0;
    for(int i=0; i<=totalStudents-1;i++)
    {  
        for(int j=0; j<totalStudents -1 - counter; j++)
        {
            if(studentList[j].getTotal() < studentList[j+1].getTotal())
            {
                EvalReport temp = studentList[j];
                studentList[j] = studentList[j+1];
                studentList[j+1] = temp;
            }
        }
        counter++;
    }
}
EvalReport* SearchByRollNumber(EvalReport* studentList, int totalStudents, char* roleNumber)
{
    EvalReport* result = 0;
    bool match = false;
    int i=0;
    for(; i<totalStudents && match == false; i++)
    {
        match = true;
        for(int j=0; j<9; j++)
        {
            if(roleNumber[j] != studentList[i].getRoll()[j])
            {
                match = false;
            }
        }
        if(match == true)
        {
            result = &studentList[i];
        }
    }
    return result;
}

void printCols()
{
    cout<<"Roll No.";
    //Helper::printSpaces(18-8);
    Helper::printSpaces(8);
    cout<<"Name";
    //Helper::printSpaces(22 - 4);
    Helper::printSpaces(18);
    for(int i=0; i < EvalReport::getTotalQuizzes(); i++)
    {
        cout<<"Q"<<i+1;
        Helper::printSpaces(8);
    }
    for(int i=0; i < EvalReport::getTotalAssignments(); i++)
    {
        cout<<"A"<<i+1;
        Helper::printSpaces(8);
    }
    cout<<"Total\n\n";
}

void printStatistics()
{
    //printing statistics data;
    Helper::printSymbols('-', 80);
    cout<<"\n";
    Helper::printSpaces(15);
    for(int i=0; i<EvalReport::getTotalQuizzes(); i++)
    {
        cout<<"Q"<<i+1;
        Helper::printSpaces(5);
    }
    for(int i=0; i<EvalReport::getTotalAssignments(); i++)
    {
        cout<<"A"<<i+1;
        Helper::printSpaces(5);
    }
    cout<<"\n";
    cout<<"Total:";
    Helper::printSpaces(15-6);
    for(int i=0; i<EvalReport::getTotalQuizzes() + EvalReport::getTotalAssignments(); i++)
    {
        cout<<EvalReport::getTotalMarks()[i];
        Helper::printSpaces(7, EvalReport::getTotalMarks()[i]);
    }
    cout<<"\n";

    cout<<"Maximum:";
    Helper::printSpaces(15-8);
    for(int i=0; i<EvalReport::getTotalQuizzes() + EvalReport::getTotalAssignments(); i++)
    {
        cout<<EvalReport::getMax()[i];
        Helper::printSpaces(7, EvalReport::getMax()[i]);
    }
    cout<<"\n";

    cout<<"Minimum:";
    Helper::printSpaces(15-8);
    for(int i=0; i<EvalReport::getTotalQuizzes() + EvalReport::getTotalAssignments(); i++)
    {
        cout<<EvalReport::getMin()[i];
        Helper::printSpaces(7, EvalReport::getMin()[i]);
    }
    cout<<"\n";


    cout<<"Average:";
    Helper::printSpaces(15-8);
    for(int i=0; i<EvalReport::getTotalQuizzes() + EvalReport::getTotalAssignments(); i++)
    {
        cout<<EvalReport::getAverage()[i];
        Helper::printSpaces(7, EvalReport::getAverage()[i]);
    }
    cout<<"\n";
    Helper::printSymbols('-', 80);
    cout<<"\n";
}

void printDetailView(EvalReport* result)
{
    cout<<"Roll No:";
    Helper::printSpaces(5);
    cout<<result->rollNo;

    cout<<"\nFull Name:";
    Helper::printSpaces(result->firstName, result->lastName, 13);
    cout<<result->firstName<<" "<<result->lastName<<"\n\n";

    
    cout<<"\nQuizzez:\n";
    Helper::printSpaces(8);
    cout<<"Total";
    Helper::printSpaces(6);
    cout<<"Obtained Marks";
    Helper::printSpaces(6);
    cout<<"Average";
    Helper::printSpaces(6);
    cout<<"Minimum";
    Helper::printSpaces(6);
    cout<<"Maximum\n";

    int i=0;
    for(; i<result->totalAssignments; i++)
    {
        cout<<"A"<<i+1;
        Helper::printSpaces(6);
        cout<<result->Total[i];
        Helper::printSpaces(12, result->Total[i]);
        cout<<result->qMarks[i];

        Helper::printSpaces(20 , result->qMarks[i]);
        cout<<result->Average[i];

        Helper::printSpaces(13, result->Average[i] );
        cout<<result->Mins[i];

        Helper::printSpaces(13, result->Mins[i]);
        cout<<result->Max[i];
        cout<<"\n";
    }
    
    cout<<"\nAssignemnts:\n";
    Helper::printSpaces(8);
    cout<<"Total";
    Helper::printSpaces(6);
    cout<<"Obtained Marks";
    Helper::printSpaces(6);
    cout<<"Average";
    Helper::printSpaces(6);
    cout<<"Minimum";
    Helper::printSpaces(6);
    cout<<"Maximum\n";
    int j=0;
    for(; j<result->totalAssignments; i++, j++)
    {
        cout<<"Q"<<i-3;
        Helper::printSpaces(6);
        cout<<result->Total[i];
        Helper::printSpaces(12, result->Total[i]);
        cout<<result->aMarks[j];

        Helper::printSpaces(20 , result->aMarks[j]);
        cout<<result->Average[i];

        Helper::printSpaces(13, result->Average[i] );
        cout<<result->Mins[i];

        Helper::printSpaces(13, result->Mins[i]);
        cout<<result->Max[i];
        cout<<"\n";
    }
    
}


int main()
{
    char fileName[25] = "gradeSheet.txt";
    int totalStudents;
    EvalReport* studentList = 0;
    studentList = ReadDataFromFile(fileName, totalStudents);
    //printAll(studentList, totalStudents);

    
    printStatistics();
    printCols();
    for(int i=0; i<totalStudents; i++)
    {
        studentList[i].printListView();
    }


    char keyword[10] = "Ali";
    int matches = 0;
    EvalReport** result = searchStudentByKeyWord(keyword, totalStudents, studentList, matches);
    Helper::printSymbols('-', 75);
    cout<<"\nSearch: "<<keyword<<"\n";
    if(matches > 0)
    {
        printCols();
        for(int i=0; i<matches; i++)
        {
            result[i]->printListView();
        }
    }
    else
    {
        cout<<"No matches found for: "<<keyword<<"\n";
    }



    SortListByTotal(studentList, totalStudents);
    cout<<"\n\nSorted by total marks:\n";
    //printAll(studentList, totalStudents);
    for(int i=0; i<totalStudents; i++)
    {
        studentList[i].printListView();
    }

    
    Helper::printSymbols('-', 75);
    cout<<"\nSearch by role number:  15L-4265\n";
    char roll[9] = "15L-4265";
    EvalReport* searchResult = SearchByRollNumber(studentList, totalStudents, roll); 
    if(searchResult != 0)
    {
        printDetailView(searchResult);
    }
    else
    {
        cout<<"No match found for Roll Number: "<<roll;
    }

    if(studentList)
        delete[] studentList;
    
    
}
