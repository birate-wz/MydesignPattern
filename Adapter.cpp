
/*
适配器模式是一种结构型设计模式， 它能使接口不兼容的对象能够相互合作。
步骤:
适配器实现与其中一个现有对象兼容的接口。
现有对象可以使用该接口安全地调用适配器方法。
适配器方法被调用后将以另一个对象兼容的格式和顺序将请求传递给该对象。
 */

#include <iostream>
#include <string>

class Target {
public:
    virtual ~Target() = default;
    virtual std::string Request() const {
        return "Target: The default target's behavior.";
    }
};

class Adaptee {
public:
    std::string SpecialRequest() const {
        return ".eetpadA eht fo roivaheb laicepS";
    }
};

class Adapter: public Target {
private:
    Adaptee *adptee_;
public:
    Adapter(Adaptee *adptee) : adptee_(adptee) { }

    std::string Request() const override {
        std::string SR = adptee_->SpecialRequest();
        std::reverse(SR.begin(), SR.end());
        return "Adapter: (TRANSLATED) " + SR;
    }
};

void ClientCode(Target* target) {
    std::cout<< target->Request();
}

int main() {
  std::cout << "Client: I can work just fine with the Target objects:\n";
  Target *target = new Target;
  ClientCode(target);
  std::cout << "\n\n";
  Adaptee *adaptee = new Adaptee;
  std::cout << "Client: The Adaptee class has a weird interface. See, I don't understand it:\n";
  std::cout << "Adaptee: " << adaptee->SpecialRequest();
  std::cout << "\n\n";
  std::cout << "Client: But I can work with it via the Adapter:\n";
  Adapter *adapter = new Adapter(adaptee);
  ClientCode(adapter);
  std::cout << "\n";

  delete target;
  delete adaptee;
  delete adapter;

  return 0;
}