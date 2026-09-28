#pragma once

#include "SerializationCoreIncludes.h"

class FArchive;

enum class EChecksumType : uint8_t {
    ECT_CRC32 = 0,
    ECT_XXHASH32 = 1,
    ECT_XXHASH64 = 2,
    ECT_HMAC = 3,
};

template <typename T>
concept SupportStringSerialization = requires(std::stringstream& Stream, T& value) {
    { Stream << value } -> std::convertible_to<std::ostream&>;
    { Stream >> value } -> std::convertible_to<std::istream&>;
};

template <typename T>
concept ImplementSpecificSerialization = requires(FArchive& Archive, T& Value) {
    {Value.Serialize(Archive)};
    {Value.DeSerialize(Archive)};
};

template <typename T>
concept IsBasicType = std::is_same_v<T, int> || std::is_same_v<T, float> || std::is_same_v<T, std::string> || std::is_same_v<T, bool>;

class SerializationUtils {
public:
    static void BuildCRC32Registry();
    static uint32_t BuildCRC32(const TArray<char>& Buffer);
private:
    static TArray<uint32_t> CRC32Table;
};

