cmake_minimum_required(VERSION 3.20)
project(MainApp LANGUAGES CXX)

# --- Configuration ---
# FlyFish v2 requires C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- FlyFish (single header, downloaded at configure time) ---
set(FLYFISH_VERSION "v2.0.0")
set(FLYFISH_SHA256 "ee9fa70300ba20f9bfe830fd744726ace1d1d6ee679bf427283085392a9da645")
set(FLYFISH_INCLUDE_DIR "${CMAKE_BINARY_DIR}/_deps/flyfish-${FLYFISH_VERSION}/include")
set(FLYFISH_HEADER "${FLYFISH_INCLUDE_DIR}/flyfish/FlyFish.h")

if(NOT EXISTS "${FLYFISH_HEADER}")
    message(STATUS "Downloading FlyFish ${FLYFISH_VERSION} header...")
    file(DOWNLOAD
            "https://raw.githubusercontent.com/fdlombae/FlyFish/${FLYFISH_VERSION}/include/flyfish/FlyFish.h"
            "${FLYFISH_HEADER}"
            EXPECTED_HASH SHA256=${FLYFISH_SHA256}
            TLS_VERIFY ON
            STATUS FLYFISH_DOWNLOAD_STATUS
    )
    list(GET FLYFISH_DOWNLOAD_STATUS 0 FLYFISH_DOWNLOAD_CODE)
    if(NOT FLYFISH_DOWNLOAD_CODE EQUAL 0)
        file(REMOVE "${FLYFISH_HEADER}")
        message(FATAL_ERROR "Failed to download FlyFish header: ${FLYFISH_DOWNLOAD_STATUS}")
    endif()
endif()

add_library(FlyFish INTERFACE)
target_include_directories(FlyFish INTERFACE "${FLYFISH_INCLUDE_DIR}")
target_compile_features(FlyFish INTERFACE cxx_std_23)

# --- Main app ---
add_executable(${PROJECT_NAME} main.cpp
        Dataset.cpp
        Dataset.h)

target_link_libraries(${PROJECT_NAME} PRIVATE FlyFish)
