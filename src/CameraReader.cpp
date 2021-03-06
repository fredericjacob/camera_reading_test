#include <CameraReader.hpp>

#define FRAMES_TO_DISCARD 4



CameraReader::CameraReader(): cap(
#ifdef DEBUG
            VideoCapture("test.mp4")
#else
            VideoCapture()
#endif
            ) {
#ifndef DEBUG
    cap.open(0);
    if (!cap.isOpened()) {
        cap.open(1);
    }
    if (!cap.isOpened()) {
        std::cerr << "No video opened" << std::endl;
    }
    cap.set(CV_CAP_PROP_FRAME_WIDTH, INIT_VIDEO_WIDTH);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT, INIT_VIDEO_HEIGHT);
#endif
}

Mat CameraReader::readImage() {
    // int numOfGrabbedImages = 0;
    // while (cap.grab()) {
    //     numOfGrabbedImages++;
    // }
    // std::cout << "%d images grabbed." << std::endl;

    // discard the first 4 (the older) frames in the buffer
    // POSSIBLE ALTERNATIVE / OPTIMIZATION: own thread for constantly reading and writing frames in a buffer with size, other thread reads the last element
    for (int i=0; i<FRAMES_TO_DISCARD; i++) {   // TODO examine if the 5th frame is really the most recent one
        cap.grab();
    }
    cap.read(image);
    return image;
}

void CameraReader::setRelativePositionInVideo(double pos) {
    cap.set(CV_CAP_PROP_POS_AVI_RATIO, pos);
}
double CameraReader::getNumberOfFrames() {
    return cap.get(CV_CAP_PROP_FRAME_COUNT);
}
VideoCapture& CameraReader::getVideoCapture() {
    return cap;
}
