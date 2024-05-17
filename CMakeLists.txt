cmake_minimum_required(VERSION 3.16)
project(miniRT C)


set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wextra -g")

# libft
file(GLOB_RECURSE LIBFT_SOURCES "libft/*/*.c")
add_library(libft STATIC ${LIBFT_SOURCES}
		src/args/single_mode.c)
target_include_directories(libft PUBLIC libft/include)

# mlx lib
file(GLOB_RECURSE MLX_SOURCES "minilibx-linux/*.c")
add_library(mlx STATIC ${MLX_SOURCES})
target_include_directories(mlx PUBLIC ./minilibx-linux)

# ignore mlx -w
target_compile_options(mlx PRIVATE -w)

# Include directories
include_directories(include)
include_directories(libft/include)
include_directories(minilibx-linux)

link_directories(/usr/lib)

# Compile miniRT
file(GLOB_RECURSE MINIRT_SOURCES
		"src/*.c"
		"src/*/*.c"
		"include/*.h"
		)

# Add the executable
add_executable(miniRT ${MINIRT_SOURCES})

# Link libraries
target_link_libraries(miniRT libft mlx X11 Xext m)
