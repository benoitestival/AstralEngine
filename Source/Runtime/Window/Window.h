#pragma once
#include "../Engine/CoreObjects/Objects/BaseObject.h"
#include "../Maths/Maths.h"

class AWindow : public ABaseObject {
public:
    
    DECLARE_ASTRAL_ENGINE_CLASS(AWindow, ABaseObject)

    virtual void Construct();
    virtual void Tick(float DeltaTime);
    virtual void Close();
    
    virtual void SetShowMouseCursor(bool CursorVisibility);

    virtual FVector2D GetWindowSize() const;
    
    virtual bool IsOpen() const;
};
