cmake_minimum_required(VERSION 3.13)
project(bq-r)

set(CMAKE_CXX_STANDARD 20)

# external deps
find_package(SFML 2.5 REQUIRED COMPONENTS graphics window audio network system)
include(FindOpenGL)
add_subdirectory(lib/Box2D)
add_subdirectory(lib/imgui)

file(GLOB_RECURSE sources "src/*.cpp")

add_executable(bq-r ${sources})

target_compile_options(bq-r PUBLIC -Wall)
target_include_directories(bq-r PUBLIC
	"src/"
	"lib/Box2D/Box2D"
	"lib/imgui"
)
target_link_libraries(bq-r
	sfml-graphics
	sfml-window
	sfml-audio
	sfml-network
	sfml-system
	tobanteGaming::Box2D
	imgui
	OpenGL::GL
)
