# Core parameters

This document summarizes the main runtime parameters currently used by the hardware interface and the Nav2 integration.

## Hardware interface parameters

The hardware interface is configured from `amr_ros/config/parameters.yaml`.

### Robot connection

- `robot.ip`: robot controller IP address
- `robot.port`: controller port
- `robot.user`: login user
- `robot.password`: login password
- `robot.protocol`: ARCL protocol profile

### Status publishing

- `status.publish`: enables the status interface and battery publisher
- `status.topic`: robot status topic
- `status.battery_topic`: battery state topic
- `status.publish_period_ms`: status publish period in milliseconds

### Laser scan publishing

- `laser.main_laser.enabled`: enables the primary front laser publisher
- `laser.main_laser.*`: primary front safety laser configuration for `/scan`
- `laser.low_laser.enabled`: enables the low front laser publisher
- `laser.low_laser.*`: low front laser configuration for `/scan_low`
- Each laser block exposes `topic`, `frame_id`, `request`, `request_period_ms`, `angle_min`, `angle_max`, `angle_increment`, `range_min`, and `range_max`

The LD250 description ([ld250.urdf.xacro](../amr_description/xacro/ld250.urdf.xacro) and the static [LD250.urdf](../amr_description/urdf/LD250.urdf)) publishes both `laser_frame` and `laser_frame_low`. When a parent launch overrides `robot_description` with a model that renames these links, set `laser.*.frame_id` to match, otherwise the scans cannot be transformed into `driver.base_frame`.

The published `angle_increment` is derived from the configured angular span and the number of points received in each packet. The configured `angle_increment` acts as a fallback when the packet does not contain enough points to infer a step size.

### Driver interface

- `driver.odom_topic`: odometry topic, currently `/odom`
- `driver.cmd_vel_topic`: velocity command topic, currently `/cmd_vel`
- `driver.stop_topic`: stop topic
- `driver.publish_odom`: enables odometry publication from `amr_core`
- `driver.publish_robot_tf`: enables TF publication from `amr_core`
- `driver.odom_frame`: odom frame name
- `driver.base_frame`: base frame name
- `driver.expected_cmd_vel_freq`: expected command rate used by the cmd_vel watchdog timer
- `driver.min_linear_speed`: minimum linear speed in mm/s
- `driver.max_linear_speed`: maximum linear speed in mm/s
- `driver.min_angular_speed`: minimum angular speed in deg/s
- `driver.max_angular_speed`: maximum angular speed in deg/s
- `driver.drive_throttle_pct`: throttle scaling
- `driver.unsafe_drive`: enables unsafe drive mode
- `driver.cmd_vel_timeout_sec`: watchdog timeout for velocity commands

## Derived Nav2 limits

The Nav2 YAML files were updated to match the driver limits as closely as possible:

- max forward linear velocity: `1.2 m/s`
- max reverse linear velocity: `-0.2 m/s`
- max angular velocity: `1.0472 rad/s`

These values appear in:

- `controller_server.FollowPath`
- `behavior_server`
- `velocity_smoother`

## Nav2 parameter files

Per-robot Nav2 parameters live in:

- `amr_nav2/config/ld90_nav2.yaml`
- `amr_nav2/config/ld250_nav2.yaml`

These files now include:

- driver-aligned velocity limits
- `/odom` as the odometry topic for Nav2 components
- per-robot footprint geometry derived from the robot dimensions

## Footprint values

### LD250

The Nav2 footprint is set to:

```yaml
[[0.475, 0.348], [0.475, -0.348], [-0.475, -0.348], [-0.475, 0.348]]
```

This matches the dimensions documented in the LD250 URDF comments.

### LD90

The Nav2 footprint is set to:

```yaml
[[0.35, 0.25], [0.35, -0.25], [-0.35, -0.25], [-0.35, 0.25]]
```

This matches the dimensions documented in the LD90 xacro comments.

## Map parameter handling

The top-level `map:=...` launch argument is a filename, not a full path.

Example:

```sh
ros2 launch amr_ros ld250.launch.py use_nav2:=true use_localization:=true map:=warehouse.yaml
```

This resolves to:

```text
amr_nav2/maps/warehouse.yaml
```

The corresponding occupancy image file referenced by that YAML must be present alongside it in the same maps directory.
