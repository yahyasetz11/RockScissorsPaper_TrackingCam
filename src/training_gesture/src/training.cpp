#include <opencv2/opencv.hpp>
#include <array>

int main()
{   
    cv::String rock_dir = "/home/yahyasetz/Downloads/archive/rps-cv-images/rock/";
    cv::String paper_dir = "/home/yahyasetz/Downloads/archive/rps-cv-images/paper/";
    cv::String scissors_dir = "/home/yahyasetz/Downloads/archive/rps-cv-images/scissors/";

    std::vector<cv::String> rock_images;
    std::vector<cv::String> paper_images;
    std::vector<cv::String> scissors_images;

    cv::glob(rock_dir, rock_images);
    cv::glob(paper_dir, paper_images);
    cv::glob(scissors_dir, scissors_images);

    cv::Mat train_data;
    cv::Mat train_labels;

    for (auto& image_path : rock_images)
    {
        cv::Mat image = cv::imread(image_path);
        if (image.empty()) {
            std::cerr << "Error: Could not open image file " << image_path << std::endl;
            continue;
        }
        cv::Mat gray_image;
        cv::cvtColor(image, gray_image, cv::COLOR_BGR2GRAY);
        train_data.push_back(0);
        train_labels.push_back(0);
    }
    std::cout << "Loaded " << train_labels.total() << " rock images." << std::endl;

    for (auto& image_path : paper_images)
    {
        cv::Mat image = cv::imread(image_path);
        if (image.empty()) 
        {
            std::cerr << "Error: Could not open image file " << image_path << std::endl;
            continue;
        }
        cv::Mat gray_image;
        cv::cvtColor(image, gray_image, cv::COLOR_BGR2GRAY);
        train_data.push_back(1);
        train_labels.push_back(1);
    }
    std::cout << "Loaded " << train_labels.total() << " rock & paper images." << std::endl;

    for (auto& image_path : scissors_images)
    {
        cv::Mat image = cv::imread(image_path);
        if (image.empty()) 
        {
            std::cerr << "Error: Could not open image file " << image_path << std::endl;
            continue;
        }
        cv::Mat gray_image;
        cv::cvtColor(image, gray_image, cv::COLOR_BGR2GRAY);
        train_data.push_back(2);
        train_labels.push_back(2);
    }
    std::cout << "Loaded " << train_labels.total() << " rock, paper, & scissors images." << std::endl;

    cv::Mat train_data_float;
    train_data.convertTo(train_data_float, CV_32F);
    std::cout << train_data.rows << " " << train_labels.total() << std::endl;
    assert(train_data.rows == train_labels.total());

    cv::Ptr<cv::ml::TrainData> trainData = cv::ml::TrainData::create(train_data_float, cv::ml::ROW_SAMPLE, train_labels);

    cv::Ptr<cv::ml::SVM> svm = cv::ml::SVM::create();
    svm->setType(cv::ml::SVM::C_SVC);
    svm->setKernel(cv::ml::SVM::LINEAR);
    svm->setTermCriteria(cv::TermCriteria(cv::TermCriteria::MAX_ITER, 100, 1e-6));

    trainData->setTrainTestSplitRatio(0.8);

    svm->train(trainData);

    svm->save("rps_svm2.xml");

    return 0;
}