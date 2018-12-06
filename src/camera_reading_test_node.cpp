#include <ros/ros.h>
#include <opencv2/opencv.hpp>
#include <CameraReader.hpp>
#include <image_processor.hpp>
#include <stdio.h>

using namespace cv;

//#define TEST_PICTURE_PATH "camera_reading_test/images/calibration_test_2.jpg"
#define TEST_PICTURE_PATH "camera_reading_test/images/track_straight.jpg"


#define USE_TEST_PICTURE
#define LOOP_RATE_IN_HERTZ 50
//#define DRAW_GRID


void drawGrid(Mat& mat) {
  int width = mat.cols;
  int height = mat.rows;
  line(mat, Point(0, (height-1)/2), Point(width-1, (height-1)/2), Scalar(0,0,255), 1);
  line(mat, Point((width-1)/2, 0), Point((width-1)/2, height-1), Scalar(0,0,255), 1);
}

int main(int argc, char** argv)
{
  // init this node
  ros::init(argc, argv, "camera_reading_test_node");

  ros::NodeHandle nh;
  Mat frame;

#ifdef USE_TEST_PICTURE
  frame = imread(TEST_PICTURE_PATH, IMREAD_COLOR);
  if (frame.empty()) {
    ROS_ERROR("Test image could not be opened!");
  }
#endif
  ROS_INFO("VIDEO READING TEST");
  char dir_name[100];
  getcwd(dir_name, 100);
  ROS_INFO("Current directory is: %s", dir_name);

#ifndef USE_TEST_PICTURE
  CameraReader reader;


  ROS_INFO("FPS: %f", reader.getVideoCapture().get(CV_CAP_PROP_FPS));
  //ROS_INFO("Buffer size: %f", reader.getVideoCapture().get(CV_CAP_PROP_BUFFERSIZE));
#endif
  
  // TODO: for more meaningful testing, move object creation in the loop
  ImageProcessor imageProcessor(frame);
  imageProcessor.calibrateCameraImage(59.0,84.0,30.0,
            Point(0,366),Point(632,363),Point(404,238),Point(237,237),
            Point(151,639),Point(488,639),Point(488,0),Point(151,0)

  );

  imshow("CameraFrame", frame);
  waitKey(0);

  frame = imageProcessor.transformTo2D();
  
  ROS_INFO("Open up window...");
  //namedWindow("CameraFrame", WINDOW_AUTOSIZE);

  ros::Rate loop_rate(LOOP_RATE_IN_HERTZ);
  while (ros::ok())
  {
    //reader.readImage();
    //ROS_INFO("Number of frames: %f", reader.getNumberOfFrames());
    
    ROS_INFO("Show frame.");
#ifndef USE_TEST_PICTURE
    frame = reader.readImage();
#endif
#ifdef DRAW_GRID
    drawGrid(frame);
#endif
    imshow("CameraFrame", frame);
    waitKey(1); // set to 0 for manual continuation (key-press) or specify auto-delay in milliseconds
    ROS_INFO("Showed frame.");

    // clear input/output buffers
    ros::spinOnce();
    // this is needed to ensure a const. loop rate
    loop_rate.sleep();
  }

  ros::spin();
}