#pragma once
#include "../../Utils/Path/Path.h"

class ARenderer;
class ATimerManager;
class ARenderManager;
class AInputManager;
class AEngine;

class GameplayStatics {
public:
    static AEngine* GetEngine();
    static AInputManager* GetInputManager();
    static ARenderer* GetRenderManager();
    static ATimerManager* GetTimerManager();
    static float GetDeltaTime();

    static void SetShowMouseCursor(bool CursorVisibility);
    static bool ShowMouseCursor();

    static FPath GetEnginePath();
};
