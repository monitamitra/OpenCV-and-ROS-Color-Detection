#include "opencv_hw/ColorFilter.h"
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


 Mat blueSubtract;
 Mat blueThresh;
 cv::Mat blueMask;
 cv::Mat blueImage;

 Mat greenSubtract;
 Mat greenThresh;
 cv::Mat greenMask;
 cv::Mat greenImage;

 Mat redSubtract;
 Mat redThresh;
 cv::Mat redMask;
 cv::Mat redImage;

 cv::Mat threeMask;
 cv::Mat threeImage;

void ColorFilter::processImage(cv::Mat img) {
    _frame = img;
    split();
    findBlue();
    findGreen();
    findRed();
    findBGR();
//    showResult();
}

void ColorFilter::split() {
    cv::split(_frame, _chans);

}

void ColorFilter::showResult() {
    //VideoCapture cap("./three_cups.avi");
    // namedWindow("color");
    // namedWindow("Blue");
    // namedWindow("Green");
    // namedWindow("Red");

    // namedWindow("blueSubtract");
    //namedWindow("blueThresh");
    //namedWindow("blueBlob");
    //namedWindow("finalBlue");
    //namedWindow("greenSubtract");
    //namedWindow("greenThresh");
    //namedWindow("greenBlob");
    //namedWindow("finalGreen");
    //namedWindow("redSubtract");
    //namedWindow("redThresh");
    //namedWindow("redMask");
    //namedWindow("redImage");
    //namedWindow("allThree");
    
    // PROBLEM 1
    // imshow("color", _frame);
   
//    PROBLEM 2 B
//    imshow("Blue", _chans[0]);
//     PROBLEM 2 G
//    imshow("Green", _chans[1]);
//     PROBLEM 2 R
//    imshow("Red", _chans[2]);

//     PROBLEM 3: Blue Subtraction
//    imshow("blueSubtract", blueSubtract);

//    PROBLEM 3: Blue Threshold
//      imshow("blueThresh", blueThresh);

//    PROBLEM 3: Largest Blue Blob
//        imshow("blueBlob", blueMask);

// PROBLEM 3: Show Blue Cup
//          imshow("finalBlue", blueImage);

// PROBLEM 4: Green Subtraction
//          imshow("greenSubtract", greenSubtract);

// PROBLEM 4: Green Threshold
//            imshow("greenThresh", greenThresh);

// PROBLEM 4: Largest Green Blob
//              imshow("greenBlob", greenMask);

// PROBLEM 4: Show Green Cup
//                imshow("finalGreen", greenImage);

// PROBLEM 5: Red Subtraction
//                imshow("redSubtract", redSubtract);

// PROBLEM 5: Red Threshold
//                imshow("redThresh", redThresh);

// PROBLEM 5: Largest Red Blob
//                  imshow("redMask", redMask);

// PROBLEM 5: Show Red Cup
//                    imshow("redImage", redImage);

// PROBLEM 6: ALL THREE
//                      imshow("allThree", threeImage);


//     waitKey(200);
}


void ColorFilter::findBlue() {
   cv::subtract(_chans[0], _chans[2], blueSubtract);
   cv::threshold(blueSubtract, blueThresh, 50, 255, cv::THRESH_BINARY);
   std::vector<cv::Mat> contours;
   std::vector<cv::Vec4i> hierarchy;
        findContours(blueThresh, contours, hierarchy, cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE);

        int maxSizeContour = 0;
        int maxContourSize = 0;

        for (int i = 0; i < contours.size(); i++) {
            int contourSize = cv::contourArea(contours[i]);
            if (contourSize > maxContourSize) {
                maxSizeContour = i;
                maxContourSize = contourSize;
            }
        }
     blueMask = cv::Mat::zeros(_frame.rows, _frame.cols, CV_8UC1);
     drawContours(blueMask, contours, maxSizeContour, cv::Scalar(255), cv::LineTypes::FILLED, 8, hierarchy);
     blueImage = cv::Mat::zeros(_frame.rows, _frame.cols, CV_8UC3);
     _frame.copyTo(blueImage, blueMask);
}

void ColorFilter::findGreen() {
    cv::subtract(_chans[1], _chans[0], greenSubtract);
    cv::threshold(greenSubtract, greenThresh, 87, 255, cv::THRESH_BINARY);
    std::vector<cv::Mat> contours;
    std::vector<cv::Vec4i> hierarchy;
        findContours(greenThresh, contours, hierarchy, cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE);

        int maxSizeContour = 0;
        int maxContourSize = 0;

        for (int i = 0; i < contours.size(); i++) {
            int contourSize = cv::contourArea(contours[i]);
            if (contourSize > maxContourSize) {
                maxSizeContour = i;
                maxContourSize = contourSize;
            }
        }

    greenMask = cv::Mat::zeros(_frame.rows, _frame.cols, CV_8UC1);
    drawContours(greenMask, contours, maxSizeContour, cv::Scalar(255), cv::LineTypes::FILLED, 8, hierarchy);
    greenImage = cv::Mat::zeros(_frame.rows, _frame.cols, CV_8UC3);
     _frame.copyTo(greenImage, greenMask);

}

void ColorFilter::findRed() {
    cv::subtract(_chans[2], _chans[1], redSubtract);
    cv::threshold(redSubtract, redThresh, 50, 255, cv::THRESH_BINARY);
    std::vector<cv::Mat> contours;
    std::vector<cv::Vec4i> hierarchy;
        findContours(redThresh, contours, hierarchy, cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE);

        int maxSizeContour = 0;
        int maxContourSize = 0;

        for (int i = 0; i < contours.size(); i++) {
            int contourSize = cv::contourArea(contours[i]);
            if (contourSize > maxContourSize) {
                maxSizeContour = i;
                maxContourSize = contourSize;
            }
        }

     redMask = cv::Mat::zeros(_frame.rows, _frame.cols, CV_8UC1);
        drawContours(redMask, contours, maxSizeContour, cv::Scalar(255), cv::LineTypes::FILLED, 8, hierarchy);
        redImage = cv::Mat::zeros(_frame.rows, _frame.cols, CV_8UC3);
     _frame.copyTo(redImage, redMask);


}

void ColorFilter::findBGR() {
    cv::bitwise_or(blueMask, redMask, threeMask);
    cv::bitwise_or(greenMask, threeMask, threeMask);
    threeImage = cv::Mat::zeros(_frame.rows, _frame.cols, CV_8UC3);
     _frame.copyTo(threeImage, threeMask);

}

cv::Mat ColorFilter::getBlueImage() {
    return blueImage;
}

cv::Mat ColorFilter::getGreenImage() {
    return greenImage;

}

cv::Mat ColorFilter::getRedImage() {
    return redImage;

}

cv::Mat ColorFilter::getBGRImage() {
    return threeImage;

}