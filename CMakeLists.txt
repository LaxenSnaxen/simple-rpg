cmake_minimum_required(VERSION 3.5)
project(rpg)

# ------------------------------
# User config
set(GAME "rpg")
set(DEBUG ON)

# Set FreeType paths manually (if needed)
set(FREETYPE_INCLUDE_DIRS "/usr/include/freetype2")
set(FREETYPE_LIBRARIES "/usr/lib/x86_64-linux-gnu/libfreetype.so")

# ------------------------------
# Debug/Release flags
option(DEBUG "" ${DEBUG})
if(DEBUG)
    message("--- Debug ---")
    set(CMAKE_BUILD_TYPE "Debug")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Og -Wall -Wextra -g -pg")
else()
    message("--- Release ---")
    set(CMAKE_BUILD_TYPE "Release")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
endif()

# ------------------------------
# Include directories
include_directories(
    "src"
    "deps/rapidjson/include"
    "deps/SFML/include"
    ${FREETYPE_INCLUDE_DIRS}   # FreeType include
)

# ------------------------------
# Find and link FreeType
find_package(Freetype REQUIRED)
# Add FreeType to your executable later

# ------------------------------
# SFML options
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_DOC OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(SFML_USE_SYSTEM_DEPS OFF CACHE BOOL "" FORCE)
set(SFML_USE_SYSTEM_FREETYPE ON CACHE BOOL "Use system FreeType" FORCE)

add_subdirectory(deps/SFML)

# ------------------------------
# Game sources
file(GLOB_RECURSE GAME_SOURCES "src/*.cpp")

add_executable(${GAME} ${GAME_SOURCES})

# Link libraries
target_link_libraries(${GAME}
    sfml-system
    sfml-window
    sfml-network
    sfml-graphics
    sfml-audio
    ${FREETYPE_LIBRARIES}      # Link FreeType
)

# ------------------------------
# Optional: add 'make run'
add_custom_target(run
    COMMAND ${GAME}
    DEPENDS ${GAME}
)

