/****************************************************************************
 Autor: Moacir Wendhasuen 
 Data: 17/01/2022

*****************************************************************************/

#include "ros/ros.h"  // Header para o pacotes do ROS
#include <string>
#include "std_msgs/String.h" // Headder necesśário para poder publicar msgs.


int main(int argc, char **argv){
    ros::init(argc, argv, "trigger_sensors");
    ros::NodeHandle nh;
    ros::Rate loop_rate(1);

    ros::Publisher trigger_pub = nh.advertise < std_msgs::String>("trigger_sensors",1000);


    int count=0;
    std::string msgPadrao= "Trigger dos sensores numero: " ;

    while (ros::ok()){
        std::string msg= msgPadrao + std::to_string(count);

        ROS_INFO("%s", msg.c_str());

        std_msgs::String msg_pub;
        msg_pub.data= msg;

        trigger_pub.publish(msg_pub);
        

        ros::spinOnce();
        loop_rate.sleep();
        count++;
    }

    return 0;
}