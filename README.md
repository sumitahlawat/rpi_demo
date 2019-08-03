# Raspberry Pi Demo with ROS
A simple cpu benchmark stress test using Robot Operating System (ROS).

# Introduction 
This project uses client-service node model from ROS containing following nodes.
1. Node 1 - A service which returns current CPU temperature when called for
2. Node 2 - serrvice client which is waiting for button trigger to run a cpu stress test.
It connects to Node 1 service to get cpu temperature.

This project uses wiringPi library to control raspberry Pi gpio.
Button is at wiringPi pin 0, press this to trigger node 1 example, press again to see output result.
LED is connected to wiringPi pin 1 (not neccessary)

# Run
1. roscore
2. rosrun scooterson_test node1
2. rosrun scooterson_test node2

Run time varies 20-40 seconds, as stress test uses rand() input.
Remove it make run time consistent

Output fom node 2
Begin : <> 	 End : <>	 Temp. difference : <>


# References
1. ROS kinectic on Raspberry Pi - http://wiki.ros.org/ROSberryPi/Installing%20ROS%20Kinetic%20on%20the%20Raspberry%20Pi#Setup_ROS_Repositories
2. Updated keys for raspian - https://answers.ros.org/question/325039/apt-update-fails-cannot-install-pkgs-key-not-working/
3. ROS tutorial - http://wiki.ros.org/ROS/Tutorials
