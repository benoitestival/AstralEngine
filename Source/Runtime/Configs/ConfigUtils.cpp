#include "ConfigUtils.h"

#include "../Engine/Implementations/SFMLEngine.h"


FClass* ConfigUtils::GetEngineClass() {
    return ASFMLEngine::StaticClass();
}
