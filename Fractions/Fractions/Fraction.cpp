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

// In place fraction multiplication (modifies this Fraction instance)
void Fraction::multiply(const Fraction& f)
{
    numerator *= f.numerator;
    denominator *= f.denominator;
}

// same as Fraction::multiply
Fraction& Fraction::operator *= (const Fraction& f)
{
    numerator *= f.numerator;
    denominator *= f.denominator;
    return *this;
}

// In place fraction division (modifies this Fraction instance)
void Fraction::divide(const Fraction& f)
{
    numerator *= f.denominator;
    denominator *= f.numerator;
}

// Multiply one fraction by another and return the result in another Fraction instance
Fraction Fraction::times(const Fraction& f) const
{
    Fraction result;
    result.numerator = numerator * f.numerator;
    result.denominator =
        denominator * f.denominator;
    return result;
}

// same as Fraction::times
Fraction Fraction::operator * (const Fraction& f) const
{
    Fraction result;
    result.numerator = numerator * f.numerator;
    result.denominator =
        denominator * f.denominator;
    return result;
}

// Divide one fraction by another and return the result in another Fraction instance
Fraction Fraction::dividedBy(const Fraction& f) const
{
    // in-class exercise
	throw std::logic_error("dividedBy() is not implemented.");
}

// Check if two fractions have identical numerator and denominator
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

// Write fraction to a stream, to be read using deserialize()
ostream& Fraction::serialize(ostream& out)
{
    out << numerator << " " << denominator;
    return out;
}

// Read fraction from a stream that was written using serialize()
istream& Fraction::deserialize(istream& in)
{
    in >> numerator;
    in >> denominator;
    return in;
}

// Write the fraction in a human-readable format
ostream& operator << (ostream& out, const Fraction& f)
{
    out << f.getNumerator() << "/" << f.getDenominator();
    return out;
}

// Convert the fraction to a string in a human-readable format
string to_string(const Fraction& f)
{
    return to_string(f.getNumerator()) + "/"
        + to_string(f.getDenominator());
}

// Populate a list of fractions from a file.
// Fractions in the file that exceed the length of the array will be discarded.
void readList(string fileName, Fraction* list,
    int length)
{
    ifstream fileIn;
    fileIn.open(fileName, ios_base::in);
    for (int i = 0; i < length && fileIn; i++)
    {
        list[i].deserialize(fileIn);
    }
}

// Write a list of fractions to a file.
void writeList(string fileName, Fraction* list,
    int length)
{
    // in-class exercise
	throw std::logic_error("writeList() is not implemented.");
}
