#include "longnumber.hpp"
#include <algorithm>
#include <iostream>

int LongNum::precisionMax = 1000;

LongNum::LongNum() : isNegative(false), exp(1), digits(std::vector<int>(1, 0)), base(2) {}
LongNum::LongNum(const LongNum& other) : isNegative(other.isNegative), digits(other.digits), exp(other.exp), base(other.base) {}
LongNum::LongNum(int number) : LongNum((long long)number) {}
LongNum::LongNum(long long number) {
    isNegative = false;
    exp = 0;
    base = 2;
    if (number < 0) {
        isNegative = true;
    }
    do {
        digits.push_back(number % base);
        number = number / base;
    } while (number != 0);
    std::reverse(digits.begin(), digits.end());
    exp += digits.size();
    this->normalize();
}
LongNum::LongNum(unsigned int number) : LongNum((unsigned long long)number) {}
LongNum::LongNum(unsigned long long number) {
    isNegative = false;
    exp = 0;
    base = 2;
    do {
        digits.push_back(number % base);
        number = number / base;
    } while (number != 0);
    std::reverse(digits.begin(), digits.end());
    exp += digits.size();
    this->normalize();
}
LongNum::LongNum(double number) : LongNum(std::to_string(number)) {}
LongNum::LongNum(long double number) : LongNum(std::to_string(number)) {}

LongNum::LongNum(std::string number) {
    isNegative = false;
    exp = 0;
    base = 2;
    if (number[0] == '-') {
        isNegative = true;
    }
    LongNum num(number, 10);
    num = abs(num);
    LongNum integer = del_exp(num);
    LongNum integer2 = integer;
    LongNum bas(std::to_string(base), 10);
    LongNum zero("0", 10);
    do {
        if (integer.exp > integer.digits.size()) {
            digits.push_back(0);
        } else {
            digits.push_back(integer.digits.back() % base);
        }
        integer = del_exp(integer / bas);
    } while (integer != zero);
    std::reverse(digits.begin(), digits.end());
    exp += digits.size();
    LongNum fract = num - integer2;
    LongNum one("1", 10);
    while (fract != zero && digits.size() - exp < precisionMax) {
        fract = fract * bas;
        if (fract >= one) {
            digits.push_back(1);
            fract = fract - one;
        }
        else {
            digits.push_back(0);
        }
    }
    this->normalize();
}

LongNum::LongNum(std::string number, int base) {
    isNegative = false;
    exp = 0;
    this->base = base;
    int i = 0;
    if (number[0] == '-') {
        isNegative = true;
        ++i;
    }
    for (; i < number.size(); ++i) {
        if (number[i] == '.') {
            ++i;
            break;
        } else {
            exp++;
            digits.push_back((int)number[i] - (int)'0');
        }
    }
    for (; i < number.size(); ++i) {
        digits.push_back((int)number[i] - (int)'0');
    }
    this->normalize();
}

void LongNum::setPrecision(int prec) {
    precisionMax = prec;
}

void LongNum::normalize() {
    if(base == 2){
        while (digits.size() > 1 && digits.size() > std::min(precisionMax + exp, 1000)){
            digits.pop_back();
        }
    }
    while (digits.size() > 1 && digits.back() == 0) {
        digits.pop_back();
    }
    while (digits.size() > 1 && digits.front() == 0) {
        digits.erase(digits.begin());
        exp--;
    }
    if (digits.size() == 1 && digits[0] == 0) {
        exp = 1;
    }
}

LongNum operator ""_longnum(long double number) {
    return LongNum(number);
}

LongNum& LongNum::operator=(const LongNum& other) {
    if (this != &other) {
        digits = other.digits;
        base = other.base;
        isNegative = other.isNegative;
        exp = other.exp;
    }
    return *this;
}

LongNum operator+(const LongNum& left, const LongNum& right) {
    if (left.isNegative == right.isNegative) {
        LongNum ans;
        ans.isNegative = left.isNegative;
        ans.base = left.base;
        int precL = left.exp;
        int precR = right.exp;
        int maxP = std::max(precL, precR);
        std::vector <int> digL = left.digits;
        std::vector <int> digR = right.digits;
        while (precL < maxP) {
            digL.insert(digL.begin(), 0);
            precL++;
        }
        while (precR < maxP) {
            digR.insert(digR.begin(), 0);
            precR++;
        }
        int digMaxS = std::max(digL.size(), digR.size());
        while (digL.size() < digMaxS) {
            digL.push_back(0);
        }
        while (digR.size() < digMaxS) {
            digR.push_back(0);
        }
        std::vector <int> res(digMaxS + 1, 0);
        for (int i = digMaxS; i > 0; --i) {
            res[i - 1] += (res[i] + digL[i - 1] + digR[i - 1]) / left.base;
            res[i] = (res[i] + digL[i - 1] + digR[i - 1]) % left.base;
        }
        ans.digits = res;
        ans.exp = maxP + 1;
        ans.normalize();
        return ans;
    } else if (right.isNegative == true) {
        if (left >= abs(right)) {
            LongNum ans;
            ans.base = left.base;
            ans.isNegative = left.isNegative;
            int precL = left.exp;
            int precR = right.exp;
            int maxP = std::max(precL, precR);
            std::vector <int> digL = left.digits;
            std::vector <int> digR = right.digits;
            while (precL < maxP) {
                digL.insert(digL.begin(), 0);
                precL++;
            }
            while (precR < maxP) {
                digR.insert(digR.begin(), 0);
                precR++;
            }
            int digMaxS = std::max(digL.size(), digR.size());
            while (digL.size() < digMaxS) {
                digL.push_back(0);
            }
            while (digR.size() < digMaxS) {
                digR.push_back(0);
            }
            std::vector <int> res(digMaxS, 0);
            for (int i = digMaxS - 1; i >= 0; --i) {
                if (digL[i] + res[i] >= digR[i]) {
                    res[i] = res[i] + digL[i] - digR[i];
                } else {
                    res[i] = left.base + res[i] + digL[i] - digR[i];
                    if (i > 0) {
                        res[i - 1] -= 1;
                    }
                }
            }
            ans.digits = res;
            ans.exp = maxP;
            ans.normalize();
            return ans;
        } else {
            LongNum nwL = right;
            nwL.isNegative = false;
            LongNum nwR = left;
            nwR.isNegative = true;
            LongNum ans(nwL + nwR);
            ans.isNegative = true;
            return ans;
        }
    } else {
        return right + left;
    }
}

LongNum operator-(const LongNum& left, const LongNum& right) {
    if (left.isNegative == true && right.isNegative == true) {
        LongNum nwL = right;
        nwL.isNegative = false;
        LongNum nwR = left;
        return nwL + nwR;
    } else if (left.isNegative == false && right.isNegative == false) {
        LongNum nwR = right;
        nwR.isNegative = true;
        return left + nwR;
    } else if (left.isNegative == false && right.isNegative == true) {
        LongNum nwR = right;
        nwR.isNegative = false;
        return left + nwR;
    } else if (left.isNegative == true && right.isNegative == false) {
        LongNum nwR = right;
        nwR.isNegative = true;
        return left + nwR;
    }
}

LongNum operator*(const LongNum& left, const LongNum& right) {
    LongNum ans;
    ans.isNegative = left.isNegative ^ right.isNegative;
    ans.base = left.base;
    ans.exp = left.exp + right.exp;
    int digS = left.digits.size() + right.digits.size();
    std::vector <int> res(digS, 0);
    for (int i = left.digits.size() - 1; i >= 0; --i) {
        for (int j = right.digits.size() - 1; j >= 0; --j) {
            res[i + j + 1] += left.digits[i] * right.digits[j];
        }
    }
    for (int i = digS - 1; i > 0; --i) {
        res[i - 1] += res[i] / left.base;
        res[i] %= left.base;
    }
    ans.digits = res;
    ans.normalize();
    return ans;
}

LongNum LongNum::inverse() const {
    LongNum denom(*this);
    denom.isNegative = false;
    LongNum num(1);
    num.base = this->base;
    LongNum res;
    res.isNegative = isNegative;
    res.exp = 1;
    res.base = base;
    res.digits.clear();
    while (denom < 1) {
        denom.exp++;
        res.exp++;
    }
    while (num < denom) {
        num.exp++;
    }
    res.exp = res.exp - num.exp + 1; 
    size_t numbers = 0;
    size_t totalNumbers = precisionMax + std::max(0, res.exp);
    do {
        int div = 0;
        while (num >= denom) {
            div++;
            num = num - denom;
        }
        num.exp++;
        num.normalize();
        res.digits.push_back(div);
        ++numbers;
    } while (num != 0 && numbers < totalNumbers);
    return res;
}

LongNum operator/(const LongNum& left, const LongNum& right)  {
    if (right.digits.size() == 1 && right.digits[0] == 0) {
        throw "division by zero is prohibited";
    }
    if(left.base == 2){
        LongNum zn1 = left;
        LongNum zn2 = right;
        zn1.isNegative = 0;
        zn2.isNegative = 0;
        if(zn1 == zn2){
            LongNum tmp(1);
            tmp.isNegative = left.isNegative ^ right.isNegative;
            return tmp;
        }
    }
    return left * right.inverse();
}

bool operator==(const LongNum& left, const LongNum& right) {
    if (left.isNegative != right.isNegative || left.exp != right.exp || left.digits.size() != right.digits.size()) {
        return false;
    }
    for (int i = 0; i < left.digits.size(); ++i) {
        if (left.digits[i] != right.digits[i]) {
            return false;
        }
    }
    return true;
}

bool operator!=(const LongNum& left, const LongNum& right) {
    return !(left == right);
}

bool operator>(const LongNum& left, const LongNum& right) {
    if (left.isNegative != right.isNegative) {
        return left.isNegative < right.isNegative;
    }
    int precL = left.exp;
    int precR = right.exp;
    int maxP = std::max(precL, precR);
    std::vector <int> digL = left.digits;
    std::vector <int> digR = right.digits;
    while (precL < maxP) {
        digL.insert(digL.begin(), 0);
        precL++;
    }
    while (precR < maxP) {
        digR.insert(digR.begin(), 0);
        precR++;
    }
    int digMaxS = std::max(digL.size(), digR.size());
    while (digL.size() < digMaxS) {
        digL.push_back(0);
    }
    while (digR.size() < digMaxS) {
        digR.push_back(0);
    }
    for (int i = 0; i < digMaxS; ++i) {
        if (digL[i] != digR[i]) {
            if (left.isNegative && right.isNegative) {
                return !(digL[i] > digR[i]);
            } else {
                return digL[i] > digR[i];
            }
        }
    }
    return false;
}

bool operator<(const LongNum& left, const LongNum& right) {
    return right > left;
}

bool operator>=(const LongNum& left, const LongNum& right) {
    return left > right || left == right;
}

bool operator<=(const LongNum& left, const LongNum& right) {
    return left < right || left == right;
}

std::string LongNum::toString() const{
    LongNum ans("0", 10);
    LongNum two("2", 10);
    LongNum twoRow("1", 10);
    std::string ansS;
    if (isNegative == true) {
        ansS += '-';
    }
    for (int i = exp - 1; i >= 0; --i) {
        if (i < digits.size() && digits[i] == 1) {
            ans = ans + twoRow;
        }
        twoRow = twoRow * two;
    }
    while (ans.digits.size() < ans.exp) {
        ans.digits.push_back(0);
    }
    for (auto i : ans.digits) {
        ansS += (char)(i + (int)'0');
    }
    ans.digits.clear();
    ans.digits.push_back(0);
    LongNum half("0.5", 10);
    LongNum halfRow("0.5", 10);
    if (exp < (long long)digits.size()) {
        ansS += '.';
        for (int i = exp; i < (long long)digits.size(); ++i) {
            if (i >= 0 && digits[i] == 1) {
                ans = ans + halfRow;
            }
            halfRow = halfRow * half;
        }
        for (auto i : ans.digits) {
            ansS += (char)(i + (int)'0');
        }
    }
    return ansS;
}

LongNum abs(LongNum x) {
    LongNum nw = x;
    if (x.isNegative == true) {
        nw.isNegative = false;
    }
    return nw;
} 

LongNum del_exp(LongNum x) {
    LongNum res = x;
    if (res.exp < 0) {
        res.exp = 0;
    }
    while (res.digits.size() > res.exp) {
        res.digits.pop_back();
    }
    if (res.digits.size() == 0) {
        res.digits.push_back(0);
        res.exp = 1;
    }
    return res;
}
