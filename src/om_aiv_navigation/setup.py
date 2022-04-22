from setuptools import setup

package_name = 'om_aiv_navigation'

setup(
    name=package_name,
    version='0.0.0',
    packages=[package_name],
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='omron',
    maintainer_email='guanyewtan@gmail.com',
    description='TODO: Package description',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'action_server = om_aiv_navigation.action_server:main',
            'goto_goal = om_aiv_navigation.goto_goal:main',
            'goto_goal_demo = om_aiv_navigation.goto_goal_demo:main',
            'dock = om_aiv_navigation.dock:main',
            'goto_point = om_aiv_navigation.goto_point:main',
            'localize_at_point = om_aiv_navigation.localize_at_point:main',
            'execute_macro = om_aiv_navigation.execute_macro:main'
        ],
    },
)
