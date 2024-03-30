#include <iostream>
using namespace std;

const int N = 64, M = 8;
const int HorseSteps[M][2] = {
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
int degree[N][N];
int moves[M][3];

void printMatrix(int matrix[N][N])
{
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout  << matrix[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "_______\n";
}
void generateDegree()
{
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            for(int a = 0; a < M; a++)
            {
                int ni = i + HorseSteps[a][0];
                int nj = j + HorseSteps[a][1];
                
                if(ni >= 0 && ni < N && nj >= 0 && nj < N)
                    degree[i][j]++;
            }
        }
    }
}
void changeDegree(int i, int j)
{
    for(int a = 0; a < M; a++)
    {
        int ni = i + HorseSteps[a][0];
        int nj = j + HorseSteps[a][1];
        
        if(!(ni >= 0 && ni < N && nj >= 0 && nj < N))
            continue;
            
        if(matrix[ni][nj] == 0)
            degree[ni][nj]--; 
    }
}
int giveMoves(int i, int j)
{
    int counter = 0;
    for(int a = 0; a < M; a++)
    {
        int ni = i + HorseSteps[a][0];
        int nj = j + HorseSteps[a][1];
        
        if(!(ni >= 0 && ni < N && nj >= 0 && nj < N))
            continue;
            
        if(matrix[ni][nj] == 0)
        {
            moves[counter][0] = ni;
            moves[counter][1] = nj;
            moves[counter][2] = degree[ni][nj];
            counter++;
        }
    }
    return counter;
}
void findMin(int& i, int& j, int count)
{
    int min = moves[0][2];
    i = moves[0][0];
    j = moves[0][1];
    for(int k = 0; k < count; k++)
    {
        if(min > moves[k][2])
        {
            min = moves[k][2];
            i = moves[k][0];
            j = moves[k][1];
        }
    }
}

bool horseStep(int& i, int& j, int step)
{
    matrix[i][j] = step;
    if(step == N * N)
        return false;
    
    changeDegree(i, j);    
    int count = giveMoves(i, j);
    
    findMin(i, j, count);
    
    return true;
}

int main() {
    generateDegree();
    printMatrix(degree);
    
    int i = 0, j = 0, step = 0;
    while(horseStep(i, j, ++step));
    
    printMatrix(matrix);
    
    return 0;
}