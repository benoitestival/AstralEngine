#pragma once
#include <sstream>
#include <string>
#include <unordered_map>


template <typename T>
concept SupportSerialization = requires(std::stringstream& Stream, T value) {
    { Stream << value } -> std::convertible_to<std::ostream&>;
    { Stream >> value } -> std::convertible_to<std::istream&>;
};

struct FStream {
public:
    FStream() = default;
    FStream(const std::string& String) : InternStream(String) {}
    std::string ToString() {
        return InternStream.str();
    }
public:
    std::stringstream InternStream;
};

struct FArchive {
public:
    FArchive() = default;

    template<SupportSerialization T>
    void AddField(const std::string& FieldID, T& FieldValue) {
        ArchiveDatas.insert(std::make_pair(FieldID, DataAsString(FieldValue)));
    }

    template<SupportSerialization T>
    T GetField(const std::string& FieldID) {
        return DataFromString<T>(ArchiveDatas.at(FieldID));
    }
private:
    template<SupportSerialization T>
    FArchive& operator<<(T& Value) {
        FStream Stream = FStream();
        Stream.InternStream << Value;
        return *this;
    }

    template<SupportSerialization T>
    FArchive& operator>>(T& Value) {
        DataStream.InternStream >> Value;
        return *this;
    }
    template<class T>
    std::string DataAsString(T& FieldValue) {
        return (*this << FieldValue).str();
    }
    template<class T>
    T DataFromString(std::string& FieldValue) {
        T Data = T();
        *this >> Data;
        return Data;
    }

private:
    FStream DataStream;
    std::unordered_map<std::string, std::string> ArchiveDatas;
};



