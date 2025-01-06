#include "Path.h"

FPathExtension::FPathExtension() : FPathExtension(""){
}

FPathExtension::FPathExtension(const std::string& ExtensionIn) {
    PathExtension = ExtensionIn;
}

FPathExtension::~FPathExtension() {
}

std::string FPathExtension::ToString() const {
    return PathExtension;
}

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

FPath FPath::operator+(const FPath& OtherPath) {
    return FPath(PathString + "\\" + OtherPath.ToString());
}

FPath FPath::operator+(const std::string& OtherString) {
    return *this + FPath(OtherString);
}

FPath FPath::operator+(const FPathExtension& OtherExtension) {
    return FPath(PathString + "." + OtherExtension.ToString());
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

FPath FPathUtils::GetEngineRessourcePath() {
    return GetEnginePath() + "Ressources";
}

FPath FPathUtils::GetEngineShadersPath() {
    return GetEngineRessourcePath() + "Shaders" + "bin";
}
