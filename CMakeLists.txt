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
    "include/lexer.hpp" "src/lexer.cpp" "include/ast.hpp" "src/ast.cpp" "include/typing.hpp" "src/typing.cpp" "include/ast_nodes/node.hpp" "include/ast_nodes/statements_node.hpp" "include/ast_nodes/expression_node.hpp" "include/ast_nodes/operator_node.hpp" "src/ast_nodes/operator_node.cpp" "include/ast_nodes/literal_node.hpp" "include/ast_nodes/assign_node.hpp" "src/ast_nodes/assign_node.cpp" "include/ast_nodes/vardecl_node.hpp" "src/ast_nodes/vardecl_node.cpp")
target_include_directories(${PROJECT_NAME} PUBLIC ${INC_DIR})

# Make it output to a standard location
set_target_properties(${PROJECT_NAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${OBJ_DIR}"
    LIBRARY_OUTPUT_DIRECTORY "${BIN_DIR}"
    RUNTIME_OUTPUT_DIRECTORY "${BIN_DIR}"
)