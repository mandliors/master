cmake_minimum_required(VERSION 3.11)
project(expression_parser)

add_executable(expression_parser)
target_sources(expression_parser PRIVATE
    src/main.c
    src/expression_parser/expression_parser.c
)
target_compile_options(expression_parser PRIVATE -Wall -Werror)
target_link_libraries(expression_parser PRIVATE m)