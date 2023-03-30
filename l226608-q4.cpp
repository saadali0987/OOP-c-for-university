#include <iostream>
using namespace std;

int main()
{
    int size = 5;
    int *arr = new int[size];
    int count = 0;
    int input;
    while (true) 
    {
        cout << "Enter an integer (-1 to exit): ";
        cin >> input;
        if (input == -1) 
        {
            break;
        }
        if (count == size) 
        {
            int *new_arr = new int[size * 2];
            for (int i = 0; i < size; i++) 
            {
                *(new_arr + i) = *(arr + i);
            }
            delete[] arr;
            arr = new_arr;
            size *= 2;
        }
        arr[count++] = input;
    }

	for(int *ptr = arr + count - 1; ptr >= arr; ptr--)
    {
		cout<<*ptr<<" ";
	}

    delete[] arr;
    return 0;
}
