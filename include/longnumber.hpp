#pragma once
#ifndef LONGNUMBER_HPP
#define LONGNUMBER_HPP

#include <vector>
#include <string>

class LongNum {
private:
    std::vector<int> digits;
    int exp;
    int base;
    static int precisionMax;
    bool isNegative;
    void normalize();
    LongNum(std::string number, int base);
public:
    LongNum();
    LongNum(LongNum const& other);
    LongNum(int number);
    LongNum(long long number);
    LongNum(unsigned int number);
    LongNum(unsigned long long number);
    LongNum(double number);
    LongNum(long double number);
    LongNum(std::string number);

    LongNum& operator=(const LongNum& other);

    friend LongNum operator+(const LongNum& left, const LongNum& right);
    friend LongNum operator-(const LongNum& left, const LongNum& right);
    friend LongNum operator*(const LongNum& left, const LongNum& right);
    friend LongNum operator/(const LongNum& left, const LongNum& right);

    friend bool operator==(const LongNum& left, const LongNum& right);
    friend bool operator!=(const LongNum& left, const LongNum& right);
    friend bool operator<(const LongNum& left, const LongNum& right);
    friend bool operator>(const LongNum& left, const LongNum& right);
    friend bool operator<=(const LongNum& left, const LongNum& right);
    friend bool operator>=(const LongNum& left, const LongNum& right);

    friend LongNum abs(LongNum);
    friend LongNum del_exp(LongNum);

    static void setPrecision(int prec);
    LongNum inverse() const;
    std::string toString() const;
};
LongNum operator ""_longnum(long double number);
#endif