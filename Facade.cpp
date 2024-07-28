/*
外观类为包含许多活动部件的复杂子系统提供一个简单的接口。 
如果你的程序需要与包含几十种功能的复杂库整合， 但只需使用其中非常少的功能， 那么使用外观模式会非常方便.

如果你需要一个指向复杂子系统的直接接口， 且该接口的功能有限， 则可以使用外观模式。
*/
#include <string>
#include <iostream>
#include <memory>

class Subsystem1{
public:
    std::string Opeartion1() {
        return "Subsystem1:Ready\n";
    }

    std::string OpeartionN() {
        return "Subsystem1:go\n";
    }
};

class Subsystem2{
public:
    std::string Opeartion2() {
        return "Subsystem2:Ready\n";
    }

    std::string OpeartionZ() {
        return "Subsystem2:go\n";
    }
};

class Facade{
protected:
    std::unique_ptr<Subsystem1> subsystem1;
    std::unique_ptr<Subsystem2> subsystem2;

public:
    Facade(std::unique_ptr<Subsystem1> system1, std::unique_ptr<Subsystem2> system2) {
        if (system1 == nullptr) subsystem1 = std::make_unique<Subsystem1>();
        else subsystem1 = std::move(system1);
        if (system2 == nullptr) subsystem2 = std::make_unique<Subsystem2>();
        else subsystem2 = std::move(system2);
    }
    ~Facade() {
        
    }

    std::string Opeartion() {
        std::string result = "Facade initializes subsystems:\n";
        result += this->subsystem1->Opeartion1();
        result += this->subsystem1->Opeartion1();
        result += "Facade orders subsystems to perform the action:\n";
        result += this->subsystem2->Opeartion2();
        result += this->subsystem2->OpeartionZ();
        return result;
    }
};

void Client(Facade *facade) {
    std::cout<< facade->Opeartion() << std::endl;
}

int main() {
    std::unique_ptr<Subsystem1> sys1(new Subsystem1);
    std::unique_ptr<Subsystem2> sys2(new Subsystem2);
    std::unique_ptr<Facade> facade(new Facade(std::move(sys1), std::move(sys2)));
    Client(facade.get());
    return 0;
}


