#pragma once

class ATimerManager;
class ARenderManager;
class AInputManager;
class AEngine;

class GameplayStatics {
public:
    static AEngine* GetEngine();
    static AInputManager* GetInputManager();
    static ARenderManager* GetRenderManager();
    static ATimerManager* GetTimerManager();
    static float GetDeltaTime();
};
