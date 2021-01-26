cmake_minimum_required(VERSION 3.1)

set(PROJECT_NAME DeqCompiler)

set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(INC_DIR ${ROOT_DIR}/include)
set(OBJ_DIR ${ROOT_DIR}/obj)
set(BIN_DIR ${ROOT_DIR}/bin)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(${PROJECT_NAME} VERSION 1.0)
add_executable(${PROJECT_NAME} 
    "src/main.cpp"
     
     "include/lexer.hpp" "src/lexer.cpp")
target_include_directories(${PROJECT_NAME} PUBLIC ${INC_DIR})

# Make it output to a standard location
set_target_properties(${PROJECT_NAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${OBJ_DIR}"
    LIBRARY_OUTPUT_DIRECTORY "${BIN_DIR}"
    RUNTIME_OUTPUT_DIRECTORY "${BIN_DIR}"
)