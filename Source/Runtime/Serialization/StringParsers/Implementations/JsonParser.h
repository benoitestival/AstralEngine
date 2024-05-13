#pragma once
#include "../BaseStringParser.h"

class AJsonParser : public ABaseStringParser{
public:
    DECLARE_ASTRAL_ENGINE_CLASS(AJsonParser, ABaseStringParser)

    // std::string ReadDataFromFile(const std::string& FileName, ParserReadParams* SpecificParserParams) override;
    // virtual bool WriteDataTofile(const std::string& Data, const std::string& FileName, ParserWriteParams* SpecificParserParams) override;
};
