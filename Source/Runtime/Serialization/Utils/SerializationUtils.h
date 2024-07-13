#pragma once
#include <sstream>

#define INVALID_STRING "INVALID"

enum class ENodeType {
    NT_NONE = 0,
    NT_ROOT = 1,
    NT_PARENT = 2,
    NT_LEAF = 3,
};

enum class EArchiveEntryType {
    AR_INVALID = 0,
    AR_KEY = 1,
    AR_VALUE = 2,
    AR_START_SUB_ARCHIVE = 3,
    AR_END_SUB_ARCHIVE = 4,
};

enum class EArchiveEntryTypeOption {
    AR_ARRAY_START = 0,
    AR_ARRAY_END = 0,
};

enum class EArchiveFlag {
    AR_NoFlags = 0x00000000,
    AR_Array = 0x00000001,
    //AR_SubArchive = 0x00000002,
};

enum class ENodeDataType {
    NT_RawString = 0,
    NT_SubNodes = 1,
};


template <typename T>
concept SupportStringSerialization = requires(std::stringstream& Stream, T& value) {
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
    std::stringstream& Stream() {
        return InternStream;
    }
private:
    std::stringstream InternStream;
};


class SerializationUtils {
public:
    
};
