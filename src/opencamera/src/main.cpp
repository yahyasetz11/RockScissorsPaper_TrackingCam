#include <opencv2/opencv.hpp>
#include <rclcpp/rclcpp.hpp>

int main(int argc, char** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::Node node("nama_node");

  cv::VideoCapture cap(0);

  if(!cap.isOpened()) {
    RCLCPP_ERROR(node.get_logger(), "Gagal membuka kamera.");
    return -1;
  }

  cv::Mat frame;

  while(rclcpp::ok()) {
    cap >> frame;
    cv::imshow("Kamera", frame);

    if(cv::waitKey(1) == 'q') {
      break;
    }
  }

  cv::destroyAllWindows();
  return 0;
}
