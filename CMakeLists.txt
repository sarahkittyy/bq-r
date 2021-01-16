cmake_minimum_required(VERSION 3.13)
project(bq-r)

set(CMAKE_CXX_STANDARD 20)

# external deps
find_package(SFML 2.5 REQUIRED COMPONENTS graphics window audio network system)
include(FindOpenGL)
add_subdirectory(lib/Box2D)
add_subdirectory(lib/imgui)

file(GLOB_RECURSE sources "src/*.cpp")

set(project_includes "src/;lib/Box2D/Box2D;lib/imgui;lib/nlohmann")
set(project_links
	"sfml-graphics;sfml-window;sfml-audio;sfml-network;sfml-system;tobanteGaming::Box2D;imgui;OpenGL::GL"
)
set(project_flags "-Wall")

option(BUILD_TESTS "Build the unit tests")
if (BUILD_TESTS)
	set(sources-lib ${sources})
	list(REMOVE_ITEM ${sources-lib} "src/main.cpp")
	add_library(bq-r-test-lib ${sources-lib})
	target_compile_options(bq-r-test-lib PUBLIC ${project_flags})
	target_include_directories(bq-r-test-lib PUBLIC ${project_includes})
	target_link_libraries(bq-r-test-lib ${project_links})
	enable_testing()
	add_subdirectory("test")
endif()

add_executable(bq-r ${sources})

target_compile_options(bq-r PUBLIC ${project_flags})
target_include_directories(bq-r PUBLIC ${project_includes})
target_link_libraries(bq-r ${project_links})
