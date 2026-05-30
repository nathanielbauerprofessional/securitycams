cmake_minimum_required(VERSION 4.3) #specifies the minimum cmake version required
project(securitycams) #sets the project name

find_package(OpenCV REQUIRED) #finds the OpenCV package and makes it available for use in the project
set_property(GLOBAL PROPERTY USE_FOLDERS ON) #says to separate the header and source files based on their extensions for organization

add_executable(${CMAKE_PROJECT_NAME} ServerThread.cpp ServerThread.h main.cpp) #defines the target executable to be built from the source file ServerThread.cpp and .h
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}) #tells the compiler to look for header files in the current source directory
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ${OpenCV_LIBS}) #links the OpenCV libraries to the target executable