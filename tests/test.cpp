#include "longnumber.hpp"
#include <algorithm>
#include <iostream>

#define RUN_TEST(test) \
    try { \
        test(); \
        std::cout << "[OK] " << #test << std::endl; \
    } catch (const std::exception& e) { \
        std::cout << "[FAIL] " << #test << " - " << e.what() << std::endl; \
    }

#define ASSERT(condition) \
    if (!(condition)) { \
        throw std::runtime_error("Assertion failed: " #condition); \
    }

void test_creation_from_literal() {
    LongNum num1 = 3.14_longnum;
    LongNum num2((long double)3.14);
    ASSERT(num1 == num2);
}

void test_creation_from_string() {
    LongNum num1("3.14");
    LongNum num2((long double)3.14);
    ASSERT(num1 == num2);
}

void test_creation_from_longlong() {
    LongNum num1((long long)92233720368547);
    LongNum num2("92233720368547");
    ASSERT(num1 == num2);
}

void test_addition() {
    LongNum result = 1.5_longnum + 2.5_longnum;
    ASSERT(result == 4.0_longnum);
}

void test_subtraction() {
    LongNum result = 10.4_longnum - 2.5_longnum;
    ASSERT(result == 7.9_longnum);
}

void test_multiplication() {
    LongNum result = 2.0_longnum * 3.0_longnum;
    ASSERT(result == 6.0_longnum);
}

void test_inverse() {
    LongNum result = 2.0_longnum;
    result = result.inverse();
    ASSERT(result == 0.5_longnum);
}

void test_division() {
    LongNum result = 1.0_longnum / 2.0_longnum;
    ASSERT(result == 0.5_longnum);
}

void test_comparison() {
    LongNum x1(1.0);
    LongNum x2(2.0);
    ASSERT(x1 < x2);
}

void test_comparison1() {
    LongNum x1(-0.2);
    LongNum x2(-0.21);
    ASSERT(x1 > x2);
}

void test_comparison2() {
    LongNum x1(2.0);
    LongNum x2(2.0);
    ASSERT(x1 <= x2);
}

void test_comparison3() {
    LongNum x1(-0.2);
    LongNum x2(-0.21);
    ASSERT(x1 >= x2);
}

void test_equality() {
    LongNum x1(0.2);
    LongNum x2(0.20);
    ASSERT(x1 == x2);
}

void test_equality1() {
    LongNum x1(-1);
    LongNum x2(-1);
    ASSERT(x1 == x2);
}

void test_inequality() {
    LongNum x1(0.2);
    LongNum x2(0.21);
    ASSERT(x1 != x2);
}

void test_inequality1() {
    LongNum x1(1);
    LongNum x2(-1);
    ASSERT(x1 != x2);
}

void test_transformation_into_string() {
    LongNum result = 0.5_longnum;
    std::string res = result.toString();
    ASSERT(res == "0.5");
}

void test_delexp() {
    LongNum result = del_exp(2.5_longnum);
    ASSERT(result == 2.0_longnum);
}

void test_abs() {
    LongNum result(-2);
    result = abs(result);
    ASSERT(result == 2.0_longnum);
}

int main() {
    RUN_TEST(test_creation_from_literal);
    RUN_TEST(test_addition);
    RUN_TEST(test_subtraction);
    RUN_TEST(test_multiplication);
    RUN_TEST(test_inverse);
    RUN_TEST(test_division);
    RUN_TEST(test_comparison);
    RUN_TEST(test_comparison1);
    RUN_TEST(test_comparison2);
    RUN_TEST(test_comparison3);
    RUN_TEST(test_equality);
    RUN_TEST(test_equality1);
    RUN_TEST(test_inequality);
    RUN_TEST(test_inequality1);
    RUN_TEST(test_transformation_into_string);
}