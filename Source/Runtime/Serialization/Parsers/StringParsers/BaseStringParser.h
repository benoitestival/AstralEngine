#pragma once
#include "../ParserBase.h"
//#include "../Archive.h"

class ABaseStringParser : public AParserBase {
public:

    DECLARE_ASTRAL_ENGINE_CLASS(ABaseStringParser, AParserBase)
    
    //read all datas from a file
    virtual std::string ReadDataFromFile(const std::string& FileName, ParserReadParams* SpecificParserParams) = 0;

    // template<class T>
    // T ReadDataFromFile(const std::string& FileName, ParserReadParams* SpecificParserParams) {
    //     return SerializeType<T>::FromString(ReadDataFromFile(FileName, SpecificParserParams));;
    // }
    //
    // //Here all data have already bean convert to string for easyer serialization
    // virtual bool WriteDataTofile(const std::string& Data, const std::string& FileName, ParserWriteParams* SpecificParserParams) = 0;
    //
    // template<class T>
    // bool WriteDataToFile(const T& Data, const std::string& FileName, ParserWriteParams* SpecificParserParams) {
    //     return WriteDataTofile(SerializeType<T>::ToString(Data), FileName, SpecificParserParams);
    // }
};
