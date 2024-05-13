#pragma once
#include <sstream>
#include <string>
#include <unordered_map>


class ISerializable {
public:
    
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

template <typename T>
concept SupportSerialization = requires(std::stringstream& Stream, T value) {
    { Stream << value } -> std::convertible_to<std::ostream&>;
    { Stream >> value } -> std::convertible_to<std::istream&>;
};

struct FArchive {
public:
    FArchive() = default;

    template<class T = ISerializable>
    void AddField(const std::string& FieldID, T& FieldValue) {
        
    }
    template<class T = ISerializable>
    T GetField(const std::string& FieldID) {
        
    }
    
    template<SupportSerialization T>
    void AddField(const std::string& FieldID, T& FieldValue) {
        ArchiveDatas.insert(std::make_pair(FieldID, DataAsString(FieldValue)));
    }

    template<SupportSerialization T>
    T GetField(const std::string& FieldID) {
        return DataFromString<T>(ArchiveDatas.at(FieldID));
    }
private:
    template<class T>
    std::string DataAsString(T& FieldValue) {
        FStream Stream = FStream();
        Stream.InternStream << FieldValue;
        return Stream.ToString();
    }
    template<class T>
    T DataFromString(std::string& FieldValue) {
        T Data = T();
        FStream(FieldValue).InternStream >> Data;
        return Data;
    }

private:
    std::unordered_map<std::string, std::string> ArchiveDatas;
};



