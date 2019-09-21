#pragma once
class Fibonacci
{
public:
    unsigned long long operator [] (unsigned short n);

private:
    unsigned long long values[93] = { 0 };
};
