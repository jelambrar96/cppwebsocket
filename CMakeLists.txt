cmake_minimum_required(VERSION 3.0.0)


# we set a name for this project
project(cppwebsocket)


# -------------------------------------------------------------------------
# This lines include opmtimization flags
# -------------------------------------------------------------------------
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()
# -------------------------------------------------------------------------


# -------------------------------------------------------------------------
# Wextra flag only if gcc compule is used
# -------------------------------------------------------------------------
IF(CMAKE_COMPILER_IS_GNUCXX)
    message(STATUS "GCC detected, adding compile flags")
    set(CMAKE_CXX_FLAGS "-pthread")
ELSE ()
    set(CMAKE_CXX_FLAGS "-pthread")
ENDIF ()
# -------------------------------------------------------------------------


# -------------------------------------------------------------------------
# optimization
# -------------------------------------------------------------------------
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
# -------------------------------------------------------------------------


# ---------------------------------------------------------------------
# debugger
# ---------------------------------------------------------------------
include(CTest)
enable_testing()
# ---------------------------------------------------------------------


# ---------------------------------------------------------------------
# ADD CPP files
# ---------------------------------------------------------------------
include_directories("include/")
file(GLOB SOURCES src/*.c*)
# ---------------------------------------------------------------------


add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${PROJECT_SOURCE_DIR}/src
)

find_package(OpenSSL REQUIRED)
target_link_libraries(${PROJECT_NAME} OpenSSL::SSL)
