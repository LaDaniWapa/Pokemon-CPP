cmake_minimum_required(VERSION 4.1)
project(pokemon-cpp)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# --- Download and compile raylib ---
include(FetchContent)
FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG        5.5
)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(raylib)

# Include headers
include_directories(include)

# Collect all sources
file(GLOB_RECURSE SOURCES
        src/*.cpp
)

# Executable
add_executable(pokemon-cpp ${SOURCES})

# Debug flags
target_compile_options(pokemon-cpp PRIVATE -g -fdiagnostics-color)

# Linkear raylib (funciona igual en Linux y Windows)
target_link_libraries(pokemon-cpp raylib)