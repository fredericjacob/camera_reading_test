#include <CameraReader.hpp>

Mat CameraReader::readImage() {
    cap.read(image);
    return image;
}
