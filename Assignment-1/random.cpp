#include <iostream>
#include <stdlib.h>
#include <fstream>

using namespace std;

int main()
{
    int A[200];

    for (int i = 0; i < 200; i++)
    {
        A[i] = 0;
    }

    int val;

    ofstream file1("tree1.txt"), file2("tree2.txt");
    int r1 = rand() % 100 + 1, r2 = rand() % 100 + 1;

    for (int i = 0; i < r1; i++)
    {
        val = rand() % 100;
        if (!A[val - 1])
        {
            A[val - 1] = 1;
            file1 << val << endl;
        }
    }

    for (int i = 0; i < r2; i++)
    {
        val = 100 + rand() % 100;
        if (!A[val - 1])
        {
            A[val - 1] = 1;
            file2 << val << endl;
        }
    }

    file1.close();
    file2.close();
}