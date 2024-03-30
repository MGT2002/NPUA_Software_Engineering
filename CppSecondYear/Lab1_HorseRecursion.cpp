#include <iostream>
using namespace std;

const int N = 8;
const int HorseSteps[8][2] = {
    {2, -1},
    {2, 1},
    {1, -2},
    {-1, -2},
    {1, 2},
    {-2, 1},
    {-1, 2},
    {-2, -1},
};
int matrix[N][N];

void printMatrix()
{
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout  << matrix[i][j] << ", ";
        }
        cout << "\n";
    }
    cout << "_______\n";
}
// true - if cell has found, false if has not
bool findEmptyCell(int* i, int* j, int* option)
{
    for(int a = *option; a < N; a++)
    {
        int ni = *i + HorseSteps[a][0];
        int nj = *j + HorseSteps[a][1];
        
        if(!(ni >= 0 && ni < N && nj >= 0 && nj < N))
            continue;
            
        if(matrix[ni][nj] == 0)
        {
            //Empty
            *i = ni;
            *j = nj;
            *option = a + 1;
            return true;
        }
    }
    *option = N;
    return false;
}
bool horseStep(int i, int j, int step)
{
    matrix[i][j] = step;
    if(step == 64)
        return true;
        
    int option = 0;
    
    while(option < N)
    {
        int ni = i, nj = j;
        if(findEmptyCell(&ni, &nj, &option))
        {
            if(horseStep(ni, nj, step + 1))
                return true;
        }
        else
        {
            matrix[i][j] = 0;
            break;
        }
    }
    matrix[i][j] = 0;
    return false;
}

int main() {
    horseStep(0, 0, 1);
    printMatrix();
    
    return 0;
}