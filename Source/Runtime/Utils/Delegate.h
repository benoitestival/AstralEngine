#pragma once
#include <map>
#include <functional>

#define DECLARE_DELEGATE(DelegateName, ...) using DelegateName = Delegate<__VA_ARGS__>;

/**
 * Very simple implementation of delegate system
 */
template<typename ...Args>
class Delegate {

public:
    Delegate() : CurrentId(0){
    }
    ~Delegate() {
        UnbindAll();
    }
    
    //Handle member functions
    template<typename T>
    int Bind(T* Instance, void(T::*func)(Args...)) {
        return Bind([=](Args... _args) {
            (Instance->*func)(_args...);
        });
    }

    //Handle Lambda and static function
    int Bind(const std::function<void(Args...)>& _slot){
        CallBacks.insert({ CurrentId++, _slot });
        return CurrentId;
    }
	
    void Unbind(int Id) {
        CallBacks.erase(Id);
        CurrentId--;
    }
    void UnbindAll() {
        CallBacks.clear();
        CurrentId = 0;
    }
    void BroadCast(Args... Params) {
        for (auto& Slot : CallBacks) {
            Slot.second(Params...);
        }
    }
	
private:
    std::map<int, std::function<void(Args...)>> CallBacks;
    int CurrentId;
};