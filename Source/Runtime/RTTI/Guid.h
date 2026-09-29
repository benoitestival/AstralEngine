#pragma once
#include <cstdint>
#include <random>

struct FGuid {
    
    static FGuid Generate() {
        FGuid ID;
        
        ID.FirstByte = GenerateRandomNumber();
        ID.SecondByte = GenerateRandomNumber();
        ID.ThirdByte = GenerateRandomNumber();
        ID.FourthByte = GenerateRandomNumber();
        
        ID.SecondByte = (ID.SecondByte & 0x0FFFFFFF) | (4 << 28);
        ID.ThirdByte = (ID.ThirdByte & 0x3FFFFFFF) | (2 << 30);
        
        return ID;
    }
    
private:
    static uint32_t GenerateRandomNumber() {
        static std::mt19937 Generator(std::random_device{}());
        static std::uniform_int_distribution<uint32_t> Distribution(std::numeric_limits<uint32_t>::min(),std::numeric_limits<uint32_t>::max());
        return Distribution(Generator);
    }

private:
    uint32_t FirstByte;
    uint32_t SecondByte;
    uint32_t ThirdByte;
    uint32_t FourthByte;
};
