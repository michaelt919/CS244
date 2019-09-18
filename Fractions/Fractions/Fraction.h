#pragma once
#include <iostream>

class Fraction
{
public:
    int getNumerator() const;
    void setNumerator(int denominator);

    int getDenominator() const;
    void setDenominator(int denominator);

    // Multiply one fraction by another and return the result in another Fraction instance
    Fraction times(const Fraction& f) const;
    
    // Divide one fraction by another and return the result in another Fraction instance
    Fraction dividedBy(const Fraction& f) const;

    // Convert Fraction to the nearest double approximation.
    double toDouble() const;

    // In place fraction multiplication (modifies this Fraction instance)
    void multiply(const Fraction& f);

    // In place fraction division (modifies this Fraction instance)
    void divide(const Fraction& f);

    // Multiply one fraction by another and return the result in another Fraction instance;
    // same as Fraction::times
    Fraction operator * (const Fraction& f) const;

    // In place fraction multiplication (modifies this Fraction instance);
    // same as Fraction::multiply
    Fraction& operator *= (const Fraction& f);

    // Check if two fractions have identical numerator and denominator
    bool operator == (const Fraction& f) const;

    // Write fraction to a stream, to be read using deserialize()
    std::ostream& serialize(std::ostream& out);

    // Read fraction from a stream that was written using serialize()
    std::istream& deserialize(std::istream& in);

private:
    int numerator = 0;
    int denominator = 1;
};

// Write the fraction in a human-readable format
std::ostream& operator << (std::ostream& out, const Fraction& f);

// Convert the fraction to a string in a human-readable format
std::string to_string(const Fraction& f);