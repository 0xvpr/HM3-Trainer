cmake_minimum_required(VERSION 3.6)

project("Splinter Cell 3 Hacks")

set(EXEC "sp3")
set(CMAKE_CXX_STANDARD C++17)

## Sources
file(GLOB SOURCES src/*.cpp)

## Includes
include_directories(src)
include_directories(include)
include_directories("/C/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Include")

## Output DLL
add_library(${EXEC} SHARED ${SOURCES})

# Output DIR
set_target_properties(${EXEC}
					  PROPERTIES
					  CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out
					  CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out
					  CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out
)

## Library Files
target_link_libraries(${EXEC} d3d9, d3dx9)