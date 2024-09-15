#pragma once
#include <GLFW/glfw3.h>

#include "../Window.h"

class AOpenGLWindow : public AWindow{
public:
    DECLARE_ASTRAL_ENGINE_CLASS(AOpenGLWindow, AWindow)

    virtual void Construct() override;
    virtual void Close() override;
    
    virtual bool IsOpen() const override;

    GLFWwindow* GetPrivateWindow();
private:
    GLFWwindow* Window = nullptr;
    
};
