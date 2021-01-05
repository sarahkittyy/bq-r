# this specific cmakelists file made by sarahkittyy
file(GLOB sources "*.cpp")

add_library(imgui ${sources})
target_include_directories(imgui PUBLIC .)
