#ifndef CAMERA_READER_HPP_
#define CAMERA_READER_HPP_

// read a file "test.mp4" instead of the webcam input if active
#define DEBUG

#include <opencv2/opencv.hpp>
using namespace cv;


class CameraReader {
    public:

        CameraReader(): cap(
#ifdef DEBUG
            VideoCapture("test.mp4")
#else
            VideoCapture(0)
#endif
            ){};
        ~CameraReader(){};


        Mat readImage();

    private:
        VideoCapture cap;
        Mat image;
};



#endif // CAMERA_READER_HPP_