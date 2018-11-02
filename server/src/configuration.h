#pragma once

#include "models/system.h"

#include <list>
#include <string>

class Configuration
{

public:
    Configuration(
            const std::string& dbPath,
            const std::list<System>& systems);

    const std::string& dbPath() const { return m_dbPath; }

    const std::list<System> systems() const { return m_systems; }

private:
    std::string m_dbPath;
    std::list<System> m_systems;
};
