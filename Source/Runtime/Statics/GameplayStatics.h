#pragma once

class AInpuManager;
class AEngine;

class GameplayStatics {
public:
    static AEngine* GetEngine();
    static AInpuManager* GetInputManager();
};
