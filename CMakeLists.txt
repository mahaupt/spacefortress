cmake_minimum_required(VERSION 2.8.9)
project (spacefortress)

#set variables
set (CMAKE_CXX_STANDARD 17)
#set(CMAKE_BUILD_TYPE debug)

#external packages
find_package(Curses REQUIRED)
add_subdirectory(yaml-cpp)
include_directories(
  ${CURSES_INCLUDE_DIR}
  "yaml-cpp/include"
)

#build files
file(GLOB_RECURSE SF_SRC
    "src/*.cpp"
)

add_executable(
    spacefortress
    ${SF_SRC}
)

target_link_libraries(
    spacefortress
    ${CURSES_LIBRARIES}
    yaml-cpp
)
