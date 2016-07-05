#include <iostream>
#include <vector>
#include <array>
#include <map>
#include <assert.h>
#include <sstream>

using namespace std;

std::string derivative(std::string);

template <class E, class A>
void myassert(E expected, A actual) {
    if (expected != actual) {
        std::cerr << "expected: {" << expected << "} actual [" << actual << "]" << std::endl;
        assert(false);
    }
}

template <class iter>
void print(iter b, iter e) {
    int index = 1;
    for (auto i = b; i != e; ++i) {
        std:cout << index++ << ": " << *i << std::endl;
    }
}

template <class T>
void print(std::vector<T> const  & v) {
    cout << "Capacity: " << v.capacity() << std::endl;
    cout << "Size: " << v.size() << std::endl;
    print(v.begin(), v.end());
}

void stdvector() {
    std::vector<long long> vint((size_t)4); // preallocate 16 elements
    print(vint);
    vint.reserve(8); // memory
    print(vint);
    vint.resize(3); // number of elements
    print(vint);

    vint.insert(vint.begin() + 1, 13); // insert second
    print(vint);

    vint.push_back(666);
    print(vint);

    vint.erase(vint.end() - 1);
    vint.erase(vint.end() - 1);
    print(vint);

    vint.pop_back();
    print(vint);

    print(vint.rbegin(), vint.rend());
    print(vint.cbegin(), vint.cend());
}

void stdarray() {
    std::array<std::string, 4> vstr;
    vstr[0] = "Hell"; vstr[1] = "No"; vstr[2] = "Beer"; vstr[3] = "Oh yeah baba!";
    std::cout << vstr.size() << " " << vstr.max_size() << std::endl;
    print(vstr.begin(), vstr.end());
}

void task() {
    myassert("2*x+1", derivative("x^2+x"));
    myassert("200*x^99+200*x", derivative("2*x^100+100*x^2"));
    myassert("10000*x^9999+1", derivative("x^10000+x+1"));
    myassert("10", derivative("x+x+x+x+x+x+x+x+x+x"));
    myassert("-3*x^2-2*x", derivative("-x^2-x^3"));
}

std::string derivative(std::string input) {

    std::map<int, int> poly;
    for (auto iter = input.begin(); iter != input.end() && *iter != '\0';) {

        int sign = 1;
        int c = 1;
        int p = 0;

        if (*iter == '-') {
            sign = -1;
            ++iter;
        }
        if (*iter == '+') {
            // positive by default
            ++iter;
        }

        if (iter != input.end() && isdigit(*iter)) {
            std::string cstr = "";
            while (iter != input.end() && isdigit(*iter)) {
                cstr += *iter++;
            }
            c = std::stoi(cstr);
        }

        if (iter != input.end() && *iter == '*') {
            ++iter;
        }

        if (iter != input.end() && *iter == 'x') {
            p = 1;
            ++iter;
        }

        if (iter != input.end() && *iter == '^') {
            iter++;
            std::string pstr = "";
            while (iter != input.end() && isdigit(*iter)) {
                pstr += *iter++;
            }
            p = std::stoi(pstr);
        }

        // done with the member
        if (poly.find(p) != poly.end()){
            poly[p] = poly[p] + sign * c;
        } else {
            poly[p] = sign * c;
        }
    }

    std::stringstream ss;
    bool start = true;
    bool derivate = true;
    for (auto iter = poly.rbegin(); iter != poly.rend(); iter++) {
        // first -- power
        // second -- coefficient
        int p = iter->first;
        int c = iter->second;

        if (derivate) {
            c *= p;
            --p;
        }

        if (c == 0) {
            continue;
        }

        if (!start && c > 0) {
            ss << "+";
        }
        start = false;

        if (p == 0) {
            ss << c;
            continue;
        }

        if (c == 1) {
            ss << 'x';
        } else if (c == -1) {
            ss << "-x";
        } else {
            ss << c << "*x";
        }

        if (p != 1) {
            ss << '^' << p;
        }
    }

    std::cout << ss.str();
    std::cout << " <- " << input;
    std::cout << std::endl;
    return ss.str();
}


int main() {
//    stdvector();
//    stdarray();
    task();
    return 0;
}