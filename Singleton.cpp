#include <thread>
#include <iostream>
#include <mutex>

class Singleton {
private:
    Singleton(std::string str):value(str)  {};
    ~Singleton() {};
    std::string value;
    static Singleton* instance;
    static std::mutex mt;

public:
    static Singleton* GetInstance(std::string str);

    std::string GetStr() {
        return this->value;
    }
};

Singleton* Singleton::instance = nullptr;
std::mutex Singleton::mt;

Singleton* Singleton::GetInstance(std::string str) {
    std::lock_guard<std::mutex> lock(mt);
    if (instance == nullptr) {
        instance = new Singleton(str);
    }
    return instance;
}

void ThreadFoo() {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    Singleton *single1 = Singleton::GetInstance("FOO");
    std::cout<< single1->GetStr() << std::endl;;
}

void ThreadBar() {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    Singleton *single2 = Singleton::GetInstance("Bar");
    std::cout<< single2->GetStr() << std::endl;;
}

int main() {
    std::thread t1(ThreadFoo);
    std::thread t2(ThreadBar);

    t1.join();
    t2.join();
    return 0;

}
