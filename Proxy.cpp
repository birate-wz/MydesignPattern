
/*
代理模式是一种结构型设计模式， 让你能够提供对象的替代品或其占位符。 代理控制着对于原对象的访问， 并允许在将请求提交给对象前后进行一些处理。
代理模式建议新建一个与原服务对象接口相同的代理类， 然后更新应用以将代理对象传递给所有原始对象客户端。 代理类接收到客户端请求后会创建实际的服务对象， 并将所有工作委派给它。

延迟初始化 （虚拟代理）。 如果你有一个偶尔使用的重量级服务对象， 一直保持该对象运行会消耗系统资源时， 可使用代理模式。
你无需在程序启动时就创建该对象， 可将对象的初始化延迟到真正有需要的时候。

访问控制 （保护代理）。 如果你只希望特定客户端使用服务对象， 这里的对象可以是操作系统中非常重要的部分， 而客户端则是各种已启动的程序 （包括恶意程序）， 此时可使用代理模式。
代理可仅在客户端凭据满足要求时将请求传递给服务对象。

本地执行远程服务 （远程代理）。 适用于服务对象位于远程服务器上的情形。
在这种情形中， 代理通过网络传递客户端请求， 负责处理所有与网络相关的复杂细节

记录日志请求 （日志记录代理）。 适用于当你需要保存对于服务对象的请求历史记录时。
代理可以在向服务传递请求前进行记录。

缓存请求结果 （缓存代理）。 适用于需要缓存客户请求结果并对缓存生命周期进行管理时， 特别是当返回结果的体积非常大时。
代理可对重复请求所需的相同结果进行缓存， 还可使用请求参数作为索引缓存的键值。

智能引用。 可在没有客户端使用某个重量级对象时立即销毁该对象。
代理会将所有获取了指向服务对象或其结果的客户端记录在案。 代理会时不时地遍历各个客户端， 检查它们是否仍在运行。 如果相应的客户端列表为空， 代理就会销毁该服务对象， 释放底层系统资源。
*/
#include <iostream>

class Subject{
public:
    virtual void Request() = 0;
};

class RealSubject:public Subject{
public:
    void Request() override {
        std::cout<<"RealSubject: Handling request.\n";
    }
};

class Proxy:public Subject{
private:
    RealSubject* realsubject_;
    bool CheckAccess() const {
        // Some real checks should go here.
        std::cout << "Proxy: Checking access prior to firing a real request.\n";
        return true;
    }
    void LogAccess() const {
        std::cout << "Proxy: Logging the time of request.\n";
    }

public:
    Proxy(RealSubject* rs):realsubject_(new RealSubject(*rs)) {}
    ~Proxy() {
        delete realsubject_;
    }
    void Request() override {
        if (this->CheckAccess()) {
            this->realsubject_->Request();
            this->LogAccess();
        }
    }
};

void ClientCode(Subject &subject) {
  // ...
  subject.Request();
  // ...
}


int main() {
  std::cout << "Client: Executing the client code with a real subject:\n";
  RealSubject *real_subject = new RealSubject;
  ClientCode(*real_subject);
  std::cout << "\n";
  std::cout << "Client: Executing the same client code with a proxy:\n";
  Proxy *proxy = new Proxy(real_subject);
  ClientCode(*proxy);

  delete real_subject;
  delete proxy;
  return 0;
}
