# Quick start

1. Install  `flask-socketio`, `nudged`, `fastapi` and `uvicorn` libraries. After this, restart the host machine

```bash
pip install flask-socketio nudged fastapi uvicorn
```

2. Build the package.

```bash
colcon build --symlink-install
```

3. Source required files for the current shell (`bash` is default on Ubuntu).

```bash
source install/setup.bash
```

4. Launch the ROS2 driver.

```bash
ros2 launch om_aiv_util server.launch.py
```
5. Launch RMF nodes together with our fleet manager and fleet adapter.


```bash
ros2 launch fleet_adapter_template all.launch.xml
```
