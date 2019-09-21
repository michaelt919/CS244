#include <iostream>
#include "Fibonacci.h"
using namespace std;

int main()
{
    Fibonacci f;
    for (int i = 0; i < 93; i++)
    {
        cout << f[i] << '\n';
    }

    system("pause");
    return 0;
}