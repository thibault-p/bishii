cmake_minimum_required(VERSION 3.1)

project(bishii_server VERSION 0.1.0)

set (CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)


find_package(Boost 1.56 REQUIRED COMPONENTS system filesystem)

add_executable(bishii_server
    src/configuration.cpp
    src/configuration.h
    src/jsonconfigurationparser.cpp
    src/jsonconfigurationparser.h
    src/main.cpp
    src/result.h
    src/models/game.cpp
    src/models/game.h
    src/models/system.cpp
    src/models/system.h)


set_target_properties (bishii_server
    PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    )

target_include_directories (bishii_server
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/libs/optional-lite/include/nonstd
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/libs/rapidjson/include
    PRIVATE ${Boost_INCLUDE_DIRS}
)

target_link_libraries(bishii_server
    ${Boost_LIBRARIES})


target_compile_definitions(bishii_server
    PRIVATE RAPIDJSON_HAS_STDSTRING=1)
