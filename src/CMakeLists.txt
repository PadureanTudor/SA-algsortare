cmake_minimum_required(VERSION 3.16)

# Project name and language
project(AlgoritmiSortare LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# =========================
# Main application
# =========================
add_executable(main_app
    main.cpp

)

if (MSVC)
    target_compile_options(main_app PRIVATE /W4 /Ot)
else()
    target_compile_options(main_app PRIVATE -Wall -Wextra -Wpedantic -O3)
endif()

