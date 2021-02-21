/*
 * main.cpp
 */

#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <iostream>
#include <vector>
#include "geometry_msgs/Twist.h"
#include "sensor_msgs/LaserScan.h"

using namespace std;


#define LINEAR_SPEED 0.5
#define ANGULAR_SPEED 0.5
#define MIN_DIST_FROM_OBSTACLE 0.7

void readSensorCallback(const sensor_msgs::LaserScan::ConstPtr &sensor_msg);

bool obstacleFound = false;

int main(int argc, char **argv) {
	ros::init(argc, argv, "random_walk_node");
	ros::NodeHandle nh;

	ros::Publisher cmd_vel_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 10);
	ros::Subscriber base_scan_sub = nh.subscribe<sensor_msgs::LaserScan>(
			"scan", 1, &readSensorCallback);

	//moveForwardCommand variable is used when no obstacle is found
	//Give them appropriate motion
	geometry_msgs::Twist moveForwardCommand; 


	//turnCommand variable is used when obstacle is found and we have to go around it
	//Give them appropriate motion
	geometry_msgs::Twist turnCommand;


    //Incase your bot is stuck for a long time, you can
	//start a count and limit it to 5 counts or 10 counts and then give a counter motion
	int count = 0;

        
	ros::Rate loop_rate(10);

	while (ros::ok()) {

		if (obstacleFound) {
			//ENTER YOUR CODE HERE
			ROS_INFO("Turning around");
		} else {
			//ENTER YOUR CODE HERE
			ROS_INFO("Moving forward");
		}

		ros::spinOnce(); // let ROS process incoming messages
		loop_rate.sleep();
	}

	return 0;
}

//This is where we are detecting the obstacle 
//by hearing (subscribing) the scanner message.
void readSensorCallback(const sensor_msgs::LaserScan::ConstPtr &scan) {
	bool isObstacle = false;
	
	for (int i = 0; i < scan->ranges.size(); i++) {
		if (scan->ranges[i] < MIN_DIST_FROM_OBSTACLE) {
			isObstacle = true;
			break;
		}
	}

	if (isObstacle) {
		ROS_INFO("Obstacle found in front!");
		obstacleFound = true;
	} else {
		obstacleFound = false;
	}
}
