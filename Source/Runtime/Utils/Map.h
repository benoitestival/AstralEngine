#pragma once
#include <unordered_map>

template<class K, class T>
class TMap{
public:
    ///////CONSTRUCTORS//////
    TMap() {
        InternMap = {};
    }
    TMap(const std::unordered_map<K, T>& Map) : InternMap(Map) {};
    TMap(const std::initializer_list<std::pair<const K, T>>& List) : InternMap(List) {};

    ///////COPY CONSTRUCTOR///////
    TMap(const TMap<K, T>& Map) : InternMap(Map.ToSTDUnorderedMap()) {};

    ///////MOVE CONSTRUCTOR///////
    TMap(TMap<K, T>&& Map) noexcept : InternMap(std::move(Map.ToSTDUnorderedMap())) {}
    
    ///////DESTRUCTOR////////
    ~TMap() {
        InternMap.clear();
    }

    ///////OPERATOR = ///////
    TMap<K, T>& operator=(const TMap<K, T>& Map) {
        if (this != &Map) {
            InternMap = Map.ToSTDUnorderedMap();
        }
        return *this;
    }
    TMap<K, T>& operator=(TMap<K, T>&& Map) noexcept {
        if (this != &Map) {
            InternMap = std::move(Map.ToSTDUnorderedMap());
        }
        return *this;
    }
    TMap<K, T>& operator=(const std::initializer_list<std::pair<const K, T>>& List){
        InternMap = List;
        return *this;
    }

    //////OPERTAOR [] ///////
    T& operator[](const K& Key) {
        return ToSTDUnorderedMap()[Key];
    }

    const T& operator[](const K& Key) const {
        return ToSTDUnorderedMap()[Key];
    }

    ///////ITERATORS///////
    auto begin() {
        return ToSTDUnorderedMap().begin();
    }
    auto begin() const {
        return ToSTDUnorderedMap().begin();
    }
    
    auto end() {
        return ToSTDUnorderedMap().end();
    }
    auto end() const {
        return ToSTDUnorderedMap().end();
    }

    ////////METHODS////////
    T& Find(const K& Key) {
        return ToSTDUnorderedMap().at(Key);
    }

    const T& Find(const K& Key) const {
        return ToSTDUnorderedMap().at(Key);
    }

    void Insert(const std::pair<K, T>& Pair) {
        ToSTDUnorderedMap().insert(Pair);
    }

    void Remove(const K& Key) {
        ToSTDUnorderedMap().erase(Key);
    }

    
    void RemoveValue(const T& Value) {
        TArray<K> KeysToRemove = TArray<K>();
        for (auto& Pair : *this) {
            if (Pair.second == Value) {
                KeysToRemove.Add(Pair.first);
            }
        }
        for (auto& KeyToRemove : KeysToRemove) {
            Remove(KeyToRemove);
        }
    }

    bool Contains(const K& Key) const {
        return ToSTDUnorderedMap().contains(Key);
    }

    void Clear() {
        ToSTDUnorderedMap().clear();
    }

    int Lenght() const {
        return ToSTDUnorderedMap().size();
    }

    std::unordered_map<K, T>& ToSTDUnorderedMap(){
        return InternMap;
    }
    const std::unordered_map<K, T>& ToSTDUnorderedMap() const{
        return InternMap;
    }

private:
    std::unordered_map<K, T> InternMap;
};

