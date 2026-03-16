cmake_minimum_required(VERSION 3.15)
project(CppHashTable VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


if(APPLE AND CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++")
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        add_compile_options(-O3)
        # -march=native может не работать на всех macOS, особенно arm64
        if(NOT APPLE)
            add_compile_options(-march=native)
        endif()
    elseif(MSVC)
        add_compile_options(/O2)
    endif()
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
elseif(MSVC)
    add_compile_options(/W4)
endif()

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(hash_table_demo src/main.cpp)

if(APPLE)
    target_link_libraries(hash_table_demo PRIVATE c++)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    target_link_libraries(hash_table_demo PRIVATE stdc++)
endif()

install(TARGETS hash_table_demo DESTINATION bin)