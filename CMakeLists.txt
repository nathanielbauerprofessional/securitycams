cmake_minimum_required(VERSION 4.3) #specifies the minimum cmake version required
set_property(GLOBAL PROPERTY USE_FOLDERS ON) #says to separate the header and source files based on their extensions for organization
project(securitycams) #sets the project name
add_executable(${CMAKE_PROJECT_NAME} ServerThread.cpp ServerThread.h main.cpp) #defines the target executable to be built from the source file ServerThread.cpp and .h
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}) #tells the compiler to look for header files in the current source directory
