#ifndef FRACTION_H
#define FRACTION_H

#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include "math.h"

using namespace std;

namespace ariel {
    class Fraction {
        private:
        int num, den;
        double frac;

        int gcd(int, int) const;
        void reduce();
        Fraction convertDoubleToFrac(double) const;
        void makeFracShort(double);

        public:
        Fraction();
        Fraction(int);
        Fraction(int, int);
        Fraction(const Fraction&);
        Fraction(double);
        Fraction(float);
        Fraction(Fraction &&) = default;
        Fraction& operator=(const Fraction&) = default;
        Fraction& operator=(Fraction &&) = default;
        ~Fraction() = default;

        // Addition
        Fraction operator+(const Fraction&) const;
        Fraction operator+(int) const;
        friend Fraction operator+(int,const Fraction&);
        Fraction operator+(double) const;
        friend Fraction operator+(double,const Fraction&);
        Fraction operator+(float) const;
        friend Fraction operator+(float,const Fraction&);
        Fraction operator++(int);
        Fraction operator++();

        // Substraction
        Fraction operator-(const Fraction&) const;
        Fraction operator-(int) const;
        friend Fraction operator-(int,const Fraction&);
        Fraction operator-(double) const;
        friend Fraction operator-(double,const Fraction&);
        Fraction operator-(float) const;
        friend Fraction operator-(float,const Fraction&);
        Fraction operator--(int);
        Fraction operator--();

        // Multiplication
        Fraction operator*(const Fraction&) const;
        Fraction operator*(int) const;
        friend Fraction operator*(int,const Fraction&);
        Fraction operator*(double) const;
        friend Fraction operator*(double,const Fraction&);
        Fraction operator*(float) const;
        friend Fraction operator*(float,const Fraction&);

        // Division
        Fraction operator/(const Fraction&) const;
        Fraction operator/(int) const;
        friend Fraction operator/(int,const Fraction&);
        Fraction operator/(double) const;
        friend Fraction operator/(double,const Fraction&);
        Fraction operator/(float) const;
        friend Fraction operator/(float,const Fraction&);

        //Boolean
        bool operator==(const Fraction&) const;
        bool operator==(int) const;
        friend bool operator==(int, const Fraction&);
        bool operator==(double) const;
        friend bool operator==(double, const Fraction&);

        bool operator<(const Fraction&) const;
        bool operator<(int) const;
        friend bool operator<(int,const Fraction&);
        bool operator<(double) const;
        friend bool operator<(double,const Fraction&);

        bool operator>(const Fraction&) const;
        bool operator>(int) const;
        friend bool operator>(int,const Fraction&);
        bool operator>(double) const;
        friend bool operator>(double,const Fraction&);

        bool operator>=(const Fraction&) const;
        bool operator>=(int) const;
        friend bool operator>=(int,const Fraction&);
        bool operator>=(double) const;
        friend bool operator>=(double,const Fraction&);

        bool operator<=(const Fraction&) const;
        bool operator<=(int) const;
        friend bool operator<=(int,const Fraction&);
        bool operator<=(double) const;
        friend bool operator<=(double,const Fraction&);

        // Input & Output
        friend ostream& operator<<(ostream&, const Fraction&);
        friend istream& operator>>(istream&,Fraction&);

        // Getters 
        int getNumerator() const;
        int getDenominator() const;
        double getFrac() const;

    };
}

#endif