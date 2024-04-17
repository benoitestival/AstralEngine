#pragma once
#include <filesystem>
#include <string>

class FilerHelpers {
public:
    static std::string BinaryDirectory;
    static std::filesystem::path GetProjectDirectory();
    static std::string GetProjectDirectoryAsString();
};
