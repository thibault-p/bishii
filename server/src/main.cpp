#include "jsonconfigurationparser.h"



#include <iostream>


using std::cout;
using std::cerr;
using std::endl;

int main(int argc, char* argv[])
{

    if (argc < 2)
    {
        cerr << "Missing argument" << endl;
        cout << "Usage: " << argv[0] << " <configuration_file>" << endl;
        return 1;
    }


    auto resConfiguration = JsonConfigurationParser::parseConfiguration(argv[1]);

    if (resConfiguration.isFailure())
    {
        cerr << "Failed to initialize configuration, reason: \n\t" << resConfiguration.getError() << endl;
        return 1;
    }

    const auto configuration = resConfiguration.getValue();

    cout << "Configuration parsed. " << configuration.systems().size() << " systems found" << endl;

    return 0;
}
