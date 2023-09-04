cmake_minimum_required(VERSION 3.26.4)
project(rule-of-5 VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost 1.82.0 REQUIRED system filesystem)

add_executable(rule-of-5 main.cpp)
target_link_libraries(rule-of-5 PRIVATE Boost::headers Boost::system Boost::filesystem)
