cmake_minimum_required(VERSION 3.16)
project(miniRT C)

set(CMAKE_C_STANDARD 11)

# Source files
set(SRC_DIR ./src)
file(GLOB SRC_FILES ${SRC_DIR}/*.c)

# Include directories
set(INC_DIR ./include)
set(LIBFT_DIR ./libft)
set(MLX_DIR ./minilibx-linux)

include_directories(${INC_DIR} ${LIBFT_DIR}/include ${MLX_DIR})

# Library directories
link_directories(${LIBFT_DIR} ${MLX_DIR})

# Compiler flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror")

# Add the executable
add_executable(miniRT ${SRC_FILES})

# Link libraries
target_link_libraries(miniRT ft mlx m)

# Set working directory for CLion run configurations
set_target_properties(miniRT PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})