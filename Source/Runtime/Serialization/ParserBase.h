#pragma once
#include <sstream>

#include "../Core/Objects/BaseObject.h"
#include "../Utils/TemplateUtils.h"

struct ParserReadParams {
    //inherit in parser subclass to pass dynamic params to write to file
    //Never forget to clean the struct once the usage is done because struct pointer are not handled automatically
};


struct ParserWriteParams {
    //inherit in parser subclass to pass dynamic params to write to file
    //Never forget to clean the struct once the usage is done because struct pointer are not handled automatically
};

class AParserBase : public ABaseObject {
public:
    DECLARE_ASTRAL_ENGINE_CLASS(AParserBase, ABaseObject)

};
