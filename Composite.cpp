
/*
如果你需要实现树状对象结构， 可以使用组合模式。
如果你希望客户端代码以相同方式处理简单和复杂元素， 可以使用该模式。
*/
#include <algorithm>
#include <iostream>
#include <string>
#include <list>

class Component {
protected:
    Component *component_;
public:
    virtual ~Component() {};
    void SetParaent(Component* component) {
        this->component_ = component;
    }

    Component* GetComponent() {
        return this->component_;
    }

    virtual void Add(Component* component) {};
    virtual void Remove(Component* component) {};
    virtual bool IsComposite() const {
        return false;
    }
    virtual std::string Operation() const = 0;
};

class Leaf:public Component {
public:
    std::string Operation() const override {
        return "Leaf";
    }
};

class Compositior:public Component {
protected:
    std::list<Component*> children_;
public:
    void Add(Component* component) override {
        this->children_.push_back(component);
        component->SetParaent(this);
    }

    void Remove(Component* component) override {
        this->children_.remove(component);
        component->SetParaent(nullptr);
    }

    bool IsComposite() const {
        return true;
    }

    std::string Operation() const override {
        std::string res;
        for (const Component *ch : children_) {
            if (ch == children_.back()) {
                res += ch->Operation();
            } else {
                res += ch->Operation() + "+";
            }
        }
        return "Branch(" + res + ")";
    }
};

void ClientCode(Component *component) {
    std::cout << "RESULT: " << component->Operation();
}

void ClientCode2(Component *component1, Component *component2) {
  // ...
  if (component1->IsComposite()) {
    component1->Add(component2);
  }
  std::cout << "RESULT: " << component1->Operation();
  // ...
}

int main() {
  Component *simple = new Leaf;
  std::cout << "Client: I've got a simple component:\n";
  ClientCode(simple);
  std::cout << "\n\n";
  /**
   * ...as well as the complex composites.
   */

  Component *tree = new Compositior;
  Component *branch1 = new Compositior;

  Component *leaf_1 = new Leaf;
  Component *leaf_2 = new Leaf;
  Component *leaf_3 = new Leaf;
  branch1->Add(leaf_1);
  branch1->Add(leaf_2);
  Component *branch2 = new Compositior;
  branch2->Add(leaf_3);
  tree->Add(branch1);
  tree->Add(branch2);
  std::cout << "Client: Now I've got a composite tree:\n";
  ClientCode(tree);
  std::cout << "\n\n";

  std::cout << "Client: I don't need to check the components classes even when managing the tree:\n";
  ClientCode2(tree, simple);
  std::cout << "\n";

  delete simple;
  delete tree;
  delete branch1;
  delete branch2;
  delete leaf_1;
  delete leaf_2;
  delete leaf_3;

  return 0;


}