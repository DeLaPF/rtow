if (WIN32)
    include(./.env.cmake OPTIONAL RESULT_VARIABLE LOCAL_ENV)
    message(STATUS "Local .env.cmake: ${LOCAL_ENV}")
endif()

cmake_minimum_required(VERSION 3.11.0)
project(rtow VERSION 0.0.1)
set(CMAKE_CXX_STANDARD 17)

# Mingw
message(STATUS "using ${CMAKE_GENERATOR}")
if (CMAKE_GENERATOR STREQUAL "MinGW Makefiles")
    if (NOT MINGW_PATH) 
      message(FATAL_ERROR "MINGW_PATH not set in .env.cmake")
    endif()
    set(USE_MINGW "True")
    set(CMAKE_C_COMPILER ${MINGW_PATH}/bin/gcc.exe)
    set(CMAKE_CXX_COMPILER ${MINGW_PATH}/bin/g++.exe)
    message(STATUS "using mingw at: ${MINGW_PATH}")
endif()

# Rtve
message(STATUS "ADDING ${PROJECT_NAME}")
file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)
add_executable(${PROJECT_NAME}
    ${SOURCES}
)
target_include_directories(${PROJECT_NAME} PUBLIC
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/external
)
if (WIN32)
    target_link_libraries(${PROJECT_NAME} PUBLIC
        -static
    )
else()
    target_link_libraries(${PROJECT_NAME} PUBLIC
    )
endif()
