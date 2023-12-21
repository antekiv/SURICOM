//
// Created by anton on 16.12.23.
//
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>
#include <utility>
#include <chrono>
#include <ctime>

std::string current_time()
{
    const auto now = std::chrono::system_clock::now();
    const std::time_t t_c = std::chrono::system_clock::to_time_t(now);
    auto cur_time = std::string(std::ctime(&t_c));

    std::replace(cur_time.begin(), cur_time.end(), ' ', '-');

    return cur_time;
}

class SimpleCamera
{
public:
    explicit SimpleCamera(std::string stream) : m_stream(std::move(stream)){ };

    void reset(std::string stream) {m_stream = std::move(stream);}
    int process() const
    {
        cv::VideoCapture capture(m_stream);

        if (!capture.isOpened())
            capture.open(atoi(m_stream.c_str()));
        if (!capture.isOpened()) {
            std::cerr << "Failed to open the video device, video file or image sequence!\n" << std::endl;
            return 1;
        }

        std::string filename;
        std::string window_name = "press space to save a picture. q or esc to quit";

        cv::namedWindow(window_name, cv::WINDOW_KEEPRATIO);
        cv::Mat frame;

        for (;;) {
            capture >> frame;
            if (frame.empty())
                break;

            cv::imshow(window_name, frame);
            char key = (char)cv::waitKey(30); //delay N millis, usually long enough to display and capture input

            switch (key) {
                case 'q':
                case 'Q':
                case 27: //escape key
                    return 0;
                case ' ': //Save an image
                    filename = current_time() + ".jpg";
                cv::imwrite(filename,frame);
                std::cout << "Saved " << filename << std::endl;
                break;
                default:
                    break;
            }
        }
        return 0;
    }
private:
    std::string m_stream;
};

int main(int, char**)
{
    SimpleCamera camera("0");
    return camera.process();
}
