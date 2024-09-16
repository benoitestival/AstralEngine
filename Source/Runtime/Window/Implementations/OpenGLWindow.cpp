
#include "OpenGLWindow.h"

#include "../../Engine/Statics/GameplayStatics.h"

void AOpenGLWindow::Construct() {
    AWindow::Construct();

    if (glfwInit()) {
        glfwInitHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwInitHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwInitHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        
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

void AOpenGLWindow::Close() {
    AWindow::Close();
    glfwTerminate();
}

bool AOpenGLWindow::IsOpen() const {
    return !glfwWindowShouldClose(Window);
}

GLFWwindow* AOpenGLWindow::GetPrivateWindow() {
    return Window;
}
