function(set_target_info)
    if(WIN32)
        set(TARGET_OS "windows" PARENT_SCOPE)
        set(TARGET_ARCH "x64" PARENT_SCOPE)
        set(VCPKG_TARGET_TRIPLET "x64-windows" PARENT_SCOPE)
    elseif(APPLE)
        set(TARGET_OS "osx" PARENT_SCOPE)
        set(TARGET_ARCH "arm64" PARENT_SCOPE)
        set(VCPKG_TARGET_TRIPLET "arm64-osx" PARENT_SCOPE)
    elseif(UNIX AND NOT APPLE)
        set(TARGET_OS "linux" PARENT_SCOPE)
        set(TARGET_ARCH "x86" PARENT_SCOPE)
        set(VCPKG_TARGET_TRIPLET "x86-linux" PARENT_SCOPE)
    endif()
endfunction()

cmake_minimum_required(VERSION 3.15)
project(plant)


if(DEFINED ENV{VCPKG_ROOT})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
    
    # Explicitly set SFML_DIR based on your platform
    if(WIN32)
        set(SFML_DIR "$ENV{VCPKG_ROOT}/installed/x64-windows/share/sfml" CACHE PATH "")
    elseif(APPLE)
        set(SFML_DIR "$ENV{VCPKG_ROOT}/installed/arm64-osx/share/sfml" CACHE PATH "")
    else() # Linux
        set(SFML_DIR "$ENV{VCPKG_ROOT}/installed/x64-linux/share/sfml" CACHE PATH "")
    endif()
    
    # Make sure this gets passed to any subdirectories
    set(SFML_DIR "${SFML_DIR}" CACHE PATH "" FORCE)
    message(STATUS "Set SFML_DIR to: ${SFML_DIR}")
else()
    message(FATAL_ERROR "VCPKG_ROOT environment variable is not set")
endif()

set_target_info()
set(VCPKG_TARGET_TRIPLET "${TARGET_ARCH}-${TARGET_OS}" CACHE STRING "")
set(VCPKG_MANIFEST_DIR ${CMAKE_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

find_package(SFML COMPONENTS Network Graphics Window Audio System CONFIG REQUIRED)

include(FetchContent)
# First declare and make available the sfsim content
FetchContent_Declare(
    sfsim
    GIT_REPOSITORY https://github.com/samif0/sfsim.git
    GIT_TAG main
)
FetchContent_MakeAvailable(sfsim)
FetchContent_GetProperties(sfsim)

file(GLOB SFSIM_LIB_SOURCES "${sfsim_SOURCE_DIR}/src/*.cpp")
# Remove main.cpp from the sources since that contains the main() function
list(FILTER SFSIM_LIB_SOURCES EXCLUDE REGEX ".*main.cpp$")

# Create a static library target
add_library(sfsim_lib STATIC ${SFSIM_LIB_SOURCES})
target_include_directories(sfsim_lib PUBLIC "${sfsim_SOURCE_DIR}/include")

# Link SFML to the library
target_link_libraries(sfsim_lib PUBLIC 
    SFML::Graphics 
    SFML::Window 
    SFML::System
)

# Build your executable
add_executable(plant ${SOURCES})
target_link_libraries(plant PRIVATE 
    SFML::Network 
    SFML::Graphics 
    SFML::Window 
    SFML::Audio 
    SFML::System
    sfsim_lib  # Link to our library, not sfsim
)
