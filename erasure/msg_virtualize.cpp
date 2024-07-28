#include <memory>
#include <vector>
#include <iostream>
#include <variant>
#include "msglib.h"
//#1 使用std::variant
// 问题 std::::variant的大小是最大的结构体最大的大小+unsigned int， 带来类型膨胀
// 性能开销，不支持空值。
//using Msg = std::variant<MoveMsg, JumpMsg, SleepMsg, ExitMsg>;


//#2 自定义一个虚函数
struct MsgBase
{
    virtual void speak() = 0;
    virtual void happy() = 0;
    virtual std::shared_ptr<MsgBase> clone() const = 0;  // 拷贝构造
    virtual ~MsgBase() = default;
};

template<class Msg>
struct MsgImpl:MsgBase
{
    Msg msg;

    template<class ...Ts>
    MsgImpl(Ts &&...ts):msg{std::forward<Ts>(ts)...} { }

    std::shared_ptr<MsgBase> clone() const override {
        return std::make_shared<MsgImpl<Msg>>(msg);
    }

    void speak() override {
        msg.speak();
    }

    void happy() override {
        if constexpr ( requires {
            msg.happy();
        }) {
            msg.happy();
        } else {
            std::cout<< "no happy\n";
        }
    }
};
//#2.1 裸指针
//std::vector<MsgBase *> msgs;

//#2.2 智能指针
template<class Msg, class ...Ts>
std::shared_ptr<MsgBase> makeMsg(Ts &&...ts) {
    return std::make_shared<MsgImpl<Msg>>(std::forward<Ts>(ts)...);
}

std::vector<std::shared_ptr<MsgBase>> msgs;

int main() {

    // #1
    //msgs.push_back(MoveMsg{5, 10});
    //msgs.push_back(JumpMsg{20});
    //msgs.push_back({SleepMsg{8}});
    //msgs.push_back(ExitMsg{});
    // for (auto &msg:msgs) {
    //     std::visit([&](auto &msg){
    //         msg.speak();
    //     }, msg);
    //     //msgs.speak();
    // }

    //#2.1
    // msgs.push_back(new MsgImpl<MoveMsg>{5, 10});
    // msgs.push_back(new MsgImpl<JumpMsg>(20));
    // msgs.push_back(new MsgImpl<SleepMsg>(8));
    // msgs.push_back(new MsgImpl<ExitMsg>{});

    //#2.2
    msgs.push_back(makeMsg<MoveMsg>(5, 10));
    msgs.push_back(makeMsg<JumpMsg>(20));
    msgs.push_back(makeMsg<SleepMsg>(8));
    msgs.push_back(makeMsg<ExitMsg>());

    for (auto &msg:msgs) {
        msg->speak();
        msg->happy();
    }

    return 0;
}