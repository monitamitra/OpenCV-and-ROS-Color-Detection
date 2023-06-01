#ifndef ROS_INTERFACE_H
#define ROS_INTERFACE_H
#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include "opencv_hw/ColorFilter.h"
#include <cv_bridge/cv_bridge.h>

class Colorfilter; 

class ROSInterface {
    protected: 
    ColorFilter cf;

ros::NodeHandle nh;
image_transport::ImageTransport it;

image_transport::Publisher pubBlueImage;
image_transport::Publisher pubGreenImage;
image_transport::Publisher pubRedImage; 
image_transport::Publisher pubBGRImage;
image_transport::Subscriber printColor;

public:
ROSInterface(ColorFilter cf);
void imageCallBack(const sensor_msgs::ImageConstPtr& msg);
};

#endif 