#pragma once

#include "configuration.h"
#include "result.h"

#include <string>


class JsonConfigurationParser
{
public:
    static Result<Configuration> parseConfiguration(const std::string& configPath);
};
