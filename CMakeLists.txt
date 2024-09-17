cmake_minimum_required(VERSION 3.11)
project(ExpressionParser)

add_executable(ExpressionParser)
target_sources(ExpressionParser PRIVATE
    src/main.c
    src/ExpressionParser/Token.c
    src/ExpressionParser/ExpressionParser.c
    src/ExpressionParser/DataStructures.c
)
#target_compile_options(expression_parser PRIVATE -Wall -Werror -fsanitize=address -fno-omit-frame-pointer)
#target_link_options(expression_parser PRIVATE -lm -fsanitize=address)
target_compile_options(ExpressionParser PRIVATE -Wall -Werror)