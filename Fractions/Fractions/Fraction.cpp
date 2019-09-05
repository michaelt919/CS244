#include <iostream>
#include <fstream>
#include <string>
#include "Fraction.h"

using namespace std;

int Fraction::getNumerator() const
{
    return numerator;
}

void Fraction::setNumerator(
    int numerator)
{
    this->numerator = numerator;
}

int Fraction::getDenominator() const
{
    return denominator;
}

void Fraction::setDenominator(
    int denominator)
{
    if (denominator != 0)
    {
        this->denominator = denominator;
    }
}

void Fraction::multiply(const Fraction& f)
{
    numerator *= f.numerator;
    denominator *= f.denominator;
}

Fraction& Fraction::operator *= (const Fraction& f)
{
    numerator *= f.numerator;
    denominator *= f.denominator;
    return *this;
}

void Fraction::divide(const Fraction& f)
{
    numerator *= f.denominator;
    denominator *= f.numerator;
}

Fraction Fraction::times(const Fraction& f) const
{
    Fraction result;
    result.numerator = numerator * f.numerator;
    result.denominator =
        denominator * f.denominator;
    return result;
}

Fraction Fraction::operator * (const Fraction& f) const
{
    Fraction result;
    result.numerator = numerator * f.numerator;
    result.denominator =
        denominator * f.denominator;
    return result;
}

Fraction Fraction::dividedBy(const Fraction& f) const
{
    // in-class exercise
    throw std::logic_error("dividedBy() is not implemented.");
}

bool Fraction::operator == (const Fraction& f) const
{
    return numerator == f.numerator
        && denominator == f.denominator;
}

double Fraction::toDouble() const
{
    // in-class exercise
    throw std::logic_error("toDouble() is not implemented.");
}

ostream& Fraction::serialize(ostream& out)
{
    out << numerator << " " << denominator;
    return out;
}

istream& Fraction::deserialize(istream& in)
{
    in >> numerator;
    in >> denominator;
    return in;
}

ostream& operator << (ostream& out, const Fraction& f)
{
    out << f.getNumerator() << "/" << f.getDenominator();
    return out;
}

string to_string(const Fraction& f)
{
    return to_string(f.getNumerator()) + "/"
        + to_string(f.getDenominator());
}
