#include <rclcpp/rclcpp.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/ml.hpp>
#include <iostream>

using namespace cv;
using namespace cv::ml;
using namespace std;

int main(int argc, char** argv)
{
    // Load the input image
    Mat img = imread(argv[1], IMREAD_COLOR);

    // Convert the input image to grayscale
    Mat gray;
    cvtColor(img, gray, COLOR_BGR2GRAY);

    // Resize the input image to 64x64
    Mat resized;
    resize(gray, resized, Size(64, 64));

    // Reshape the input image to a 1D vector
    Mat data = resized.reshape(1, 1);
    data.convertTo(data, CV_32FC1);

    // Load the trained SVM model
    Ptr<SVM> svm = SVM::load("/home/yahyasetz/ros2/detect_image/src/rock_papers/src/rps_svm.xml");

    // Predict the class label of the input image
    float prediction = svm->predict(data);

    // Print the predicted class label
    if (prediction == 0) {
        cout << "Paper" << endl;
    }
    else if (prediction == 1) {
        cout << "Rock" << endl;
    }
    else if (prediction == 2) {
        cout << "Scissors" << endl;
    }
    else {
        cout << "Unknown class label" << endl;
    }

    return 0;
}
