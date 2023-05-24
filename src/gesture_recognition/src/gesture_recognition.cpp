#include <opencv2/opencv.hpp>

int main()
{
    cv::VideoCapture cap(0);
    if (!cap.isOpened())
    {
        std::cerr << "Error: Could not open camera" << std::endl;
        return -1;
    }

    cv::CascadeClassifier hand_cascade;
    if (!hand_cascade.load("/home/yahyasetz/ros2/gesture_tracking_ws/src/gesture_recognition/src/palm.xml"))
    {
        std::cerr << "Error: Could not load cascade classifier" << std::endl;
        return -1;
    }

    while (true)
    {
        cv::Mat frame;
        cap >> frame;
        if (frame.empty())
            break;

        cv::Mat gray_image;
        cv::cvtColor(frame, gray_image, cv::COLOR_BGR2GRAY);
        cv::equalizeHist(gray_image, gray_image);

        std::vector<cv::Rect> hands;
        hand_cascade.detectMultiScale(gray_image, hands, 1.1, 3, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));

        for (auto& hand : hands)
        {
            cv::rectangle(frame, hand, cv::Scalar(0, 0, 255), 2);
            cv::Mat roi = gray_image(hand);

            cv::Scalar mean_value, std_dev_value;
            cv::meanStdDev(roi, mean_value, std_dev_value);

            if (mean_value[0] > 200 && std_dev_value[0] < 60)
                cv::putText(frame, "Rock", cv::Point(hand.x, hand.y - 10), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 255), 2);
            else if (mean_value[0] > 130 && std_dev_value[0] > 80)
                cv::putText(frame, "Paper", cv::Point(hand.x, hand.y - 10), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 255), 2);
            else if (mean_value[0] < 100 && std_dev_value[0] < 50)
                cv::putText(frame, "Scissors", cv::Point(hand.x, hand.y - 10), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 255), 2);
        }

        cv::imshow("Gesture Recognition", frame);
        if (cv::waitKey(10) == 'q')
            break;
    }

    return 0;
}