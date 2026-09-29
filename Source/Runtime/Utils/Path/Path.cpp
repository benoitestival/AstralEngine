#include "Path.h"

/////////////////////////////////////////////////////////////////////////////////////////////

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

/////////////////////////////////////////////////////////////////////////////////////////////

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

bool FPath::IsFolder() const {
   return std::filesystem::is_directory(ToStdPath());
}

bool FPath::HasExtension(const FPathExtension& Extension) const {
    std::filesystem::path StdPath = ToStdPath();
    return StdPath.has_extension() && StdPath.extension() == Extension.ToString();
}

FPath FPath::RemoveExtension() const {
    std::filesystem::path StdPath = ToStdPath();
    StdPath.replace_extension("");   // "Texture.json.meta" → "Texture.json"
    return FPath(StdPath.string());
}

FPath FPath::operator+(const FPath& OtherPath) const{
    return FPath(PathString + "\\" + OtherPath.ToString());
}

FPath FPath::operator+(const std::string& OtherString) const{
    return *this + FPath(OtherString);
}

FPath FPath::operator+(const FPathExtension& OtherExtension) const{
    return FPath(PathString + "." + OtherExtension.ToString());
}

std::string FPath::ToString() const {
    return PathString;
}

std::filesystem::path FPath::ToStdPath() const {
    return std::filesystem::path(PathString);
}

/////////////////////////////////////////////////////////////////////////////////////////////

FPathIterator::Iterator::Iterator(std::filesystem::recursive_directory_iterator It)  : InternIt(It) {
}

FPath FPathIterator::Iterator::operator*() const {
    return FPath(InternIt->path().string());
}

FPathIterator::Iterator& FPathIterator::Iterator::operator++() {
    ++InternIt; 
    return *this;
}

bool FPathIterator::Iterator::operator!=(const Iterator& Other) const {
    return InternIt != Other.InternIt;
}

FPathIterator::FPathIterator() : FPathIterator(FPath()){
}

FPathIterator::FPathIterator(const FPath& PathIn) : RootPath(PathIn){
}

FPathIterator::Iterator FPathIterator::begin() const {
    return FPathIterator::Iterator(std::filesystem::recursive_directory_iterator(RootPath.ToString()));
}

FPathIterator::Iterator FPathIterator::end() const {
    return FPathIterator::Iterator(std::filesystem::recursive_directory_iterator());
}

/////////////////////////////////////////////////////////////////////////////////////////////

FPath FPathUtils::GetEnginePath() {
    std::filesystem::path CurrentPath = std::filesystem::current_path();
    return FPath(CurrentPath.parent_path().parent_path().string());//For IDE
    //return FPath(CurrentPath.parent_path().parent_path().parent_path().string());//For Exe
}

FPath FPathUtils::GetEngineContentPath() {
    return GetEnginePath() + "Content";
}

FPath FPathUtils::GetEngineRessourcePath() {
    return GetEnginePath() + "Ressources";
}

FPath FPathUtils::GetEngineShadersPath() {
    return GetEngineRessourcePath() + "Shaders" + "bin";
}
