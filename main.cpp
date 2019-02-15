//
// Created by student4 on 2019/02/15.
//

#include <opencv2/opencv.hpp>

#include "web_camera.h"

int main()
{
    WebCamera webcam(0);

    while(1){
        cv::Mat frame;
        webcam.GetImage(&frame);
        if (frame.empty()){
            break;
        }
        cv::imshow("web camera", frame);
        int k = cv::waitKey(1);
        if (k == 'q') {
            break;
        }
    }
    return EXIT_SUCCESS;
}