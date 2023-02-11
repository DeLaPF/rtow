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

# oneTBB
if (WIN32)
    if (NOT TBB_PATH)
        message(FATAL_ERROR "TBB_PATH not set in .env.cmake")
    endif()
    set(TBB_LIB "${TBB_PATH}/lib/intel64/vc14")
    #set(TBB_LIB "${TBB_PATH}/redist/intel64/vc14")
    message(STATUS "Using oneTBB path specified in .env")
else()
    add_subdirectory(${PROJECT_SOURCE_DIR}/libs/oneTBB EXCLUDE_FROM_ALL)
endif()

# Rtve
message(STATUS "ADDING ${PROJECT_NAME}")
file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)
add_executable(${PROJECT_NAME}
    ${SOURCES}
)
target_include_directories(${PROJECT_NAME} PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)
#target_link_directories(${PROJECT_NAME} PUBLIC
#    ${TBB_LIB}
#)
if (WIN32)
    target_link_libraries(${PROJECT_NAME} PUBLIC
        #${TBB_LIB}
        #tbb
        -static
    )
else()
    target_link_libraries(${PROJECT_NAME} PUBLIC
        tbb
    )
endif()
