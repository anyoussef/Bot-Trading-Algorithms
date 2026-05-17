cmake_minimum_required(VERSION 3.20)
project(alpaca_client)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)  # <-- this is the key line for clangd

find_package(CURL REQUIRED)
find_package(nlohmann_json REQUIRED)

add_executable(alpaca_client src/main.cpp)

target_link_libraries(alpaca_client PRIVATE
    CURL::libcurl
    nlohmann_json::nlohmann_json
)
