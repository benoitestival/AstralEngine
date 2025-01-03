#pragma once
#include <string>
#include <filesystem>

#define MAKE_FILE_PATH(FolderPath, FileName, FileExtension)\
    FPath(FolderPath + FileName + FPathExtension(FileExtension))

struct FPathExtension {
public:
    FPathExtension();
    FPathExtension(const std::string& ExtensionIn);
    ~FPathExtension();

    std::string ToString() const;
private:
    std::string PathExtension;
};

class FPath {
public:
    FPath();
    FPath(const std::string& PathIn);
    ~FPath();

    bool IsRelative() const;
    bool IsAbsolute() const; 

    FPath operator+(const FPath& OtherPath);
    FPath operator+(const std::string& OtherString);
    FPath operator+(const FPathExtension& OtherExtension);
    
    std::string ToString() const;
private:
    std::filesystem::path ToStdPath() const;
    std::string PathString;
};

class FPathUtils {
public:
    static FPath GetEnginePath();
    static FPath GetEngineRessourcePath();
    static FPath GetEngineShadersPath();
};
