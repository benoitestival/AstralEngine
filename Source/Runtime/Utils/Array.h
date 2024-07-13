#pragma once
#include <vector>
#include <utility>

template<class T>
class TArray{
public:
    ///////CONSTRUCTORS//////
    TArray() {
        InternVector = {};
    }
    TArray(const std::vector<T>& Vector) : InternVector(Vector) {};
    TArray(const std::initializer_list<T>& List) : InternVector(List) {};

    ///////COPY CONSTRUCTOR///////
    TArray(const TArray<T>& Array) : InternVector(Array.ToSTDVector()) {};

    ///////MOVE CONSTRUCTOR///////
    TArray(TArray<T>&& Array) noexcept : InternVector(std::move(Array.ToSTDVector())) {}
    
    ///////DESTRUCTOR////////
    ~TArray() {
        InternVector.clear();
    }

    ///////OPERATOR = ///////
    TArray<T>& operator=(const TArray<T>& Array) {
        if (this != &Array) {
            InternVector = Array.ToSTDVector();
        }
        return *this;
    }
    TArray<T>& operator=(TArray<T>&& Array) noexcept {
        if (this != &Array) {
            InternVector = std::move(Array.ToSTDVector());
        }
        return *this;
    }
    TArray<T>& operator=(const std::initializer_list<T>& List){
        InternVector = List;
        return *this;
    }

    //////OPERTAOR [] ///////
    T& operator[](size_t index) {
        return ToSTDVector()[index];
    }

    const T& operator[](size_t index) const {
        return ToSTDVector()[index];
    }

    ///////ITERATORS///////
    auto begin() {
        return ToSTDVector().begin();
    }
    auto begin() const {
        return ToSTDVector().begin();
    }
    
    auto end() {
        return ToSTDVector().end();
    }
    auto end() const {
        return ToSTDVector().end();
    }
    
    ////////METHODS////////
    void Add(const T& Element) {
        return ToSTDVector().push_back(Element);
    }

    void Append(const TArray<T>& Array) {
        ToSTDVector().insert(end(), Array.begin(), Array.end());
    }
    
    bool Remove(const T& element) {
        bool SuccessfullyRemove = false;
        auto Iterator = std::find(begin(), end(), element);
        if (Iterator != end()) {
            ToSTDVector().erase(Iterator);
            SuccessfullyRemove = true;
        }
        return SuccessfullyRemove;
    }
    
    template<class CompareType>
    bool RemoveByKey(const CompareType& element) {
        bool SuccessfullyRemove = false;
        auto Iterator = std::find(begin(), end(), element);
        if (Iterator != end()) {
            ToSTDVector().erase(Iterator);
            SuccessfullyRemove = true;
        }
        return SuccessfullyRemove;
    }

    bool RemoveAt(int Index) {
        bool SuccessfullyRemove = false;
        if (Index >= LastIndex()) {
            ToSTDVector().erase(begin() + Index);
            SuccessfullyRemove = true;
        }
        return SuccessfullyRemove;
    }

    void Clear() {
        ToSTDVector().clear();
    }
    
    template<class CompareType>
        bool Contains(CompareType element) const {
        auto Iterator = std::find(begin(), end(), element);
        return Iterator != end();
    }

    int Lenght() {
        return ToSTDVector().size();
    }
    
    int LastIndex() {
        return Lenght() - 1;
    }
    
    T& Last() {
        return *this[LastIndex()];
    }

    //ONLY FOR OUTSIDE OF TARRAY
    std::vector<T>& ToSTDVector(){
        return InternVector;
    }
    const std::vector<T>& ToSTDVector() const{
        return InternVector;
    }
private:
    std::vector<T> InternVector;
};
