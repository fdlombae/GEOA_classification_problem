cmake_minimum_required(VERSION 3.14)
project(MainApp LANGUAGES CXX)

# --- Configuration ---
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Submodule check ---
if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/FlyFish/CMakeLists.txt")
    message(STATUS "FlyFish submodule not found. Initializing...")
    execute_process(
            COMMAND git submodule update --init --recursive
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )
endif()

# --- Add the FlyFish submodule ---
add_subdirectory(FlyFish)

# --- Main app ---
add_executable(${PROJECT_NAME} main.cpp
        Dataset.cpp
        Dataset.h)

# --- Include and link FlyFish ---
target_link_libraries(${PROJECT_NAME} PRIVATE FlyFish)
target_include_directories(${PROJECT_NAME} PRIVATE FlyFish/include)