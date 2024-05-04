#pragma once
#include <vector>

template<class T>
class TArray : public std::vector<T>{
public:
    ///////CONSTRUCTORS//////
    TArray() : std::vector<T>() {};
    
    TArray(const std::vector<T>& Vector) : std::vector<T>(Vector) {};
    TArray(const TArray<T>& Array) : std::vector<T>(Array) {
        //Add Array special logic here if needed
    };
    
    TArray(std::vector<T>&& Vector) noexcept : std::vector<T>(std::move(Vector)) {};
    TArray(TArray<T>&& Array) noexcept : std::vector<T>(std::move(Array)) {
        //Add Array special logic here if needed
    };
    
    TArray(const std::initializer_list<T>& List) : std::vector<T>(List){};
    /////////////////////////

    bool Remove(T element) {
        bool SuccessfullyRemove = false;
        auto Iterator = std::find(std::vector<T>::begin(), std::vector<T>::end(), element);
        if (Iterator != std::vector<T>::end()) {
            std::vector<T>::erase(Iterator);
            SuccessfullyRemove = true;
        }
        return SuccessfullyRemove;
    }
};
