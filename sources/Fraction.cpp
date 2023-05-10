#include "Fraction.hpp"

using namespace ariel;

Fraction::Fraction() {
    num = 0;
    den = 1;
    frac = (double)num / (double)den;
}

Fraction::Fraction(int number) {
    throw invalid_argument("Invalid input!");
}

Fraction::Fraction(int _num, int _den) {
    if(_den == 0) throw invalid_argument("Divide by 0!!");
    num = _num;
    den = _den;
    frac = (double)num / (double)den;
}

Fraction::Fraction(const Fraction &fraction) {
    num = fraction.getNumerator();
    den = fraction.getDenominator();
    frac = fraction.getFrac();
    reduce();
}

Fraction::Fraction(double fraction) {
    *this = Fraction(convertDoubleToFrac(fraction));
}

Fraction::Fraction(float fraction) {
    *this = Fraction(convertDoubleToFrac((double)fraction));
}

/**************
*Addition start*
***************/

Fraction Fraction::operator+( const Fraction& fraction) const {
    long long num_result = static_cast<long long>(num) * fraction.getDenominator() + static_cast<long long>(fraction.getNumerator()) * den;
    long long den_result = static_cast<long long>(den) * fraction.getDenominator();
    if (num_result > numeric_limits<int>::max() ||
        num_result < numeric_limits<int>::min() ||
        den_result > numeric_limits<int>::max() ||
        den_result < numeric_limits<int>::min()) {
        throw overflow_error("Overflow!");
    }
    Fraction result(0,1);
    if((num < 0 || den < 0) && (fraction.getNumerator() < 0 || fraction.getDenominator() < 0) && !(num < 0 && fraction.getNumerator() < 0)) {
        if(num < 0 && fraction.getDenominator() < 0) 
            result = Fraction(num * abs(fraction.getDenominator()) + fraction.getNumerator() * den, den * fraction.getDenominator());
        else if(den < 0 && fraction.getNumerator() < 0)
            result = Fraction(num * fraction.getDenominator() + abs(fraction.getNumerator()) * den, den * fraction.getDenominator());
        else if(den < 0 && fraction.getDenominator() < 0)
            result = Fraction(num * abs(fraction.getDenominator()) + fraction.getNumerator() * abs(den), abs(den) * fraction.getDenominator());
    }
    else result = Fraction(num * fraction.getDenominator() + fraction.getNumerator() * den, den * fraction.getDenominator());
    result.reduce();
    return result;
}

Fraction Fraction::operator+(int number) const {
    Fraction temp = Fraction(number, 1), result = *this+temp;
    result.reduce();
    return result;
}

Fraction ariel::operator+(int number, const Fraction& fraction) {
    Fraction result = fraction+number;
    result.reduce();
    return result;
}

Fraction Fraction::operator+(double number) const {
    Fraction temp = convertDoubleToFrac(number), result = *this+temp;
    result.reduce();
    return result;
}

Fraction ariel::operator+(double number, const Fraction& fraction) {
    Fraction result = fraction+number;
    result.reduce();
    return result;
}

Fraction Fraction::operator+(float number) const {
    Fraction temp = convertDoubleToFrac((double)number), result = *this+temp;
    result.reduce();
    return result;
}

Fraction ariel::operator+(float number, const Fraction& fraction) {
    Fraction result = fraction+number;
    result.reduce();
    return result;
}

Fraction Fraction::operator++(int n) {
    Fraction temp1 = Fraction(den, den), temp2 = *this;
    *this = Fraction(num + temp1.getDenominator(), den);
    reduce();
    return temp2;
}

Fraction Fraction::operator++() {
    Fraction temp1 = Fraction(den, den);
    *this = Fraction(num + temp1.getDenominator(), den);
    reduce();
    return *this;
}

/*************
*Addition end*
*************/

/*******************
*Substraction start*
*******************/

Fraction Fraction::operator-(const Fraction& fraction) const {
    long long num_result = static_cast<long long>(num) * fraction.getDenominator() - static_cast<long long>(fraction.getNumerator()) * den;
    long long den_result = static_cast<long long>(den) * fraction.getDenominator();
    if (num_result > numeric_limits<int>::max() || num_result < numeric_limits<int>::min() ||
        den_result > numeric_limits<int>::max() || den_result < numeric_limits<int>::min()) {
        throw overflow_error("Overflow!");
    }

    Fraction result = Fraction(num * fraction.getDenominator() - fraction.getNumerator() * den, den * fraction.getDenominator());
    result.reduce();
    return result;
}

Fraction Fraction::operator-(int number) const {
    Fraction temp = Fraction(number, 1), result = *this-temp;
    return result;
}

Fraction ariel::operator-(int number, const Fraction& fraction) {
    Fraction temp = Fraction(number, 1), result = temp-fraction;
    return result;
}

Fraction Fraction::operator-(double number) const {
    Fraction temp = convertDoubleToFrac(number), result = *this-temp;
    return result;
}

Fraction ariel::operator-(double number, const Fraction& fraction) {
    Fraction temp = fraction.convertDoubleToFrac(number), result = temp-fraction;
    result.makeFracShort(result.getFrac());
    return result;
}

Fraction Fraction::operator-(float number) const {
    Fraction temp = convertDoubleToFrac((double)number), result = *this-temp;
    return result;
}

Fraction ariel::operator-(float number, const Fraction& fraction) {
    Fraction temp = fraction.convertDoubleToFrac((double)number), result = temp-fraction;
    return result;
}


Fraction Fraction::operator--(int n) {
    Fraction temp1 = Fraction(den, den), temp2 = *this;
    *this = Fraction(num - temp1.getDenominator(), den);
    reduce();
    return temp2;
}

Fraction Fraction::operator--() {
    Fraction temp1 = Fraction(den, den);
    *this = Fraction(num - temp1.getDenominator(), den);
    reduce();
    return *this;
}

/*****************
*Substraction end*
*****************/

/*********************
*Multiplication start*
*********************/

Fraction Fraction::operator*(const Fraction& fraction) const {
    Fraction This = *this, temp = fraction;
    This.reduce();
    temp.reduce();
    if(temp.getDenominator() == 1 && temp.getNumerator() == 1) return Fraction(This);
    else if(This.getNumerator() == 1 && This.getDenominator() == 1) return Fraction(temp);

    long long num_result = static_cast<long long>(This.getNumerator()) * static_cast<long long>(temp.getNumerator());
    long long den_result = static_cast<long long>(This.getDenominator()) * static_cast<long long>(temp.getDenominator());

    if (num_result > numeric_limits<int>::max() || den_result > numeric_limits<int>::max() 
    || num_result < numeric_limits<int>::min() || den_result < numeric_limits<int>::min()) {
        throw overflow_error("overflow!");
    }
    Fraction result = Fraction(This.getNumerator() * temp.getNumerator(), This.getDenominator() * temp.getDenominator());
    return result;
}

Fraction Fraction::operator*(int number) const {
    Fraction temp = Fraction(number, 1), result = (*this)*temp;
    return result;
}

Fraction ariel::operator*(int number, const Fraction& fraction) {
    Fraction result = fraction*number;
    return result;
}

Fraction Fraction::operator*(double number) const {
    Fraction temp = convertDoubleToFrac(number), result = (*this)*temp;
    return result;
}

Fraction ariel::operator*(double number, const Fraction& fraction) {
    Fraction result = fraction*number;
    return result;
}

Fraction Fraction::operator*(float number) const {
    Fraction temp = convertDoubleToFrac(number), result = (*this)*temp;
    return result;
}

Fraction ariel::operator*(float number, const Fraction& fraction) {
    Fraction result = fraction*number;
    return result;
}

/*******************
*Multiplication end*
*******************/

/***************
*Division start*
***************/


Fraction Fraction::operator/(const Fraction& fraction) const {
    if(fraction.getFrac() == 0.0) throw runtime_error("Divide by 0!!");

    Fraction This = *this, temp = fraction;
    This.reduce();
    temp.reduce();
    if(temp.getDenominator() == 1 && temp.getNumerator() == 1) return Fraction(This);
    else if(This.getNumerator() == 1 && This.getDenominator() == 1) return Fraction(temp.getDenominator(), temp.getNumerator());

    long long num_result = static_cast<long long>(This.getNumerator()) * static_cast<long long>(temp.getDenominator());
    long long den_result = static_cast<long long>(This.getDenominator()) * static_cast<long long>(temp.getNumerator());
    if (num_result > numeric_limits<int>::max() || den_result > numeric_limits<int>::max() 
    || num_result < numeric_limits<int>::min() || den_result < numeric_limits<int>::min()) {
        throw overflow_error("overflow!");
    }
    Fraction result = Fraction(This.getNumerator() * temp.getDenominator(), This.getDenominator() * temp.getNumerator());
    result.reduce();
    return result;
}

Fraction Fraction::operator/(int number) const {
    if(number == 0) throw runtime_error("Divide by 0!!");
    Fraction temp = Fraction(number, 1), result = *this/temp;
    result.reduce();
    return result;
}

Fraction ariel::operator/(int number, const Fraction& fraction) {
    if(fraction.getFrac() == 0.0) throw runtime_error("Divide by 0!!");
    Fraction temp = Fraction(number, 1), result = temp/fraction;
    result.reduce();
    return result;
}

Fraction Fraction::operator/(double number) const {
    if(number == 0.0) throw runtime_error("Divide by 0!!");
    Fraction temp = convertDoubleToFrac(number), result = *this/temp;
    result.reduce();
    return result;
}

Fraction ariel::operator/(double number, const Fraction& fraction) {
    if(fraction.getFrac() == 0.0) throw runtime_error("Divide by 0!!");
    Fraction temp = fraction.convertDoubleToFrac(number), result = temp/fraction;
    result.reduce();
    return result;
}

Fraction Fraction::operator/(float number) const {
    if(number == 0.0) throw runtime_error("Divide by 0!!");
    Fraction temp = convertDoubleToFrac(number), result = *this/temp;
    result.reduce();
    return result;
}

Fraction ariel::operator/(float number, const Fraction& fraction) {
    if(fraction.getFrac() == 0.0) throw runtime_error("Divide by 0!!");
    Fraction temp = fraction.convertDoubleToFrac((double)number), result = temp/fraction;
    result.reduce();
    return result;
}

/*************
*Division end*
*************/

/**************
*Boolean start*
**************/

bool Fraction::operator==(const Fraction& fraction) const {
    return (frac == fraction.getFrac()) || (num == fraction.getNumerator() && den == fraction.getDenominator());
}

bool Fraction::operator==(int number) const {
    Fraction temp = Fraction(number, 1);
    return *this==temp;
}

bool ariel::operator==(int number,const Fraction& fraction) {
    return fraction==number;
}

bool Fraction::operator==(double number) const {
    Fraction temp = convertDoubleToFrac(number);
    return *this==temp;
}

bool ariel::operator==(double number,const Fraction& fraction) {
    return fraction==number;
}

bool Fraction::operator<(const Fraction& fraction) const {
    return frac < fraction.getFrac();
}

bool Fraction::operator<(int number) const {
    Fraction temp = Fraction(number, 1);
    return *this<temp;
}

bool ariel::operator<(int number,const Fraction& fraction) {
    return fraction>number;
}

bool Fraction::operator<(double number) const {
    Fraction temp = convertDoubleToFrac(number);
    return *this<temp;
}

bool ariel::operator<(double number,const Fraction& fraction) {
    return fraction>number;
}

bool Fraction::operator>(const Fraction& fraction) const {
    return fraction<*this;
}

bool Fraction::operator>(int number) const {
    Fraction temp = Fraction(number, 1);
    return *this>temp;
}

bool ariel::operator>(int number,const Fraction& fraction) {
    return fraction<number;
}

bool Fraction::operator>(double number) const {
    Fraction temp = convertDoubleToFrac(number);
    return *this>temp;
}

bool ariel::operator>(double number,const Fraction& fraction) {
    return fraction<number;
}

bool Fraction::operator>=(const Fraction& fraction) const {
    return (*this>fraction) || (*this == fraction);
}

bool Fraction::operator>=(int number) const {
    Fraction temp = Fraction(number, 1);
    return *this>=temp;
}

bool ariel::operator>=(int number,const Fraction& fraction) {
    return fraction<=number;
}

bool Fraction::operator>=(double number) const {
    Fraction temp = convertDoubleToFrac(number);
    return *this>=temp;
}

bool ariel::operator>=(double number,const Fraction& fraction) {
    return fraction<=number;
}

bool Fraction::operator<=(const Fraction& fraction) const {
    return (*this<fraction) || (*this == fraction);
}

bool Fraction::operator<=(int number) const {
    Fraction temp = Fraction(number, 1);
    return *this<=temp;
}

bool ariel::operator<=(int number,const Fraction& fraction) {
    return fraction>=number;
}

bool Fraction::operator<=(double number) const {
    Fraction temp = convertDoubleToFrac(number);
    return *this<=temp;
}

bool ariel::operator<=(double number,const Fraction& fraction) {
    return fraction<=number;
}

/*********************
*Input & Output start*
*********************/

ostream& ariel::operator<<(ostream& outputStream, const Fraction& fraction) {
    Fraction temp(fraction);
    temp.reduce();
    outputStream << temp.getNumerator() << "/" << temp.getDenominator();
    return outputStream;
}

istream& ariel::operator>>(istream& inputStream, Fraction& fraction) {
    string input1, input2;

    inputStream >> input1;
    if(input1.empty()) throw runtime_error("Invalid input");

    if(input1.find('.') != string::npos) { // float or double
        inputStream.ignore(1);
        if(!inputStream.eof()) throw runtime_error("Invalid input"); // float as numerator
        else { // float as fraction
            fraction = Fraction(stof(input1));
            return inputStream;
        }
    } 
    else fraction.num = stoi(input1); // int
    if (inputStream.eof()) throw runtime_error("Invalid input: second input is missing");

    inputStream.ignore(1);
    inputStream >> input2;
    if(input2.find('.') != string::npos) throw runtime_error("Invalid input");
    if(input2.find('0') != string::npos) throw runtime_error("Divide by 0!");
    fraction.den = stoi(input2);

    fraction.reduce();
    return inputStream;
}

/*********************
*Input & Output end*
*********************/

/************************
*Getters and Etc.. start*
************************/

int Fraction::getNumerator() const {
    return num;
}

int Fraction::getDenominator() const {
    return den;
}

double Fraction::getFrac() const {
    return frac;
}

int Fraction::gcd(int a, int b) const {
    if (b == 0) return a;
    return gcd(b, a % b);
}

void Fraction::reduce() {
    if (num == 0) return;
    int numTemp = abs(num), denTemp = abs(den);
    int _gcd = gcd(numTemp, denTemp);

    if(num < 0 && den > 0) {
        num = -1 * (numTemp / _gcd);
        den = denTemp / _gcd;
    }
    else if(num > 0 && den < 0) {
        num = numTemp / _gcd;
        den = -1 * (denTemp / _gcd);
    }
    else {
        num = numTemp / _gcd;
        den = denTemp / _gcd;
    }
    
    makeFracShort((double)num / (double)den);
}

Fraction Fraction::convertDoubleToFrac(double number) const {
    Fraction temp = Fraction(number*pow(10, 3), pow(10, 3));
    temp.reduce();
    return temp;
}

void Fraction::makeFracShort(double fraction) {
    string strFrac = to_string(fraction), result;
    for(unsigned long i = 0; i < strFrac.length(); i++) {
        if(strFrac[i] == '.') {
            int j = 0;
            while(strFrac[i] != '\0' && j <= 3) { //includes '.'
                result += strFrac[i];
                j++;
                i++;
            }
            break;
        }
        result += strFrac[i];
    }
    frac = stod(result);
}



/**********************
*Getters and Etc.. end*
**********************/