#pragma once

class AEngine;

class Application {
public:
    void Start();
    void End();

    static void Terminate();
    
    AEngine* GetEngine();
private:
    AEngine* Engine = nullptr;
};
