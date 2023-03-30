#include <iostream>
using namespace std;



class Date
{
    private:
        int day;
        int month;
        int year;

    public:
        Date()
        {
            day = 1;
            month = 1;
            year = 1926;
            cout<<"default constructor called\n";
        }
        Date(int d, int m, int y)
        {
            day = d;
            month = m;
            year = y;
            cout<<"overloaded constructor called\n";
        }
        ~Date()
        {
            cout<<"destructor called\n";
        }
        void Print()
        {
            cout<<day<<"/"<<month<<"/"<<year<<endl;
        }
        void Input()
        {
            cin>>day;
            cin>>month;
            cin>>year;
        }
        void setDay(int d)
        {
            day = d;
        }
        void setMonth(int m)
        {
            month = m;
        }
        void setYear(int y)
        {
            year = y;
        }
        int getDay()
        {
            return day;
        }
        int getMonth()
        {
            return month;
        }
        int getYear()
        {
            return year;
        }
        int Compare(Date d2)
        {
            if(year > d2.year)
                return 1;
            else if(month > d2.month)
                return 1;
            else if(day > d2.day)
                return 1;
            else
                return -1;
        }
        Date incrementMonth()
        {
            if(month == 12)
            {
                return Date(day, 1, year+1);

            }
            return Date(day, month+1, year);
        }
};


int main()
{
    Date date1;
    date1.Print();
    date1.Input();
    date1.Print();
    Date independenceDay(14, 8, 1947);
    independenceDay.Print();
    
    Date xmasDay;
    xmasDay.Print();
    xmasDay.setDay(25);
    xmasDay.setMonth(12);
    xmasDay.setYear(2018);
    // cout<<xmasDay.getDay()<<"/"<<xmasDay.getMonth()<<"/"<<xmasDay.getYear()<<endl;

    // Date temp;
    // temp = xmasDay;
    // temp.Print();
    cout<<xmasDay.Compare(independenceDay)<<endl;
    Date d2 = date1.incrementMonth();
    d2.Print();


}