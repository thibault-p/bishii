#pragma once

#include "game.h"

#include <list>
#include <string>


class System
{
public:
    System(std::string name, std::list<std::string> romFolders);
    
    const std::list<std::string>& getRomFolders() const;


private:
    std::string name;
    std::list<std::string> romFolders;
};
