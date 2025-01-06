
#include "GLFWWindow.h"

#include "../../Engine/Statics/GameplayStatics.h"

void AGLFWWindow::Construct() {
    AWindow::Construct();

    if (glfwInit()) {
        // glfwInitHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        // glfwInitHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        // glfwInitHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        
        Window = glfwCreateWindow(800, 800, "Window", nullptr, nullptr);
        if (Window != nullptr) {
            glfwMakeContextCurrent(Window);
            glfwSetWindowUserPointer(Window, GameplayStatics::GetEngine());
            
            //TODO Handle all the callbacks below
            glfwSetCursorEnterCallback(Window, [](GLFWwindow* PrivateWindow, int Entered) {
                //TODO

            });
            glfwSetWindowCloseCallback(Window, [](GLFWwindow* PrivateWindow) {
                //TODO

            });
            glfwSetWindowFocusCallback(Window, [](GLFWwindow* PrivateWindow, int Focused) {
                //TODO

            });

            glfwSetWindowMaximizeCallback(Window, [](GLFWwindow* PrivateWindow, int Maximize) {
                //TODO

            });

            glfwSetWindowSizeCallback(Window, [](GLFWwindow* PrivateWindow, int SizeX, int SizeY) {
                //TODO

            });
        }
        else {
            //TODO assert Engine failed to launch window
        }
    }
    else {
        //TODO assert failed to launch opengl
    }

}

void AGLFWWindow::Close() {
    AWindow::Close();
    glfwTerminate();
}

void AGLFWWindow::SetShowMouseCursor(bool CursorVisibility) {
    AWindow::SetShowMouseCursor(CursorVisibility);
    
    if (CursorVisibility) {
        glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
    else {
        glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    
}

FVector2D AGLFWWindow::GetWindowSize() const {
    int WindowWidth = 0;
    int WindowHeight = 0;
    glfwGetWindowSize(GetPrivateWindow(), &WindowWidth, &WindowHeight);
    return {(float)WindowWidth, (float)WindowWidth};
}

bool AGLFWWindow::IsOpen() const {
    return !glfwWindowShouldClose(Window);
}

GLFWwindow* AGLFWWindow::GetPrivateWindow() const {
    return Window;
}
