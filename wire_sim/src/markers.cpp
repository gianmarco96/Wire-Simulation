#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <tf2/LinearMath/Quaternion.h>
#include <cmath>
#include <string>

void init_f_vec(visualization_msgs::Marker &f_vec, float R,float P,float Y, int colour){
    // Set our initial shape type to be a cube
    uint32_t shape = visualization_msgs::Marker::ARROW;

    f_vec.header.frame_id = "load_cell_centre";
    f_vec.header.stamp = ros::Time::now();

    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
    f_vec.ns = "force_vectors";

    // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
    f_vec.type = shape;

    // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
    f_vec.action = visualization_msgs::Marker::ADD;

    // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header

    tf2::Quaternion quatBuffer; 
    quatBuffer.setRPY(R, P, Y);
    f_vec.pose.position.x = 0;
    f_vec.pose.position.y = 0;
    f_vec.pose.position.z = 0;
    f_vec.pose.orientation.x = quatBuffer.x();
    f_vec.pose.orientation.y = quatBuffer.y();
    f_vec.pose.orientation.z = quatBuffer.z();
    f_vec.pose.orientation.w = quatBuffer.w();

    // Set the scale of the marker -- 1x1x1 here means 1m on a side
    f_vec.scale.x = 0.05;
    f_vec.scale.y = 0.01;
    f_vec.scale.z = 0.01;

    f_vec.lifetime = ros::Duration();

    switch (colour)
    {
    case 1:
        f_vec.color.r = 1.0f;
        f_vec.color.g = 0.0f;
        f_vec.color.b = 0.0f;
        f_vec.color.a = 1.0;
        f_vec.id = 0;
        break;
    case 2:
        f_vec.color.r = 0.0f;
        f_vec.color.g = 1.0f;
        f_vec.color.b = 0.0f;
        f_vec.color.a = 1.0;
        f_vec.id = 1;
        break;
    case 3:
        f_vec.color.r = 0.0f;
        f_vec.color.g = 0.0f;
        f_vec.color.b = 1.0f;
        f_vec.color.a = 1.0;
        f_vec.id = 2;
        break;
    
    default:
        ROS_ERROR("Wrong color assignment received please use 1 for RED, 2 for GREEN, or 3 for BLUE");
        break;
    }

    
}

int main( int argc, char** argv )
{
  ros::init(argc, argv, "force_vectors");
  ros::NodeHandle n;
  ros::Rate r(1000);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("force_marker", 2);

  int i = 0;


  while (ros::ok())
  {
    visualization_msgs::Marker zf_vector;
    init_f_vec(zf_vector, 0, -1.5708,0 , 3);

    visualization_msgs::Marker xf_vector;
    init_f_vec(xf_vector, 0, 0, -1.5708, 1);

    visualization_msgs::Marker yf_vector;
    init_f_vec(yf_vector, 0,0,0, 2);
    
    // Publish the marker
    while (marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
        return 0;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      sleep(1);
    }

    marker_pub.publish(zf_vector);
    // i++;
    // yf_vector.scale.x = sin(i*0.021);
    marker_pub.publish(yf_vector);
    marker_pub.publish(xf_vector);

    

    r.sleep();
  }
}