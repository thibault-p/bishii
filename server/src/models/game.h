#pragma once

#include <string>
#include <vector>


class Game
{
public:
    Game(unsigned int id, const std::string& name, const std::string& romPath, const std::vector<uint32_t>& imgData);

    unsigned int id() const  { return m_id; }

    const std::string& name() const { return m_name; }

    const std::string& romPath() const  { return m_romPath; }

    const std::vector<uint32_t>& image() const { return m_imgData; }

private:
    unsigned int m_id;
    std::string m_name;
    std::string m_romPath;
    std::vector<uint32_t> m_imgData;
};
