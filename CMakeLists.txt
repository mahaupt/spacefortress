cmake_minimum_required(VERSION 3.1.0)
project (sf)

#set variables
set (CMAKE_PROJECT_VERSION 0.0.9)
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_BUILD_TYPE Debug)
#set (CMAKE_BUILD_TYPE RelWithDebInfo)
set (CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(THREADS_PREFER_PTHREAD_FLAG ON)
set(CURSES_NEED_NCURSES TRUE)
set(CURSES_NEED_WIDE TRUE)

#external packages
find_package(Curses REQUIRED)
find_package(Threads REQUIRED)
add_subdirectory(yaml-cpp)
include_directories(
  ${CURSES_INCLUDE_DIR}
  "yaml-cpp/include"
)

#check ncursesw
message(STATUS "CURSES_LIBRARIES: ${CURSES_LIBRARIES}")
message(STATUS "CURSES_INCLUDE: ${CURSES_INCLUDE_DIR}")

#build files
file(GLOB_RECURSE SF_SRC
    "src/*.cpp"
)

add_executable(
    sf
    ${SF_SRC}
)

target_link_libraries(
    sf
    ${CURSES_LIBRARIES}
    yaml-cpp
    Threads::Threads
)

#copy config and language files
#file(COPY lang DESTINATION .)
configure_file(lang/en.yaml lang/en.yaml COPYONLY)
configure_file(lang/de.yaml lang/de.yaml COPYONLY)
configure_file(config.yaml config.yaml COPYONLY)
