#pragma once
#include "../Utils/SerializationUtils.h"

template<class T>
class TSerializableField {
public:
    TSerializableField() {
        FieldKey = INVALID_STRING;
        FieldData = nullptr;
    }
    TSerializableField(T& Data) {
        FieldKey = INVALID_STRING;
        FieldData = &Data;
    }
    TSerializableField(T* Data) {
        FieldKey = INVALID_STRING;
        FieldData = Data;
    }
    TSerializableField(const std::string& Key, T& Data) {
        FieldKey = Key;
        FieldData = &Data;
    }
    TSerializableField(const std::string& Key, T* Data) {
        FieldKey = Key;
        FieldData = Data;
    }

    std::string Key() const {
        return FieldKey;
    }

    T* GetData() const{
        return FieldData;
    }

private:
    std::string FieldKey;
    T* FieldData;
};
