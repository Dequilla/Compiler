cmake_minimum_required(VERSION 3.1)

set(PROJECT_NAME DeqCompiler)

set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(INC_DIR ${ROOT_DIR}/include)
set(SRC_DIR ${ROOT_DIR}/src)
set(OBJ_DIR ${ROOT_DIR}/obj)
set(BIN_DIR ${ROOT_DIR}/bin)

# Source files
file(GLOB_RECURSE SOURCE_FILES
    "${SRC_DIR}/*.c"
)

project(${PROJECT_NAME} C)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC ${INC_DIR})

# Make it output to a standard location
set_target_properties(${PROJECT_NAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${OBJ_DIR}"
    LIBRARY_OUTPUT_DIRECTORY "${BIN_DIR}"
    RUNTIME_OUTPUT_DIRECTORY "${BIN_DIR}"
)