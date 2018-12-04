#include <ros/ros.h>
#include <opencv2/opencv.hpp>
#include <CameraReader.hpp>
#include <stdio.h>

using namespace cv;


int main(int argc, char** argv)
{
  //std::cout << "Hallo erstmal" << std::endl;
  // init this node
  ros::init(argc, argv, "camera_reading_test_node");
  //std::cout << "after init" << std::endl;

  // get ros node handle
  ros::NodeHandle nh;
  //std::cout << "after NodeHandle" << std::endl;


//   // sensor message container
//   sensor_msgs::Range usr, usf, usl;
//   std_msgs::Int16 motor, steering;

//   // generate subscriber for sensor messages
//   ros::Subscriber usrSub = nh.subscribe<sensor_msgs::Range>(
//       "/uc_bridge/usr", 10, boost::bind(usrCallback, _1, &usr));
//   ros::Subscriber uslSub = nh.subscribe<sensor_msgs::Range>(
//       "/uc_bridge/usl", 10, boost::bind(uslCallback, _1, &usl));
//   ros::Subscriber usfSub = nh.subscribe<sensor_msgs::Range>(
//       "/uc_bridge/usf", 10, boost::bind(usfCallback, _1, &usf));

  // generate control message publisher

  ROS_INFO("VIDEO READING TEST");
  char dir_name[100];
  getcwd(dir_name, 100);
  ROS_INFO("Current directory is: %s", dir_name);

  CameraReader reader;

  // Loop starts here:
  // loop rate value is set in Hz
  ros::Rate loop_rate(1);
  while (ros::ok())
  {
    reader.readImage();
    ROS_INFO("Open up window...");
    namedWindow("Frame", WINDOW_AUTOSIZE);
    imshow("Frame", reader.readImage());
    waitKey(0);
    ROS_INFO("Showed frame.");

    // publish command messages on their topics
    // side note: setting steering and motor even though nothing might have
    // changed is actually stupid but for this demo it doesn't matter too much.

    // clear input/output buffers
    ros::spinOnce();
    // this is needed to ensure a const. loop rate
    loop_rate.sleep();
  }

  ros::spin();
}