from setuptools import setup
import os
from glob import glob

package_name = 'map_navigation2'

setup(
    name=package_name,
    version='0.0.0',
    packages=[package_name],
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        (os.path.join('share', package_name), glob('launch/*_launch.py')),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='dasnote11',
    maintainer_email='dasnote11@todo.todo',
    description='TODO: Package description',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'path_uncertainty = map_navigation2.path_uncertainty:main',
            'picture_tracking = map_navigation2.picture_tracking:main',
            'tf2twist = map_navigation2.tf2twist:main',
            'changetopicname = map_navigation2.changetopicname:main',
            'world = map_navigation2.world:main',
            'circle_movement = map_navigation2.circle_movement:main',
            'move_robot = map_navigation2.move_robot:main',
            'second_move_robot = map_navigation2.second_move_robot:main',
            'camera = map_navigation2.camera:main',
            ##以下に付け足していく　by堀江
            
        ],
    },
)
