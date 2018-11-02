#include "configuration.h"

using std::list;

Configuration::Configuration(
        const std::string& dbPath, const std::list<System>& systems) :
    m_dbPath(dbPath),
    m_systems(systems)
{}
