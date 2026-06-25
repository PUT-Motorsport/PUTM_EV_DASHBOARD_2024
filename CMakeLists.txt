cmake_minimum_required(VERSION 3.22)

#
# This file is generated only once,
# and is not re-generated if converter is called multiple times.
#
# User is free to modify the file as much as necessary
#

# Setup compiler settings
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Set the project name
set(CMAKE_PROJECT_NAME Riverdi_50STM32U5A9)

###################################
#Relase build setup




###################################
# include("cmake/gcc-arm-none-eabi.cmake")

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Core project settings
project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})

# Enable CMake support for ASM, C and C++ languages
enable_language(C CXX ASM)

# Create an executable object type
add_executable(${CMAKE_PROJECT_NAME})

# Add STM32CubeMX generated sources
add_subdirectory(cmake/stm32cubemx)

# Add touchgfx generated sources and libraries
add_subdirectory(cmake/touchgfx)

add_subdirectory(Components/PUTM_EV_CAN_LIBRARY)

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined library search paths
)

# Add sources to executable
file(GLOB_RECURSE graphics_core_generated_SRCS
    ${root_tgfx_dir}/generated/*.cpp
    ${root_tgfx_dir}/gui/*.cpp
    ${root_tgfx_dir}/gui/*.c
    ${CMAKE_SOURCE_DIR}/Core/Src/data.c
    ${CMAKE_SOURCE_DIR}/Core/Src/communication_task.cpp
    ${CMAKE_SOURCE_DIR}/Core/Src/timer_task.cpp
    ${CMAKE_SOURCE_DIR}/Core/Src/led_test_task.cpp
    ${CMAKE_SOURCE_DIR}/Core/Src/interface_task.cpp
    ${CMAKE_SOURCE_DIR}/Drivers/BSP/Components/mx25lm51245g.c
)

# Add sources to executable
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    ${graphics_core_generated_SRCS}
    
    # Add user sources here
)

set(root_tgfx_dir ${CMAKE_SOURCE_DIR}/TouchGFX)

# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Application includes
    ${root_tgfx_dir}/gui/include
    ${root_tgfx_dir}/generated/gui_generated/include
    ${root_tgfx_dir}/generated/images/include
    ${root_tgfx_dir}/generated/bitmaps/include
    ${root_tgfx_dir}/generated/fonts/include
    ${root_tgfx_dir}/generated/texts/include
    ${root_tgfx_dir}/generated/videos/include
    
    # TouchGFX framework includes (assuming it's in a specific location relative to this file)
    ${root_tgfx_dir}/../Middlewares/ST/touchgfx/framework/include
    ${root_tgfx_dir}/../Middlewares/ST/touchgfx/framework/include/common
    ${root_tgfx_dir}/../Middlewares/ST/touchgfx/framework/common/include

    # Adding the path to the TouchGFX framework itself to resolve the "No such file or directory" errors.
    ${root_tgfx_dir}/../Middlewares/ST/touchgfx/
    
    # Add user defined include paths
    Components/
)

# Add project symbols (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined symbols
)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    stm32cubemx
    putm_ev_can
    # Add user defined libraries

    # The TouchGFX library file for ARM (not the simulator version)
    #  ${CMAKE_SOURCE_DIR}/Middlewares/ST/touchgfx/lib/core/cortex_m33/gcc/libtouchgfx-float-abi-hard.a
)
