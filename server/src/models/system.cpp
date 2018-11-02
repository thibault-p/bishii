#include "system.h"

System::System(std::string name, std::list<std::string> romFolders) :
    name(name), romFolders(romFolders)
{}

const std::list<std::string>& System::getRomFolders() const {
    return romFolders;
}
