#include <ros/ros.h>
#include "opencv_hw/ROSInterface.h"
#include "opencv_hw/ColorFilter.h"


int main(int argc, char **argv) {
    ros::init(argc, argv, "image_listener");
    ColorFilter cf;
    ROSInterface rosInter(cf);
        ros::spin();
        return 0;
    }