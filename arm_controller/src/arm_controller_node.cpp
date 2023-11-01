#include "ros/ros.h"
#include "sensor_msgs/JointState.h"
#include "std_msgs/Float64.h"
#include "std_msgs/String.h"
#include <sstream>


void jointStateCallback(const sensor_msgs::JointState::ConstPtr& msg) {
    for (int i = 0; i < msg->name.size(); ++i) {
        ROS_INFO("Joint %s: Position %f", msg->name[i].c_str(), msg->position[i]);
    }
}


int main(int argc, char **argv) {
    ros::init(argc, argv, "arm_controller_node");
    ros::NodeHandle nh;

    ros::Subscriber jointStateSub = nh.subscribe("arm/joint_states", 10, jointStateCallback);

    ros::Publisher joint1CommandPub = nh.advertise<std_msgs::Float64>("arm/PositionJointInterface_J1_controller/command", 10);
    ros::Publisher joint2CommandPub = nh.advertise<std_msgs::Float64>("arm/PositionJointInterface_J2_controller/command", 10);
    ros::Publisher joint3CommandPub = nh.advertise<std_msgs::Float64>("arm/PositionJointInterface_J3_controller/command", 10);
    ros::Publisher joint4CommandPub = nh.advertise<std_msgs::Float64>("arm/PositionJointInterface_J4_controller/command", 10);
    
    ros::Rate loop_rate(10);

    while (ros::ok()) {

        std_msgs::Float64 joint1Command;
        std_msgs::Float64 joint2Command;
        std_msgs::Float64 joint3Command;
        std_msgs::Float64 joint4Command;

        joint1Command.data = 1.0;  
        joint2Command.data = 0.5;
        joint3Command.data = 0.5;
        joint4Command.data = 0.5;

        joint1CommandPub.publish(joint1Command);
        joint2CommandPub.publish(joint2Command);
        joint3CommandPub.publish(joint2Command);
        joint4CommandPub.publish(joint2Command);

        ros::spinOnce(); 
        loop_rate.sleep();

    }

    return 0;
}
