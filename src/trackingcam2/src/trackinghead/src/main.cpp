#include <rclcpp/rclcpp.hpp>
#include <opencv2/opencv.hpp>
#include <sensor_msgs/msg/image.hpp>

using namespace std::chrono_literals;

class TrackingCamNode : public rclcpp::Node {
public:
  TrackingCamNode() : Node("tracking_cam_node") {
    // Load face detector model
    if (!face_cascade.load("/home/yahyasetz/ros2/trackingcam2/src/trackinghead/src/haarcascade.xml")) {
      RCLCPP_ERROR(get_logger(), "Failed to load face detector model");
      return;
    }

    // Open default camera
    cap = cv::VideoCapture(0);
    if (!cap.isOpened()) {
      RCLCPP_ERROR(get_logger(), "Failed to open camera");
      return;
    }

    // Create publisher for face image
    face_pub = this->create_publisher<sensor_msgs::msg::Image>("face_image", 10);

    // Create timer for processing frames
    timer = create_wall_timer(16ms, [this]() { processFrame(); });
  }

private:
  cv::CascadeClassifier face_cascade;
  cv::VideoCapture cap;
  rclcpp::TimerBase::SharedPtr timer;
  rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr face_pub;

  void processFrame() {
    cv::Mat frame;
    cap >> frame;
    if (frame.empty()) {
      RCLCPP_ERROR(get_logger(), "Failed to read frame");
      return;
    }

    // Convert to grayscale and detect faces
    cv::Mat gray;
    cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
    std::vector<cv::Rect> faces;
    face_cascade.detectMultiScale(gray, faces);

    // Draw bounding box around each face and publish face image
    for (const auto& face : faces) {
      cv::rectangle(frame, face, cv::Scalar(0, 0, 255), 2);
      cv::Mat face_img = frame(face);
      sensor_msgs::msg::Image msg;
      msg.header.stamp = now();
      msg.height = face_img.rows;
      msg.width = face_img.cols;
      msg.encoding = "bgr8";
      msg.is_bigendian = false;
      msg.step = face_img.cols * 3;
      msg.data = std::vector<uint8_t>(face_img.data, face_img.data + face_img.total() * face_img.elemSize());
      face_pub->publish(msg);
    }

    // Show the frame
    cv::imshow("TrackingCam", frame);
    cv::waitKey(1);
  }
};

int main(int argc, char** argv) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<TrackingCamNode>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
