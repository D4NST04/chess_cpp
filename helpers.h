//generates empty array.
int **getArray(int N);
//prints NxN array, used to display board when debugging.
void printArr(int **arr, int N);
//helps create attack boards.
void mergeAttackBoards(int **a, int **b);

//fills with 0.
void eraseArr(int** arr);
