cmake_minimum_required(VERSION 3.12)

project(OldSchoolGame VERSION 1.0 LANGUAGES CXX)

#Automatically collect all .cpp files in the project directory
file(GLOB SRC_FILES CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/*.cpp")

add_executable(${PROJECT_NAME} ${SRC_FILES})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic -O3)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR})
