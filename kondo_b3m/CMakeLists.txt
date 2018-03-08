cmake_minimum_required(VERSION 2.8)

add_definitions("-std=c++11")

project(kondo)
set(Boost_USE_MULTITHREADED ON)
find_package(Boost REQUIRED COMPONENTS system thread)

link_directories(
	${Boost_LIBRARY_DIR}
	${Boost_LIBRARY_DIRS}
)

include_directories(${Boost_INCLUDE_DIRS})

add_executable(kondo main.cpp B3M.h Servo.cpp Servo.h)
target_link_libraries(kondo ${Boost_SYSTEM_LIBRARY} pthread)

