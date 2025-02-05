cmake_minimum_required(VERSION 3.15)

project(GraphProject)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add source files
set(SOURCES
    graph.cc
    main.cc
    solution.cc
    window.cc
)

# Set the output executable name
set(EXECUTABLE_NAME graph)

# Find SFML using vcpkg or system package
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Add the executable
add_executable(${EXECUTABLE_NAME} ${SOURCES})

# Link SFML libraries
target_link_libraries(${EXECUTABLE_NAME} PRIVATE sfml-graphics sfml-window sfml-system)

# Ensure vcpkg integration on Windows
if (WIN32)
    if (DEFINED ENV{VCPKG_ROOT})
        set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
    endif()
endif()

# Windows
# mkdir build
# cd build
# cmake .. -DCMAKE_TOOLCHAIN_FILE=C:\vcpkg\scripts\buildsystems\vcpkg.cmake
# cmake --build .
# .\graph.exe

# Linux
# mkdir build
# cd build
# cmake ..
# cmake --build .
# ./graph