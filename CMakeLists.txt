cmake_minimum_required(VERSION 3.0.2)
project(snake)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_LINK_LIBS libncurses.so.6)
link_directories(/lib/x86_64-linux-gnu)

include_directories(include)
file(GLOB SOURCES "src/*.cpp")

add_executable(snake ${SOURCES})
target_link_libraries(snake ${PROJECT_LINK_LIBS})