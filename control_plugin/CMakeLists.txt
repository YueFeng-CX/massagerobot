cmake_minimum_required(VERSION 3.10)
project(massagerobot_gazebo_control_plugin)

find_package(gz-sim7 REQUIRED)
find_package(Protobuf REQUIRED)
add_subdirectory(msgs)
set_source_files_properties(${PROTO_SRC} ${PROTO_HEADER}
                           PROPERTIES GENERATED TRUE)
                           
# Add includes
include_directories(${CMAKE_BINARY_DIR})
include_directories(".")
 
# Add sources
set(controlsrc 
	src/control_main_framework.cpp
	src/base_controller.cpp
	src/joint_controller.cpp
	src/pid_controller.cpp
	${PROTO_SRC}
	)
set(userinterfacesrc
    src/pid_userinterface.cpp
    ${PROTO_SRC}
    )
    
add_executable(PidUserInterface ${userinterfacesrc})
target_link_libraries(PidUserInterface
  gz-sim7
)
add_dependencies(PidUserInterface protobuf_interface)

add_library(ControlMainFrameworkSystem SHARED ${controlsrc})
set_property(TARGET ControlMainFrameworkSystem PROPERTY CXX_STANDARD 17)
target_link_libraries(ControlMainFrameworkSystem
  gz-sim7
)
add_dependencies(ControlMainFrameworkSystem protobuf_interface)





