#pragma once

class ARenderManager;
class AInpuManager;
class AEngine;

class GameplayStatics {
public:
    static AEngine* GetEngine();
    static AInpuManager* GetInputManager();
    static ARenderManager* GetRenderManager();
    static float GetDeltaTime();
};
