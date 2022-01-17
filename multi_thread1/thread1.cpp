#include <iostream>
#include <thread>

struct func {
    int& _i;
    func(int& i) : _i(i) {}
    void operator() ()
    {
        for (unsigned j = 0; j < 10000; ++j) {
            std::cout << _i + j << std::endl;
        }
    }
};

int main(void)
{
    int local_data = 10000;
    func my_func{local_data};
    std::thread my_thread(my_func);
//    my_thread.join();
    return 0;

}
