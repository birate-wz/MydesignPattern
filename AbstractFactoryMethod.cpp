#include <iostream>
#include <string>

/*
 如果代码需要与多个不同系列的相关产品交互， 但是由于无法提前获取相关信息， 或者出于对未来扩展性的考虑， 你不希望代码基于产品的具体类进行构建， 在这种情况下， 你可以使用抽象工厂。

抽象工厂为你提供了一个接口， 可用于创建每个系列产品的对象。 只要代码通过该接口创建对象， 那么你就不会生成与应用程序已生成的产品类型不一致的产品。

如果你有一个基于一组抽象方法的类， 且其主要功能因此变得不明确， 那么在这种情况下可以考虑使用抽象工厂模式。

在设计良好的程序中， 每个类仅负责一件事。 如果一个类与多种类型产品交互， 就可以考虑将工厂方法抽取到独立的工厂类或具备完整功能的抽象工厂类中。

你可以确保同一工厂生成的产品相互匹配。
你可以避免客户端和具体产品代码的耦合。
单一职责原则。 你可以将产品生成代码抽取到同一位置， 使得代码易于维护。
开闭原则。 向应用程序中引入新产品变体时， 你无需修改客户端代码。
*/


class AbstractProductA {
public:
    virtual ~AbstractProductA() {};
    virtual std::string UsefulFunctionA() const = 0;
};

class ConcreteProductA1: public AbstractProductA
{
public:
    virtual ~ConcreteProductA1() {};
    std::string UsefulFunctionA() const override {
        return "The result of product A1";
    }
};

class ConcreteProductA2 : public AbstractProductA
{
public:
    virtual ~ConcreteProductA2() {};
    std::string UsefulFunctionA() const override {
        return "The result of product A2";
    }
};

class AbstractProductB {
public:
    virtual ~AbstractProductB() {};
    virtual std::string UsefulFunctionB() const = 0;

    virtual std::string UsefulAnotherFunctionB(const AbstractProductA& collaborate) const = 0;
};

class ConcreteProductB1: public AbstractProductB
{
public:
    virtual ~ConcreteProductB1() {};
    std::string UsefulFunctionB() const override {
        return "The result of product B1";
    }
    std::string UsefulAnotherFunctionB(const AbstractProductA& collaborate) const {
        return "he result of the B1 collaborating with ( " + collaborate.UsefulFunctionA() + " )";
    }
};

class ConcreteProductB2 : public AbstractProductB
{
public:
    virtual ~ConcreteProductB2() {};
    std::string UsefulFunctionB() const override {
        return "The result of product B2";
    }
    std::string UsefulAnotherFunctionB(const AbstractProductA& collaborate) const {
        return "he result of the B2 collaborating with ( " + collaborate.UsefulFunctionA() + " )";
    }
};

class AbstractFactory
{
public:
    virtual AbstractProductA* CreateProductA() const = 0;
    virtual AbstractProductB* CreateProductB() const = 0;
};

class ConcreteFactory1 : public AbstractFactory
{
public:
    AbstractProductA* CreateProductA() const override {
        return new ConcreteProductA1();
    }
    AbstractProductB* CreateProductB() const override {
        return new ConcreteProductB1();
    }
};

class ConcreteFactory2 : public AbstractFactory
{
public:
    AbstractProductA* CreateProductA() const override {
        return new ConcreteProductA2();
    }
    AbstractProductB* CreateProductB() const override {
        return new ConcreteProductB2();
    }
};

void ClientCode(const AbstractFactory& factory) {
    const AbstractProductA *productA = factory.CreateProductA(); 
    const AbstractProductB *productB = factory.CreateProductB();

    std::cout << productB->UsefulFunctionB() << "\n";
    std::cout << productB->UsefulAnotherFunctionB(*productA) << "\n";
    delete productA;
    delete productB;
}

int main() {
    AbstractFactory *factory1 = new ConcreteFactory1();
    ClientCode(*factory1);

    AbstractFactory *factory2 = new ConcreteFactory2();
    ClientCode(*factory2);

    return 0;
}
