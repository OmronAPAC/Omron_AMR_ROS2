# Digital Twin Override Pattern

For mixed real-hardware and simulation workflows, keep the generic AMR defaults in [../amr_ros/config/parameters.yaml](../amr_ros/config/parameters.yaml) or [../amr_ros/config/ld250_parameters.yaml](../amr_ros/config/ld250_parameters.yaml) and layer package-specific overrides on top.

## Launch layering

[../amr_ros/launch/amr_core.launch.py](../amr_ros/launch/amr_core.launch.py) accepts:

- `params_file`: the base hardware parameter file
- `extra_params_file`: an optional overlay file applied after `params_file`

The LD250 wrapper [../amr_ros/launch/ld250.launch.py](../amr_ros/launch/ld250.launch.py) forwards the same `extra_params_file` argument.

## Twin-safe controls

For a simulation-authoritative setup, the libaria-backed driver can remain command-capable while simulation owns robot state. The main controls are:

- `status.publish`
- `laser.main_laser.enabled`
- `laser.low_laser.enabled`
- `driver.publish_odom`
- `driver.publish_robot_tf`

## Example override

Omron Handsolo can layer an override file that looks like this:

```yaml
amr_core:
  ros__parameters:
    status:
      publish: false

    laser:
      main_laser:
        enabled: false
      low_laser:
        enabled: false

    driver:
      publish_odom: false
      publish_robot_tf: false
```

With that arrangement:

- simulation owns TF and odometry
- simulation owns scan publication
- `amr_core` still receives filtered velocity commands and forwards them to the AMR

This keeps robot-state authority in one place instead of splitting it across simulation and hardware interfaces.