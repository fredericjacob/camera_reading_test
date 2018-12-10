#include <opencv2/opencv.hpp>

using namespace cv;

class ColorSelector {
    public:
        ColorSelector(std::string windowName);
        ~ColorSelector() {};

        int getLowH();
        int getLowS();
        int getLowV();
        int getHighH();
        int getHighS();
        int getHighV();

        int getLowCannyThresh();
        int getHighCannyThresh();


        // static ColorSelector getInstance() {
        //     if (&instance==NULL) {
        //         instance = ColorSelector("greenFilter");
        //     }
        //     return instance;
        // }



    private:
        

        // static ColorSelector instance;

        int lowH;
        int lowS;
        int lowV;

        int highH;
        int highS;
        int highV;

        int lowCannyThresh;
        int highCannyThresh;
};