#include <string>
#include <iostream>

class StringPointer {
private:
        std::string *ptr;

public:
    std::string *operator->() {
        if (!ptr) {
            ptr = new std::string("");
        }
        return ptr;
    }

    operator std::string*() {
        if (!ptr) {
            ptr = new std::string("");
        }
        return ptr;
    }

    StringPointer(std::string *ptr) {
        if (ptr) {
            this->ptr = new std::string(*ptr);
        }
    };

    ~StringPointer() { 
        if (ptr) {  
            delete ptr;
            ptr = nullptr;
        }
    };

};


int main() {
    std::string s1 = "Hello, world!";

    StringPointer sp1(&s1);
    StringPointer sp2(NULL);
    
    std::cout << sp1->length() << std::endl;
    std::cout << *sp1 << std::endl;
    std::cout << sp2->length() << std::endl;
    std::cout << *sp2 << std::endl;
    return 0;
}
