#include "jsonconfigurationparser.h"

#include "models/system.h"


#include <boost/filesystem.hpp>

#define RAPIDJSON_HAS_STDSTRING 1

#include <rapidjson/document.h>

#include <optional.hpp>


#include <initializer_list>
#include <iostream>
#include <list>
#include <sstream>
#include <vector>

using boost::filesystem::path;

using nonstd::nullopt;
using nonstd::optional;

using std::cout;
using std::endl;
using std::list;
using std::stringstream;
using std::string;
using std::vector;

namespace  {

    Result<string> loadValue(const rapidjson::Value& node, std::initializer_list<string> properties)
    {
        stringstream ss;
        rapidjson::Value const * propNode = &node;

        if (node.IsObject())
        {
            std::cout << "here" << std::endl;
        }
        if (node.IsNull())
        {
            std::cout << "NULL" << std::endl;
        }

        for (const auto& property : properties)
        {
            ss << "." << property;
            if (propNode == nullptr || !propNode->IsObject() || !propNode->HasMember(property))
            {
                return Result<string>::failure("Property " + ss.str() + " does not exist");
            }
            propNode = &((*propNode)[property]);
        }
        if (!propNode->IsString())
        {
            return Result<string>::failure("Property " + ss.str() + " is not a string");
        }
        return Result<string>::success(propNode->GetString());
    }

    Result<list<System>> loadSystems(const rapidjson::Value& systemsNode, const path& basePath)
    {
        if (systemsNode == NULL || !systemsNode.IsArray())
        {
            return  Result<list<System>>::failure("'systems' node is missing");
        }
        list<System> systems;
        for (const auto& systemNode : systemsNode.GetArray())
        {
            if (!(systemNode.IsObject() && systemNode.HasMember("name") && systemNode.HasMember("rom_folders")))
            {
                continue;
            }
            list<string> romFolders;
            for (const auto& folder : systemNode["rom_folders"].GetArray())
            {
                path p(folder.GetString());
                if (p.is_relative())
                {
                    path resolved = basePath / p;
                    p = resolved.normalize();
                }
                cout << "rom folder: " << p.string() << endl;
                romFolders.push_back(p.string());
            }
            System sys(systemNode["name"].GetString(), romFolders);
            systems.push_back(sys);
        }
        return Result<list<System>>::success(systems);
    }
}

Result<Configuration> JsonConfigurationParser::parseConfiguration(const string& configurationPath)
{
    // read file in buffer
    FILE* fp = fopen(configurationPath.c_str(), "r");
    if (fp == nullptr)
    {
        return Result<Configuration>::failure("Failed to open file " + configurationPath);
    }

    fseek(fp, 0, SEEK_END);
    size_t fileSize = static_cast<size_t>(ftell(fp));
    char* buffer = static_cast<char*>(malloc(sizeof (char) * (fileSize + 1)));
    size_t readLength = fread(buffer, 1, fileSize, fp);
    buffer[readLength] = '\0';
    fclose(fp);

    rapidjson::Document document;
    document.ParseInsitu(buffer);

    boost::filesystem::path p(configurationPath);

    auto parentPath = p.parent_path();
    std::cout << parentPath.string() << std::endl;
    
    const auto dbPath = loadValue(document, {"database_path"});
    if (dbPath.isFailure())
    {
        free(buffer);
        return Result<Configuration>::failure("Failed to parse database, reason: " + dbPath.getError());
    }

    const auto systems = loadSystems(document["system"], parentPath);

    if (systems.isFailure()) {
        free(buffer);
        return Result<Configuration>::failure("Failed to parse systems, reason: " + systems.getError());
    }

    Configuration config(
         dbPath.getValue(),
         systems.getValue());

    free(buffer);
    return Result<Configuration>::success(config);
}
