
/*
原型解决了复制同类对象的问题；如果你需要复制一些对象， 同时又希望代码独立于这些对象所属的具体类， 可以使用原型模式。

原型模式将克隆过程委派给被克隆的实际对象。 模式为所有支持克隆的对象声明了一个通用接口， 该接口让你能够克隆对象， 同时又无需将代码和对象所属类耦合。 通常情况下， 这样的接口中仅包含一个 克隆方法。

*/

#include <iostream>
#include <string>

class Prototype
{
protected:
    std::string prototype_name_;
    float prototype_field_;
public:
    Prototype() {};
    Prototype(std::string prototype_name):prototype_name_(prototype_name) {
        std::cout << "Constructor Prototype: " << prototype_name_ << " with field : " << prototype_field_ << std::endl; 
    };
    virtual ~Prototype() {
        std::cout << "Deconstructor Prototype: " << prototype_name_ << " with field : " << prototype_field_ << std::endl; 
    };
    virtual Prototype* clone() const = 0;
    virtual void Methods(float prototype_field) {
        prototype_field_ = prototype_field;
        std::cout << "Call Method from " << prototype_name_ << " with field : " << prototype_field << std::endl;
    }
};

class ConcreteProtype1:public Prototype{
private:
    float concrete_protype1_field;
public:
    ConcreteProtype1(std::string prototype_name, float prototype_field):
        Prototype(prototype_name), concrete_protype1_field(prototype_field) {
            std::cout << "Constructor ConcreteProtype1: " << prototype_name << " with field : " << prototype_field << std::endl; 
        }

    ~ConcreteProtype1() {
        std::cout << "Deconstructor ConcreteProtype1: "<< std::endl; 
    }
    Prototype* clone() const override {
        return new ConcreteProtype1(*this);
    }
};

class ConcreteProtype2:public Prototype{
private:
    float concrete_protype1_field;
public:
    ConcreteProtype2(std::string prototype_name, float prototype_field):
        Prototype(prototype_name), concrete_protype1_field(prototype_field) {
            std::cout << "Constructor ConcreteProtype2: " << prototype_name << " with field : " << prototype_field << std::endl; 
        }
    ~ConcreteProtype2() {
        std::cout << "Deconstructor ConcreteProtype2: "<< std::endl; 
    }
    Prototype* clone() const override {
        return new ConcreteProtype2(*this);
    }
};

class PrototypeFactory {
private:
    Prototype* prototypes_[2];
public:
    PrototypeFactory() {
        std::cout << "Constructor PrototypeFactory: " << std::endl; 
        prototypes_[0] = new ConcreteProtype1("PROTOTYPE1", 50.f);
        prototypes_[1] = new ConcreteProtype2("PROTOTYPE2", 70.f);
    }

    ~PrototypeFactory() {
        std::cout << "Deconstructor PrototypeFactory: " << std::endl; 
        delete prototypes_[0];
        delete prototypes_[1]; 
    }

    Prototype* CreateType(int type) {
        return prototypes_[type]->clone();
    }
};

void client(PrototypeFactory &factory) {
    Prototype* type1 = factory.CreateType(0);
    type1->Methods(90);
    delete type1;

    Prototype* type2 = factory.CreateType(1);
    type2->Methods(10);
    delete type2;
}

int main() {
    PrototypeFactory *factory = new PrototypeFactory();
    client(*factory);
    delete factory;
    return 0;
}