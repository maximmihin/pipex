cmake_minimum_required(VERSION 3.21)
project(pipex C)

set(CMAKE_C_STANDARD 11)

include_directories(includes)

add_executable(pipex
        includes/pipex.h
        libft_func/ft_split.c
        libft_func/ft_strlen.c
        libft_func/ft_strncmp.c
        libft_func/ft_substr.c
        src/pipex.c src/childs.c libft_func/ft_strjoin.c src/errors.c)
