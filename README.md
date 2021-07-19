# om_aiv - ROS Packages for Omron Mobile Robot
![omron ld robot](https://assets.omron.com/m/438d82ed579472a4/Portrait_M-Mobile_Robot_Product-News-jpg.jpg "omron ld robot")

This repository contains various ROS packages that allows you to interface with your Omron AMR Mobile Robot via the ROS environment.

## Supported Features
1. Capture AMR status information
    * General status of AMR
    * Laser scan values
    * Odometer values
    * Map goals
    * Application fault messages
2. Visualize AMR via RVIZ tool
    * Display loaded map
    * Display live laser scans
    * Display forbidden areas
    * Display map goals
3. Navigate AMR
    * Go to specified goal point
    * Go back to designated dock

**For details on the packages' inner workings, see the [Developer's Guide](https://github.com/guanyewtan/Omron_LD/blob/master/docs/DeveloperGuide.adoc).**

## Limitations
ROS is not able to have access to robot hardware, therefore this package does not have full access to all AMR's capabilities. This package uses ARCL to communicate and control the AMR and thus the limitations of this package is defined by ARCL's limitations.

## References
ARCL Reference Guide, 18448-000 Rev A, Updated: 1/19/2017 which is included in root directory of this repository.
