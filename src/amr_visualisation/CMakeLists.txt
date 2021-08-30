cmake_minimum_required(VERSION 3.5)
project(amr_visualisation)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_definitions(-DROS2_BUILD)

# find dependencies
find_package(ament_cmake REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(control_msgs REQUIRED)
find_package(visualization_msgs REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(om_aiv_msg REQUIRED)
find_package(nav_msgs REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(
  include
  ${rclcpp_INCLUDE_DIRS}
  ${rclcpp_action_INCLUDE_DIRS}
  ${catkin_INCLUDE_DIRS}
)

link_directories(${catkin_LIBRARY_DIRS})
set(HEADERS
  include/amr_visualisation/laser_scans.hpp
)


if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

include_directories(include
  ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(joints_publisher 
  src/joints_publisher.cpp
)

ament_target_dependencies(joints_publisher
  rclcpp
  std_msgs
  sensor_msgs
  geometry_msgs
  control_msgs
  tf2_ros
  om_aiv_msg
)

add_executable(goals_marker
 src/goals_marker.cpp
)

ament_target_dependencies(goals_marker
 rclcpp
 std_msgs
 visualization_msgs
 geometry_msgs
 tf2_ros
 om_aiv_msg
)

add_executable(data_points_marker
  src/data_points_marker.cpp
)

ament_target_dependencies(data_points_marker
  rclcpp
  std_msgs
  sensor_msgs
  geometry_msgs
  control_msgs
  tf2_ros
  om_aiv_msg
  visualization_msgs
  nav_msgs
)

add_executable(laser_scans
  src/laser_scans.cpp
)

ament_target_dependencies(laser_scans
  rclcpp
  std_msgs
  sensor_msgs
  geometry_msgs
  control_msgs
  tf2_ros
  om_aiv_msg
  visualization_msgs
  nav_msgs
)

install(TARGETS
  joints_publisher data_points_marker goals_marker laser_scans
  DESTINATION lib/${PROJECT_NAME}
)

install(
  DIRECTORY launch config map meshes param urdf
  DESTINATION share/${PROJECT_NAME}
)

ament_package()
