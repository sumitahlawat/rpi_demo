#include "ros/ros.h"
#include "scooterson_test/Temperature.h"

bool get_temp(scooterson_test::Temperature::Request  &req,
         scooterson_test::Temperature::Response &res)
{
  FILE *temperatureFile;
  float T;
  temperatureFile = fopen ("/sys/class/thermal/thermal_zone0/temp", "r");
  if (temperatureFile == NULL) {
    ROS_INFO("file open fail");
    res.sum = 50.0;
  }
  else {
    fscanf (temperatureFile, "%f", &T);
    T /= 1000;  
    res.sum = T;
  }
  fclose (temperatureFile);
  ROS_INFO("sending back response: [%f]", (float)res.sum);
  return true;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "temperature_server");
  ros::NodeHandle n;

  ros::ServiceServer service = n.advertiseService("Temperature", get_temp);
  ROS_INFO("Ready to cpu temp.");
  ros::spin();

  return 0;
}
