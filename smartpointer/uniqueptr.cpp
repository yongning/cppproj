#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <thread>

#include <cstdlib>
#include <cstdio>
#include <cstring>

namespace smptr {

class buffer {
public:
    buffer(size_t number = 1500) : size_(number) {
        std::cout << "buffer cstor" << std::endl;
        pData_ = new char(number);
    }

    virtual ~buffer() {
        std::cout << "buffer destruction" << std::endl;
        delete pData_;
    }

    void buffername() {
        std::cout << name_ << std::endl;
        std::cout << pData_ << std::endl;
    }

    void set(const char* data, size_t size) {
        strncpy(pData_, data, size);
    }
private:
    size_t size_;
    char* pData_;
    std::string name_{"buffer_test"};
};

struct bufferDeleter {
    bufferDeleter() {};
    void operator()(smptr::buffer* p) const {
        std::cout << "bufferDeleter" << std::endl;
        delete p;
    }
};


void fn(std::unique_ptr<smptr::buffer, smptr::bufferDeleter> p1) {
    p1->buffername();
}



};

int main()
{
    smptr::bufferDeleter d;
    std::unique_ptr<smptr::buffer, smptr::bufferDeleter> ptr1(new smptr::buffer(1500), d);
    // auto ptr1 = std::make_unique<smptr::buffer, decltype(smptr::bufferDeleter())>(1500, d);
    // auto ptr1 = std::make_unique<smptr::buffer>(1500);
    const char* pchr = "this is a test";
    ptr1->set(pchr, strlen("this is a test"));
    ptr1->buffername();

    // auto ptr2(std::move(ptr1));

    std::thread t1(smptr::fn, std::move(ptr1));

    if (!ptr1) {
        std::cout << "ptr1" << std::endl;
    }

    // ptr2->buffername();
    t1.join();

    std::cout << "main thread exit" << std::endl;

    auto ptrarray1 = std::make_unique<smptr::buffer[]>(3);
    ptrarray1[0].set("testarray1", strlen("testarray1"));
    ptrarray1[0].buffername();


    return 0;

}
