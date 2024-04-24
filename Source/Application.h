#pragma once

class AEngine;

class Application {
public:
    void Start();
    void End();

private:
    AEngine* Engine = nullptr;
};
