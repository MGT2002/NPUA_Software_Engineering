#include <iostream>
using namespace std;

void PrintArray(int* arr, int length)
{
    cout << "{ ";
    for(int i = 0; i < length; i++)
    {
        cout <<*(arr+i) <<" ";   
    }
    cout << "}" << endl;
}

int* InputArray(int& length)
{
    int n;
    cout << "arr.length = ";
    cin >> n;
    
    int* arr = new int[n];
    
    for(int i = 0 ; i < n; i++)
    {
        cout << "arr[" << i << "] = ";
        cin >> *(arr + i);
    }
    
    length = n;
    return arr;
}

int* GetIndexesOfAdders(int* arr, int length, int sum)
{
    for(int i = 0; i < length; i++)
    {
        int adder1 = *(arr + i);
        for(int j = i + 1; j < length; j++)
        {
            int adder2 = *(arr + j);
            
            if(adder1 + adder2 == sum)
            {
                return new int[2]{i, j};
            }
        }
    }
    
    return new int[2]{-1, -1};
}

int main()
{
    int n;
    int* arr = InputArray(n);
    PrintArray(arr, n);
    int m;
    cout << "m = ";
    cin >> m;
    
    int* result = GetIndexesOfAdders(arr, 4, m);
    cout << result[0] << ", " << result[1];
    
    delete result;
    return 0;
}
//input 4 2 7 11 15 9