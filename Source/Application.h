#pragma once

class AEngine;

class Application {
public:
    void Start();
    void End();

    AEngine* GetEngine();
private:
    AEngine* Engine = nullptr;
};
