cmake_minimum_required(VERSION 3.13)
project(bq-r)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 2.5 REQUIRED COMPONENTS graphics window audio network system)

file(GLOB_RECURSE sources "src/*.cpp")

add_executable(bq-r ${sources})

target_compile_options(bq-r PUBLIC -Wall)
target_include_directories(bq-r PUBLIC
	"src/"
)
target_link_libraries(bq-r
	sfml-graphics
	sfml-window
	sfml-audio
	sfml-network
	sfml-system
)
