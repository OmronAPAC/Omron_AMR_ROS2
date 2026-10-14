# Omron AMR package

To view the original Readme.md [click here](./docs/old_docs/original_readme.md)

This package is a restructuring of [OmronAPAC/Omron_AMR_ROS2](https://github.com/OmronAPAC/Omron_AMR_ROS2) along with integration of [libaria](https://github.com/CollaborativeRoboticsLab/libaria) following [KalanaRatnayake/ros_omron_agv](https://github.com/KalanaRatnayake/ros_omron_agv)

| Branch | ROS2 Version | Compile |
|--------|--------------|---------|
| main | Jazzy | [![main](https://github.com/CollaborativeRoboticsLab/omron_amr/actions/workflows/compile.yml/badge.svg?branch=main)](https://github.com/CollaborativeRoboticsLab/omron_amr/actions/workflows/compile.yml?query=branch%3Amain) |
| develop | Jazzy | [![develop](https://github.com/CollaborativeRoboticsLab/omron_amr/actions/workflows/compile.yml/badge.svg?branch=develop)](https://github.com/CollaborativeRoboticsLab/omron_amr/actions/workflows/compile.yml?query=branch%3Adevelop) |
| humble | Humble | [![humble](https://github.com/CollaborativeRoboticsLab/omron_amr/actions/workflows/compile.yml/badge.svg?branch=humble)](https://github.com/CollaborativeRoboticsLab/omron_amr/actions/workflows/compile.yml?query=branch%3Ahumble) |

## Documentation

- [Core startup](./docs/core_startup.md)
- [Core parameters](./docs/core_parameters.md)
- [Digital twin overrides](./docs/digital_twin.md)
- [Laser interface](./docs/laser_interface.md)
- [Nav2 usage](./docs/nav2_usage.md)

## Setup

Create a workspace

```sh
mkdir -p omron_ws/src
cd omron_ws/src
```

Install dependencies
```sh
sudo apt install ros-humble-navigation2 ros-humble-nav2-bringup ros-humble-slam-toolbox ros-humble-teleop-twist-joy ros-humble-joy
```

Clone the repositories into the `src` folder by

```sh
git clone --recurse-submodules https://github.com/CollaborativeRoboticsLab/omron_amr.git
```

Build by

```sh
cd ..
colcon build
```

## Start only the hardware interface

```sh
source install/setup.bash
ros2 launch amr_ros amr_core.launch.py
```

## LD250

### Start LD250 base only (Hardware interface + robot description)

```sh
source install/setup.bash
ros2 launch amr_ros ld250.launch.py
```

### Start Nav2 SLAM and open the Nav2 RViz view for mapping

```sh
source install/setup.bash
ros2 launch amr_ros ld250.launch.py use_nav2:=true use_slam:=true
```

```sh
source install/setup.bash
ros2 launch amr_nav2 nav2_rviz.launch.py
```

### Start Nav2 localization with a map from amr_nav2/maps and open the Nav2 RViz view

```sh
source install/setup.bash
ros2 launch amr_ros ld250.launch.py use_nav2:=true use_localization:=true map:=my_map.yaml
```

```sh
source install/setup.bash
ros2 launch amr_nav2 nav2_rviz.launch.py
```


## LD90

### Start LD90 base only (Hardware interface + robot description)

```sh
source install/setup.bash
ros2 launch amr_ros ld90.launch.py
```

### Start Nav2 SLAM and open the Nav2 RViz view for mapping

```sh
source install/setup.bash
ros2 launch amr_ros ld90.launch.py use_nav2:=true use_slam:=true
```

```sh
source install/setup.bash
ros2 launch amr_nav2 nav2_rviz.launch.py
```

### Start Nav2 localization with a map from amr_nav2/maps and open the Nav2 RViz view

```sh
source install/setup.bash
ros2 launch amr_ros ld90.launch.py use_nav2:=true use_localization:=true map:=my_map.yaml
```

```sh
source install/setup.bash
ros2 launch amr_nav2 nav2_rviz.launch.py
```

## Start teleoperation

```sh
source install/setup.bash
ros2 launch amr_teleop amr_joyop.launch.py
```
 or 

```sh
ros2 run teleop_twist_keyboard teleop_twist_keyboard
```