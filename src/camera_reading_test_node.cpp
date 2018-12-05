#include <ros/ros.h>
#include <opencv2/opencv.hpp>
#include <CameraReader.hpp>
#include <stdio.h>

using namespace cv;

#define LOOP_RATE_IN_HERTZ 50
#define DRAW_GRID


void drawGrid(Mat& mat) {
  int width = mat.cols;
  int height = mat.rows;
  line(mat, Point(0, (height-1)/2), Point(width-1, (height-1)/2), Scalar(0,0,255), 3);
  line(mat, Point((width-1)/2, 0), Point((width-1)/2, height-1), Scalar(0,0,255), 3);
}

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

  ROS_INFO("FPS: %f", reader.getVideoCapture().get(CV_CAP_PROP_FPS));
  //ROS_INFO("Buffer size: %f", reader.getVideoCapture().get(CV_CAP_PROP_BUFFERSIZE));
  ROS_INFO("Open up window...");
  namedWindow("CameraFrame", WINDOW_AUTOSIZE);

  ros::Rate loop_rate(LOOP_RATE_IN_HERTZ);
  while (ros::ok())
  {
    //reader.readImage();
    //ROS_INFO("Number of frames: %f", reader.getNumberOfFrames());
    
    ROS_INFO("Show frame.");
    Mat frame = reader.readImage();
#ifdef DRAW_GRID
    drawGrid(frame);
#endif
    imshow("CameraFrame", reader.readImage());
    waitKey(1); // set to 0 for manual continuation (key-press) or specify auto-delay in milliseconds
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