cmake_minimum_required(VERSION 3.8.0)

# Enable languages
enable_language(CXX)
enable_language(ASM_MASM)

# Project name
project("Shitman3")
set(TARGET "Shitman3")

# Set language standards
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD   99)

# Output path
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/Bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/Bin")

# Setup Directx
include_directories(${TARGET} "C:\\Program Files (x86)\\Microsoft DirectX SDK (June 2010)\\Include")

# Include directories
include_directories(${TARGET} Include)
set(INCLUDE_DIR Include)

# Source directories
set(SOURCE_DIR Source)
set(ASM_DIR ${SOURCE_DIR}/Assembly)

# Add sources
set(SOURCES 
    # CXX Sources
    ${SOURCE_DIR}/D3d9Hook.cpp
    ${SOURCE_DIR}/Drawing.cpp
    ${SOURCE_DIR}/Events.cpp
    ${SOURCE_DIR}/Hacks.cpp
    ${SOURCE_DIR}/Main.cpp
    ${SOURCE_DIR}/Memory.cpp
    ${SOURCE_DIR}/Render.cpp
    # Includes
    ${INCLUDE_DIR}/D3d9Hook.hpp
    ${INCLUDE_DIR}/Drawing.hpp
    ${INCLUDE_DIR}/Entity.hpp
    ${INCLUDE_DIR}/Events.hpp
    ${INCLUDE_DIR}/Hacks.hpp
    ${INCLUDE_DIR}/Memory.hpp
    ${INCLUDE_DIR}/Offsets.hpp
    ${INCLUDE_DIR}/Render.hpp
    # Assembly Sources
    #${INCLUDE_DIR}/Assembly.hpp
    #${ASM_DIR}/foo.asm
)

# Build dynamic load library
add_library(${TARGET} SHARED ${SOURCES})
set_target_properties(
    ${TARGET}
    PROPERTIES
    OUTPUT_NAME ${TARGET}
    PREFIX ""
    SUFFIX ".dll"
)

# Setup Directx Libs
target_link_directories(${TARGET} PUBLIC "C:\\Program Files (x86)\\Microsoft DirectX SDK (June 2010)\\Lib\\x86")
target_link_libraries(${TARGET} d3d9 d3dx9)
