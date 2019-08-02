#include "ros/ros.h"
#include "scooterson_test/Temperature.h"
#include <cstdlib>
#include <ctime>

extern "C" {
#include <wiringPi.h>
}

using namespace std;

int main(int argc, char **argv)
{
  ros::init(argc, argv, "node2");
  float temp1, temp2;
  int num;
  time_t t1, t2;
  wiringPiSetup();
  pinMode(1, INPUT);
  pinMode(0, OUTPUT);
  digitalWrite (0, LOW);
  srand(time(0));

  ros::NodeHandle n;
  ros::ServiceClient client = n.serviceClient<scooterson_test::Temperature>("Temperature");
  scooterson_test::Temperature srv;
  srv.request.a = 55;	//Dummy command

  while(1)
  {
	while(digitalRead(1) != 1) {
		usleep(50*1000);
	}
    if (client.call(srv))
    {
	  temp1 = srv.response.sum;	
    }
    else
    {
      ROS_ERROR("Failed to call service add_two_ints");
      return 1;
    }
  
    digitalWrite(0, HIGH);
    t1 = time(nullptr);
    num = (rand() % (50)) + 50;

    for (int i=0;i<10000;i++)
    {
	  for (int j=0;j<5000;j++) 
	  {
	    for (int k=0;k<num;k++) 
	    {
		  i*j*k;
	    }
      }
    }
    
    digitalWrite (0, LOW);
    t2=time(nullptr);    

    if (client.call(srv))
    {
	  temp2 = srv.response.sum;
    }
    else
    {
      ROS_ERROR("Failed to call service add_two_ints");
      return 1;
    }
  
    while(digitalRead(1) != 1) {
		usleep(50*1000);
	}
	
    ROS_INFO("\r\nBegin : %d \t End : %d\t Temp. difference : %f ", 	    
	  t1, t2, (temp2-temp1));
	
	// 1-sec debounce interval for button
	usleep(100*1000);
  }  
  return 0;
}
