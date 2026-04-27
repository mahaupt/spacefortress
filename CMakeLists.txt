cmake_minimum_required(VERSION 3.14.0)

#set variables
set (CMAKE_PROJECT_VERSION 0.0.9)
set (CMAKE_CXX_STANDARD 17)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

#set project variables
project (sf)
set (CMAKE_EXPORT_COMPILE_COMMANDS 1)
if ( CMAKE_COMPILER_IS_GNUCC )
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-unused-parameter")
endif()
set(THREADS_PREFER_PTHREAD_FLAG ON)
set(CURSES_NEED_WIDE TRUE)

#external packages
include(FetchContent)

if(MSVC)
  FetchContent_Declare(
    pdcurses
    GIT_REPOSITORY https://github.com/wmcbrine/PDCurses.git
    GIT_TAG 618e0aaa31b4728eb4df78ec4de6c2b873908eda
  )
  FetchContent_GetProperties(pdcurses)
  if(NOT pdcurses_POPULATED)
    FetchContent_Populate(pdcurses)
  endif()

  add_custom_target(
   PDCurses
   COMMAND nmake -f Makefile.vc WIDE=Y UTF8=Y
   WORKING_DIRECTORY "${pdcurses_SOURCE_DIR}/Wincon"
  )
  set(CURSES_LIBRARIES "${pdcurses_SOURCE_DIR}/Wincon/pdcurses.lib")
  set(CURSES_INCLUDE_DIR "${pdcurses_SOURCE_DIR}")
else()
  find_package(PkgConfig QUIET)
  if(PkgConfig_FOUND)
    pkg_check_modules(NCURSESW QUIET IMPORTED_TARGET ncursesw)
  endif()

  if(NCURSESW_FOUND)
    find_library(
      NCURSESW_LIBRARY
      NAMES ncursesw ncurses
      HINTS
        ${NCURSESW_LIBRARY_DIRS}
        /opt/homebrew/opt/ncurses/lib
        /usr/local/opt/ncurses/lib
    )

    if(NCURSESW_LIBRARY)
      set(CURSES_LIBRARIES ${NCURSESW_LIBRARY})
      set(CURSES_INCLUDE_DIR ${NCURSESW_INCLUDE_DIRS})
      set(CURSES_CFLAGS_OTHER ${NCURSESW_CFLAGS_OTHER})
    else()
      set(CURSES_LIBRARIES PkgConfig::NCURSESW)
    endif()
  else()
    find_package(Curses REQUIRED)
  endif()
endif()

find_package(Threads REQUIRED)
find_package(yaml-cpp QUIET CONFIG)
if(TARGET yaml-cpp::yaml-cpp)
  set(YAML_CPP_TARGET yaml-cpp::yaml-cpp)
elseif(TARGET yaml-cpp)
  set(YAML_CPP_TARGET yaml-cpp)
else()
  set(YAML_CPP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
  set(YAML_CPP_BUILD_TOOLS OFF CACHE BOOL "" FORCE)
  set(YAML_CPP_BUILD_CONTRIB OFF CACHE BOOL "" FORCE)
  FetchContent_Declare(
    yaml-cpp
    GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
    GIT_TAG yaml-cpp-0.9.0
  )
  FetchContent_MakeAvailable(yaml-cpp)

  if(TARGET yaml-cpp::yaml-cpp)
    set(YAML_CPP_TARGET yaml-cpp::yaml-cpp)
  else()
    set(YAML_CPP_TARGET yaml-cpp)
  endif()
endif()

include_directories(
  ${CURSES_INCLUDE_DIR}
)

#check ncursesw
message(STATUS "CURSES_LIBRARIES: ${CURSES_LIBRARIES}")
message(STATUS "CURSES_INCLUDE: ${CURSES_INCLUDE_DIR}")

#tests
ENABLE_TESTING()
ADD_SUBDIRECTORY( tests )

##############################
# SF
file(GLOB_RECURSE SF_SRC
    "src/sf/*.cpp"
)

add_executable(
    sf
    ${SF_SRC}
)
if(TARGET PDCurses)
  add_dependencies(sf PDCurses)
endif()

target_link_libraries(
    sf
    ${CURSES_LIBRARIES}
    ${YAML_CPP_TARGET}
    Threads::Threads
)
target_compile_options(sf PRIVATE ${CURSES_CFLAGS_OTHER})

set_target_properties( sf PROPERTIES RUNTIME_OUTPUT_DIRECTORY . )
set_target_properties( sf PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG . )
set_target_properties( sf PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE . )


#copy config and language files
#file(COPY lang DESTINATION .)
configure_file(lang/en.yaml lang/en.yaml COPYONLY)
configure_file(lang/de.yaml lang/de.yaml COPYONLY)
configure_file(config.yaml config.yaml COPYONLY)
