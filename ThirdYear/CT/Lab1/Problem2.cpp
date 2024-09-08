#include <iostream>
using namespace std;

void PrintArray(int* arr, int length){
    cout << "{ ";
    for(int i = 0; i < length; i++)
    {
        cout <<*(arr+i) <<" ";   
    }
    cout << "}" << endl;
}

void PrintMatrix(int** matrix, int rows, int cols) {
    std::cout << "[" << std::endl;
    for (int i = 0; i < rows; i++) {
        std::cout << "  ";
        for (int j = 0; j < cols; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "]" << std::endl;
}

int* InputArray(int& length){
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

int** InputMatrix(int& rows, int& cols) {
    std::cout << "Number of rows: ";
    std::cin >> rows;

    std::cout << "Number of columns: ";
    std::cin >> cols;

    int** matrix = new int*[rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[cols];
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << "matrix[" << i << "][" << j << "] = ";
            std::cin >> matrix[i][j];
        }
    }

    return matrix;
}

void Swap(int& a, int& b)// Safe way if a is b
{
    int t = a;
    a = b;
    b = t;
}

void MakeTranspose(int** matrix, int n)
{
    for(int i = 1; i < n; i++)
    {
        for(int j = 0; j < i; j++)
        {
            Swap(matrix[i][j], matrix[j][i]);
        }
    }
}

void ReverseRows(int** matrix, int rows, int cols)
{
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols / 2; j++)
        {
            Swap(matrix[i][j], matrix[i][cols - 1 - j]);
        }
    }
}

void Rotate90Degree(int** matrix, int n)
{
    MakeTranspose(matrix, n);
    ReverseRows(matrix, n, n);
}

int main()
{
    int n;
    int** matrix = InputMatrix(n, n);
    PrintMatrix(matrix, n, n);
    
    Rotate90Degree(matrix, n);
    PrintMatrix(matrix, n, n);
    
    return 0;
}