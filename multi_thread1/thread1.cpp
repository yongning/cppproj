#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <optional>
#include <utility>

#include <sw/redis++/redis++.h>

struct func {
    int& _i;
    func(int& i) : _i(i) {}
    void operator() ()
    {
        for (unsigned j = 0; j < 10; ++j) {
            std::cout << _i + j << std::endl;
        }
    }
};

struct redisfunc1 {
    sw::redis::Redis& _redis;
    redisfunc1(sw::redis::Redis& i) : _redis(i) {}
    void operator() ()
    {
        for (unsigned k = 0; k < 100; ++k) {
        _redis.set("key1", "valfunc1");
        auto valfunc1 = _redis.get("key1");
        std::cout << *valfunc1 << std::endl;
        }
    }
};

struct redisfunc2 {
    sw::redis::Redis& _redis;
    std::vector<std::string> vec;
    redisfunc2(sw::redis::Redis& i) : _redis(i) {}
    void operator() ()
    {
        auto valfunc2 = _redis.brpop("mylist2", 0);
        std::cout << valfunc2.value().second << std::endl;
    }
};


int main(void)
{
    auto redis = sw::redis::Redis("tcp://127.0.0.1:6379");
    redis.set("key", "val");
    auto val = redis.get("key");
    std::cout << *val << std::endl;

    int local_data = 10000;
    func my_func{local_data};
    std::thread my_thread(my_func);
    redisfunc1 redisfunc1(redis);
    std::thread my_thread1(redisfunc1);
    redisfunc2 redisfunc2(redis);
    std::thread my_thread2(redisfunc2);

    my_thread.join();
    my_thread1.join();
    my_thread2.join();
    return 0;

}

