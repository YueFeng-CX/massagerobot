#!/bin/bash
# Gazebo default plugins loaded generally not satisfy specific needs, so load a custom server configuration file to make the simulation world work.

# config this path to the file "gazebo_server.config"
export GZ_SIM_SERVER_CONFIG_PATH=`pwd`/gazebo_server.config
