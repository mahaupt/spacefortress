cmake_minimum_required(VERSION 2.8.9)
project (spacefortress)

#set variables
set (CMAKE_PROJECT_VERSION 0.0.9)
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_BUILD_TYPE debug)
set (DCMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CURSES_NEED_NCURSES TRUE)
set(CURSES_NEED_WIDE TRUE)

#external packages
find_package(Curses REQUIRED)
add_subdirectory(yaml-cpp)
include_directories(
  ${CURSES_INCLUDE_DIR}
  "yaml-cpp/include"
)

message(STATUS "CURSES_LIBRARIES: ${CURSES_LIBRARIES}")
message(STATUS "CURSES_INCLUDE: ${CURSES_INCLUDE_DIR}")

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
