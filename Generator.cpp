#include <vector>
#include <string>
#include <iostream>
/*
 使用生成器模式可避免 “重叠构造函数 （telescoping constructor）” 的出现。

假设你的构造函数中有十个可选参数， 那么调用该函数会非常不方便； 因此， 你需要重载这个构造函数， 新建几个只有较少参数的简化版。 但这些构造函数仍需调用主构造函数， 传递一些默认数值来替代省略掉的参数。
*/

class Product1 {
public:
    std::vector<std::string> parts;

    void ListParts() const {
        std::cout<< "Product parts:";
        for (size_t i = 0; i < parts.size(); i++) {
            if (parts[i] == parts.back()) 
                std::cout<< parts[i];
            else 
                std::cout<<parts[i] << ",";
        }
        std::cout<<std::endl; 
    }
};

class Builder {
    public:
    virtual ~Builder() {};
    virtual void ProducePartsA() const = 0;
    virtual void ProducePartsB() const = 0;
    virtual void ProducePartsC() const = 0;
};

class ConcreteBuilder1:public Builder {
    private:
    Product1 *product;
    public:
    ConcreteBuilder1() {
        this->Reset();
    }
    ~ConcreteBuilder1() {
        delete product;
    }

    void Reset(){
        this->product= new Product1();
    }
    void ProducePartsA() const override {
        product->parts.push_back("PartsA");
    }

    void ProducePartsB() const override {
        product->parts.push_back("PartsB");
    }

    void ProducePartsC() const override {
        product->parts.push_back("PartsC");
    }

    Product1 *GetProduct() {
        Product1 *res = product;
        this->Reset();
        return res;
    }
};

class Director{
private:
    Builder* builder;
    /**
     * The Director works with any builder instance that the client code passes
     * to it. This way, the client code may alter the final type of the newly
     * assembled product.
     */

    public:

    void set_builder(Builder* builder){
        this->builder=builder;
    }

    /**
     * The Director can construct several product variations using the same
     * building steps.
     */

    void BuildMinimalViableProduct(){
        this->builder->ProducePartsA();
    }
    
    void BuildFullFeaturedProduct(){
        this->builder->ProducePartsA();
        this->builder->ProducePartsB();
        this->builder->ProducePartsC();
    }
};


void ClientCode(Director& director)
{
    ConcreteBuilder1* builder = new ConcreteBuilder1();
    director.set_builder(builder);
    std::cout << "Standard basic product:\n"; 
    director.BuildMinimalViableProduct();
    
    Product1* p= builder->GetProduct();
    p->ListParts();
    delete p;

    std::cout << "Standard full featured product:\n"; 
    director.BuildFullFeaturedProduct();

    p= builder->GetProduct();
    p->ListParts();
    delete p;

    // Remember, the Builder pattern can be used without a Director class.
    std::cout << "Custom product:\n";
    builder->ProducePartsA();
    builder->ProducePartsC();
    p=builder->GetProduct();
    p->ListParts();
    delete p;

    delete builder;
}

int main() {
    Director* director= new Director();
    ClientCode(*director);
    delete director;
    return 0;
}
