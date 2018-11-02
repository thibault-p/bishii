#include "game.h"

Game::Game(
        unsigned int id,
        const std::string& name,
        const std::string& romPath,
        const std::vector<uint32_t>& imgData) :
    m_id(id), m_name(name), m_romPath(romPath), m_imgData(imgData)
{}
