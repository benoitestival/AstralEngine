#include "FilerHelpers.h"

std::string FilerHelpers::BinaryDirectory = "out/binaries";

std::filesystem::path FilerHelpers::GetProjectDirectory() {
    std::filesystem::path OffsetPath = FilerHelpers::BinaryDirectory;
    int PathLenght = 1; //init to one because there is always one folder
    while (OffsetPath.has_parent_path()) {
        OffsetPath = OffsetPath.parent_path();
        PathLenght++;
    }

    std::filesystem::path CurrentPath = std::filesystem::current_path();
    while (PathLenght > 0) {
        CurrentPath = CurrentPath.parent_path();
        PathLenght--;
    }
    return CurrentPath;
}

std::string FilerHelpers::GetProjectDirectoryAsString() {
    return FilerHelpers::GetProjectDirectory().string();
}
