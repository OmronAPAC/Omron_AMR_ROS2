import os
from setuptools import setup
from glob import glob

package_name = 'handeye_4dof_ros2'
submodules = 'handeye_4dof_ros2/handeye_4dof'

setup(
    name=package_name,
    version='0.0.0',
    packages=[package_name, submodules],
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),        
        (os.path.join('share', package_name, 'launch'), glob('launch/*.launch.py')),
        (os.path.join('share', package_name, 'config'), glob('config/*.yaml'))
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='zeon',
    maintainer_email='ennzerothreetwo@gmail.com',
    description='TODO: Package description',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'handeye_4dof_node = handeye_4dof_ros2.handeye_4dof_node:main'
        ],
    },
)
