#include <iostream>
using namespace std;


int **getArray(int N)
{
    int **arr = new int *[N];
    for (int i = 0; i < N; ++i)
    {
        arr[i] = new int[N];
        for (int j = 0; j < N; ++j)
        {
            arr[i][j] = 0;
        }
    }
    return arr;
}


void eraseArr(int **arr){
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            arr[i][j] = 0;
        }
       
    } 
}

void printArr(int **arr, int N)
{

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            cout << arr[i][j];
        }
        cout << endl;
    }
}


void mergeAttackBoards(int **a, int **b)
{
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
           
            a[i][j] += b[i][j];
        }
    }
}