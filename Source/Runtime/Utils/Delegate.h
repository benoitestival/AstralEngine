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
    int Bind(T* Instance, void(T::*Func)(Args...)) {
        return Bind([=](Args... _args) {
            (Instance->*Func)(_args...);
        });
    }

    //Handle Lambda and static function
    int Bind(const std::function<void(Args...)>& Func){
        CallBacks.insert({ CurrentId++, Func });
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

    static Delegate<Args...> FromLambda(const std::function<void(Args...)>& Lambda) {
        Delegate<Args...> ResultDelegate = Delegate<Args...>();
        ResultDelegate.Bind(Lambda);
        return ResultDelegate;
    }
    
    template<typename T>
    static Delegate<Args...> FromObject(T* Instance, void(T::*Func)(Args...)) {
        Delegate<Args...> ResultDelegate = Delegate<Args...>();
        ResultDelegate.Bind(Instance, Func);
        return ResultDelegate;
    }
	
private:
    std::map<int, std::function<void(Args...)>> CallBacks;
    int CurrentId;
};