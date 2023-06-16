cmake_minimum_required(VERSION 3.10)
project(massagerobot_gazebo_control_plugin)

find_package(gz-sim7 REQUIRED)

# Add includes
include_directories(".")
 
# Add sources
set(cppsrc 
	src/control_main_framework.cpp)

add_library(ControlMainFrameworkSystem SHARED ${cppsrc})

set_property(TARGET ControlMainFrameworkSystem PROPERTY CXX_STANDARD 17)

target_link_libraries(ControlMainFrameworkSystem
  gz-sim7
)