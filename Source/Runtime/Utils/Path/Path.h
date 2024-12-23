#pragma once
#include <string>
#include <filesystem>

class FPath {
public:
    FPath();
    FPath(const std::string& PathIn);
    ~FPath();

    bool IsRelative() const;
    bool IsAbsolute() const; 
    
private:
    std::filesystem::path ToStdPath() const;
    std::string PathString;
};

class FPathUtils {
public:
    static FPath GetEnginePath();
};
