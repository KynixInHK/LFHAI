cmake_minimum_required(VERSION 3.25)
project(agent C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(agent
        test.agent.main.c board.c user.agent.c KynixAI.h)
