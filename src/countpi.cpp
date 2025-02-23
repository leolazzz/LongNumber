#include "longnumber.hpp"
#include <algorithm>
#include <iostream>
#include <chrono>
#include <ctime>
#include <string>
#include <thread>

class TimerGuard {
private:
    std::string m;
    std::ostream& output;
    std::chrono::high_resolution_clock::time_point start;

public:
    TimerGuard(std::string message = "", std::ostream& out = std::cout) :
        m(message),
        output(out),
        start(std::chrono::high_resolution_clock::now()) {}
    ~TimerGuard() {
        std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        output << m << " " << (int)(duration.count() * 1000) << "ms\n";
    }
};

std::vector <LongNum> binary_split(int a,int b) {
    std::vector <LongNum> vec;
    LongNum al(a);
    LongNum bl(b);
    if (b == a + 1) {
        vec.push_back((5.0_longnum - 6.0_longnum * al) * (2.0_longnum * al - 1.0_longnum) * (6.0_longnum * al - 1.0_longnum));
        vec.push_back(10939058860032000.0_longnum * al * al * al);
        vec.push_back(vec[0] * (545140134.0_longnum * al + 13591409.0_longnum));
    }
    else {
        int m = (a + b) / 2;
        std::vector <LongNum> v1 = binary_split(a, m);
        std::vector <LongNum> v2 = binary_split(m, b);
        vec.push_back(v1[0] * v2[0]);
        vec.push_back(v1[1] * v2[1]);
        vec.push_back(v2[1] * v1[2] + v1[0] * v2[2]);
    }
    return vec;
}

void calculatePiChad(int n) {
    TimerGuard time("execution time:", std::cout);
    if (n == 1) {
        std::cout << "3.1\n";
        return;
    }
    int q = n;
    if (n <= 100) {
        q = 8;
    }
    LongNum::setPrecision(std::max(5 * q, 500));
    std::vector <LongNum> a = binary_split(1, q);
    LongNum b("42698670.6663333958177128891606596082733208840025090828008380071788526051574575942163017999114556686013457371674940804113922927361812667281931368821705825634600667987664834607957359835523339854848545832762473774912507545850325782197456759912124003920153233212768354462964858373");
    LongNum d(13591409);
    LongNum res = (b * a[1]) / (d * a[1] + a[2]);
    std::string str;
    str = res.toString();
    for (int i = 0; i < n + 2; ++i) {
        std::cout << str[i];
    }
    std::cout << '\n';
    /*
    std::string s = "3.14159265358979323846264338327950288419716939937510582097494459230781640628620899862803482534211706798214808651328230664709384460955058223172535940812848111745028410270193852110555964462294895493038196442881097566593344612847564823378678316527120190914564856692346034861045432664821339360726024914127372458700660631558817488152092096282925409171536436789259036001133053054882046652138414695194151160943305727036575959195309218611738193261179310511854807446237996274956735188575272489122793818301194912983367336244065664308602139494639522473719070217986094370277053921717629317675238467481846766940513200056812714526356082778577134275778960917363717872146844090122495343014654958537105079227968925892354201995611212902196086403441815981362977477130996051870721134999999837297804995105973173281609631859502445945534690830264252230825334468503526193118817101000313783875";
    for (int i = 0; i < n + 2; ++i) {
        std::cout << s[i];
    }
    std::cout << '\n' << s.size();
    */

}

int main() {
    // int n;
    // std::cout<<"Enter the precision of pi: ";
    // std::cin >> n;
    // calculatePiChad(n);
    calculatePiChad(100);
}