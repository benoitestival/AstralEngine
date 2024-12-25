#include "Path.h"

FPath::FPath() : FPath("") {
}

FPath::FPath(const std::string& PathIn) {
    PathString = PathIn;
}

FPath::~FPath() {
}

bool FPath::IsRelative() const {
    return ToStdPath().is_relative();
}

bool FPath::IsAbsolute() const {
    return ToStdPath().is_absolute();
}

std::string FPath::ToString() const {
    return PathString;
}

std::filesystem::path FPath::ToStdPath() const {
    return std::filesystem::path(PathString);
}

FPath FPathUtils::GetEnginePath() {
    std::filesystem::path CurrentPath = std::filesystem::current_path();
    return FPath(CurrentPath.parent_path().parent_path().string());
}
