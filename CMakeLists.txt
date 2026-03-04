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

# Definicja ścieżki (musi być przed GLOB)
set(root_tgfx_dir ${CMAKE_SOURCE_DIR}/TouchGFX)

# Add STM32CubeMX generated sources
add_subdirectory(cmake/stm32cubemx)

# --- UWAGA: Zakomentowane, aby uniknąć podwójnej kompilacji z GLOB ---
# add_subdirectory(cmake/touchgfx) 

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # 1. Główna biblioteka TouchGFX
    ${CMAKE_SOURCE_DIR}/Middlewares/ST/touchgfx/lib/core/cortex_m33/gcc
    
    # 2. Biblioteka TouchGFX Nema (specyficzna dla U5)
    ${CMAKE_SOURCE_DIR}/Middlewares/ST/touchgfx_components/gpu2d/TouchGFXNema/lib/cortex_m33/gcc
    
    # 3. Biblioteka NemaGFX (silnik akceleracji)
    ${CMAKE_SOURCE_DIR}/Middlewares/ST/touchgfx_components/gpu2d/NemaGFX/lib/core/cortex_m33/gcc
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
    ${CMAKE_SOURCE_DIR}/Drivers/BSP/Components/mx25lm51245g/mx25lm51245g.c
)

# FILTR: Usuwamy pliki symulatora, których nie da się skompilować na ARM
list(FILTER graphics_core_generated_SRCS EXCLUDE REGEX "TouchGFX/generated/simulator")

# Add sources to executable
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    ${graphics_core_generated_SRCS}
    
    # Pliki systemowe nowego projektu
    Core/Src/main.cpp
    Core/Src/app_freertos.c
    Core/Src/stm32u5xx_it.c
    # Add user sources here
)

# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Application includes
    Core/Inc
    Drivers/BSP/Components/mx25lm51245g
    Core/Inc/PUTM_EV_CAN_LIBRARY/lib
    Core/Inc/PUTM_EV_CAN_LIBRARY/lib/CanHeaders
    
    ${root_tgfx_dir}/gui/include
    ${root_tgfx_dir}/generated/gui_generated/include
    ${root_tgfx_dir}/generated/images/include
    ${root_tgfx_dir}/generated/bitmaps/include
    ${root_tgfx_dir}/generated/fonts/include
    ${root_tgfx_dir}/generated/texts/include
    ${root_tgfx_dir}/generated/videos/include
    
    # TouchGFX framework includes
    ${root_tgfx_dir}/../Middlewares/ST/touchgfx/framework/include
    ${root_tgfx_dir}/../Middlewares/ST/touchgfx/framework/include/common
    ${root_tgfx_dir}/../Middlewares/ST/touchgfx/framework/common/include

    # Path to the TouchGFX framework itself
    ${root_tgfx_dir}/../Middlewares/ST/touchgfx/
    
    # Niezbędne dla akceleracji NemaGFX (STM32U5)
    ${CMAKE_SOURCE_DIR}/Middlewares/ST/touchgfx_components/gpu2d/NemaGFX/include
    ${CMAKE_SOURCE_DIR}/Middlewares/ST/touchgfx_components/gpu2d/TouchGFXNema/include
)

# Add project symbols (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    USE_HAL_DRIVER
    STM32U5A9xx
    USE_BPP=24
    # Add user defined symbols
)

# Remove wrong libob.a library dependency
list(REMOVE_ITEM CMAKE_C_IMPLICIT_LINK_LIBRARIES ob)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    stm32cubemx
    # Ręczne linkowanie biblioteki TouchGFX i akceleracji U5
    touchgfx-float-abi-hard
    touchgfxnema-float-abi-hard
    nemagfx-float-abi-hard
)