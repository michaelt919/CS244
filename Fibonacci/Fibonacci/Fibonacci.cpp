#include "Fibonacci.h"
#include "Fibonacci.h"
#include <stdexcept>
using namespace std;

//// Recursive without memoization
//unsigned long long Fibonacci::operator [] (unsigned short n)
//{
//    if (n == 0 || n == 1)
//    {
//        return n;
//    }
//    else
//    {
//        return operator[](n - 1) + operator[](n - 2);
//    }
//}

//// Recursive with memoization
//unsigned long long Fibonacci::operator [] (unsigned short n)
//{
//    if (n >= 93)
//    {
//        throw out_of_range(
//            "n must be less than 93.");
//    }
//    else if (n == 0 || n == 1)
//    {
//        return n;
//    }
//    else if (values[n] == 0)
//    {
//        values[n] = operator[](n - 1)
//            + operator[](n - 2);
//        return values[n];
//    }
//    else
//    {
//        return values[n];
//    }
//}

// Iterative
unsigned long long Fibonacci::operator[] (unsigned short n)
{
    if (n >= 93)
    {
        throw out_of_range(
            "n must be less than 93.");
    }
    else if (n == 0 || n == 1)
    {
        return n;
    }
    else
    {
        values[0] = 0;
        values[1] = 1;
        for (int i = 2; i <= n; i++)
        {
            values[i] = values[i - 1] + values[i - 2];
        }
        return values[n];
    }
}
