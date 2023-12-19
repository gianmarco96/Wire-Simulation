#include <ros/ros.h>
#include <visualization_msgs/Marker.h>

#include <tf2/LinearMath/Quaternion.h>

#include <cmath>

int main( int argc, char** argv )
{
  ros::init(argc, argv, "points_and_lines");
  ros::NodeHandle n;
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 10);

  ros::Rate r(30);

  float f = 0.0;
  float i = 0;
  while (ros::ok())
  {
    /*
    visualization_msgs::Marker points, line_strip, line_list, mesh;
    points.header.frame_id = line_strip.header.frame_id = line_list.header.frame_id = mesh.header.frame_id= "my_frame";
    points.header.stamp = line_strip.header.stamp = line_list.header.stamp = mesh.header.stamp =ros::Time::now();
    points.ns = line_strip.ns = line_list.ns = mesh.ns = "points_and_lines";
    points.action = line_strip.action = line_list.action = mesh.action= visualization_msgs::Marker::ADD;
    points.pose.orientation.w = line_strip.pose.orientation.w = line_list.pose.orientation.w = mesh.pose.orientation.w = 1.0;



    points.id = 0;
    line_strip.id = 1;
    line_list.id = 2;
    mesh.id = 3;



    points.type = visualization_msgs::Marker::POINTS;
    line_strip.type = visualization_msgs::Marker::LINE_STRIP;
    line_list.type = visualization_msgs::Marker::LINE_LIST;

    mesh.type = visualization_msgs::Marker::MESH_RESOURCE;
    mesh.mesh_resource  = "file:///home/ubuntu20/ke_ws/src/panda_multiple_arms/meshes/- End_Effector_Assem_Redesign_Drive.stl"; 


    
    // POINTS markers use x and y scale for width/height respectively
    points.scale.x = 0.2;
    points.scale.y = 0.2;

    // LINE_STRIP/LINE_LIST markers use only the x component of scale, for the line width
    line_strip.scale.x = 0.1;
    line_list.scale.x = 0.1;



    // Points are green
    points.color.g = 1.0f;
    points.color.a = 1.0;

    // Line strip is blue
    line_strip.color.b = 1.0;
    line_strip.color.a = 1.0;

    // Line list is red
    line_list.color.r = 1.0;
    line_list.color.a = 1.0;



    geometry_msgs::Point p;
    i -= 0.01; 
    std::cout << i << std::endl;
    p.x = 1;
    p.y = 0;
    p.z = 0;
    points.points.push_back(p);
    line_list.points.push_back(p);
    p.x = 3;
    p.z = 5+i;

    points.points.push_back(p);
    line_list.points.push_back(p);
    mesh.points.push_back(p);
    mesh.scale.x = 100.0;
    */

    //marker_pub.publish(points);
    //marker_pub.publish(line_strip);
    //marker_pub.publish(line_list);
    tf2::Quaternion myQuaternion; 
    myQuaternion.setRPY(1.5708,0,0);
    myQuaternion = myQuaternion.normalize();
    geometry_msgs::Pose pose;
    pose.position.x = 0.042/2;
    pose.position.y = 0.1227/2;
    pose.position.z = (0.9588+0.006)/2;
    pose.orientation.x = myQuaternion.x();
    pose.orientation.y = myQuaternion.y();
    pose.orientation.z = myQuaternion.z();
    pose.orientation.w = myQuaternion.w();

    std_msgs::ColorRGBA colour;
    colour.a = 1;
    colour.r = 0.19;
    colour.g = 0.19;
    colour.b = 0.19;

    visualization_msgs::Marker marker;

    marker.header.frame_id = "world";
    marker.header.stamp = ros::Time::now();
    marker.action = visualization_msgs::Marker::ADD;
    marker.type = visualization_msgs::Marker::MESH_RESOURCE;
    marker.pose = pose;
    marker.id = 0;
    marker.mesh_resource = "file:///home/ubuntu20/wire_sim_ws/src/wire_sim/meshes/- End_Effector_Assem_Redesign_Drive.stl";
    marker.scale.x = 1;
    marker.scale.y = 1;
    marker.scale.z = 1;
    marker.color = colour;
  

    marker_pub.publish(marker);
    //i += 0.02;

    //marker.pose.position.y += i;
    //marker_pub.publish(marker);
    //std::cout << marker.pose.position.x << std::endl;

    r.sleep();

    f += 0.04;
  }
}