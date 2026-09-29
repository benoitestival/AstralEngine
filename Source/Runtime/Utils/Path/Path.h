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

/////////////////////////////////////////////////////////////////////////////////////////////

class FPath {
public:
    FPath();
    FPath(const std::string& PathIn);
    ~FPath();

    bool IsRelative() const;
    bool IsAbsolute() const; 

    bool IsFolder() const;
    bool HasExtension(const FPathExtension& Extension) const;
    
    FPath RemoveExtension() const;
    
    FPath operator+(const FPath& OtherPath) const;
    FPath operator+(const std::string& OtherString) const;
    FPath operator+(const FPathExtension& OtherExtension) const;
    
    std::string ToString() const;
private:
    std::filesystem::path ToStdPath() const;
    std::string PathString;
};

/////////////////////////////////////////////////////////////////////////////////////////////

class FPathIterator {
public:
    
    class Iterator {
    public:
        Iterator(std::filesystem::recursive_directory_iterator It);

        FPath operator*() const;
        Iterator& operator++();
        bool operator!=(const Iterator& Other) const;

    private:
        std::filesystem::recursive_directory_iterator InternIt;
    };
    
    FPathIterator();
    FPathIterator(const FPath& PathIn);
    
    Iterator begin() const;
    Iterator end() const;
    
private:
   FPath RootPath;
};

/////////////////////////////////////////////////////////////////////////////////////////////

class FPathUtils {
public:
    static FPath GetEnginePath();
    static FPath GetEngineContentPath();
    static FPath GetEngineRessourcePath();
    static FPath GetEngineShadersPath();
};
