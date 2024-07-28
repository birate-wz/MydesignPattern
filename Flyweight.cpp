/*
享元模式是一种结构型设计模式， 它摒弃了在每个对象中保存所有数据的方式， 通过共享多个对象所共有的相同状态， 让你能在有限的内存容量中载入更多对象。

仅在程序必须支持大量对象且没有足够的内存容量时使用享元模式。
应用该模式所获的收益大小取决于使用它的方式和情景。 它在下列情况中最有效：
    程序需要生成数量巨大的相似对象
    这将耗尽目标设备的所有内存
    对象中包含可抽取且能在多个对象间共享的重复状态。

实现方式：
将需要改写为享元的类成员变量拆分为两个部分：
    内在状态： 包含不变的、 可在许多对象中重复使用的数据的成员变量。
    外在状态： 包含每个对象各自不同的情景数据的成员变量
保留类中表示内在状态的成员变量， 并将其属性设置为不可修改。 这些变量仅可在构造函数中获得初始数值。
找到所有使用外在状态成员变量的方法， 为在方法中所用的每个成员变量新建一个参数， 并使用该参数代替成员变量。
你可以有选择地创建工厂类来管理享元缓存池， 它负责在新建享元时检查已有的享元。 如果选择使用工厂， 客户端就只能通过工厂来请求享元， 它们需要将享元的内在状态作为参数传递给工厂。
客户端必须存储和计算外在状态 （情景） 的数值， 因为只有这样才能调用享元对象的方法。 为了使用方便， 外在状态和引用享元的成员变量可以移动到单独的情景类中。
*/
#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>

class SharedState {
public:
    std::string brand_;
    std::string model_;
    std::string color_;

    SharedState(const std::string &brand, const std::string &model, const std::string &color):
        brand_(brand),
        model_(model),
        color_(color) {

    }

    friend std::ostream &operator<<(std::ostream &os, const SharedState& state) {
        return os<<"[ "<< state.brand_ << ", " << state.model_ <<", "<< state.color_<<" ]";
    }
};

class UniqueState {
public:
    std::string owner_;
    std::string plates_;

    UniqueState(const std::string &owner, const std::string &plates):
        owner_(owner),
        plates_(plates) {

    }

    friend std::ostream &operator<<(std::ostream &os, const UniqueState& state) {
        return os<<"[ "<< state.owner_ << ", " << state.plates_ <<" ]";
    }
};

class Flyweight {
private:
    std::unique_ptr<SharedState> shared_state_;
public:
    Flyweight(const SharedState*shared_state):shared_state_(std::make_unique<SharedState>(*shared_state)) {}
    Flyweight(const Flyweight &other):shared_state_(new SharedState(*other.shared_state_)) {}
    ~Flyweight() {}

    SharedState *shared_state() const {
        return shared_state_.get();
    }

    void Operation(const UniqueState &unique_state) const {
        std::cout<< "Flyweight: Displaying shared (" << *shared_state_ << ") and unique (" << unique_state << ") state.\n";
    }
};

class FlyweightFactory{
private:
    std::unordered_map<std::string, Flyweight> flyweights_;
    std::string GetKey(const SharedState &ss) const {
        return ss.brand_ + "_" + ss.model_ + "_" + ss.color_;
    }

public:
    FlyweightFactory(std::initializer_list<SharedState> shared_states) {
        for (auto ss:shared_states) {
            this->flyweights_.insert({this->GetKey(ss), Flyweight(&ss)});
        }
    }

    Flyweight GetFlyweight(const SharedState& shared_state) {
        auto key = this->GetKey(shared_state);
        if (flyweights_.find(key) == flyweights_.end()) {
            std::cout << "FlyweightFactory: Can't find a flyweight, creating new one.\n";
            this->flyweights_.insert({key, Flyweight(&shared_state)});
        } else {
            std::cout << "FlyweightFactory: Reusing existing flyweight.\n";
        }
        return this->flyweights_.at(key);
    }

    void ListFlyweights() const {
        size_t count = this->flyweights_.size();
        std::cout << "\nFlyweightFactory: I have " << count << " flyweights:\n";
        for (auto val:flyweights_) {
            std::cout<<val.first << "\n";
        }
    }
};

void AddCarToPoliceDatabase(FlyweightFactory& ff, const std::string &plates, const std::string &owner,
    const std::string &brand, const std::string &model, const std::string &color) {
    std::cout << "\nClient: Adding a car to database.\n";
    const Flyweight &flyweight = ff.GetFlyweight({brand, model, color});
    // The client code either stores or calculates extrinsic state and passes it
    // to the flyweight's methods.
    flyweight.Operation({owner, plates});
}

int main() {
    FlyweightFactory *factory = new FlyweightFactory({{"Chevrolet", "Camaro2018", "pink"}, {"Mercedes Benz", "C300", "black"}, {"Mercedes Benz", "C500", "red"}, {"BMW", "M5", "red"}, {"BMW", "X6", "white"}});
    factory->ListFlyweights();

    AddCarToPoliceDatabase(*factory,
                            "CL234IR",
                            "James Doe",
                            "BMW",
                            "M5",
                            "red");

    AddCarToPoliceDatabase(*factory,
                            "CL234IR",
                            "James Doe",
                            "BMW",
                            "X1",
                            "red");
    factory->ListFlyweights();
    delete factory;
    return 0;
}
