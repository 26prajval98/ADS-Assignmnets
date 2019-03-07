#include <iostream>
#include <stdlib.h>
#include <fstream>

using namespace std;

int main()
{
    ofstream file1("tree1.txt"), file2("tree2.txt");
    int r1 = rand() % 100 + 1, r2 = rand() % 100 + 1;

    for (int i = 0; i < r1-1; i++)
        file1 << rand() % 100 << endl;
    file1 << rand() % 100;

    for (int i = 0; i < r2; i++)
        file2 << 100 + rand() % 100 << endl;
    file2 << 100 + rand() % 100;

    file1.close();
    file2.close();
}