#include <iostream>
#include <mutex>
#include <atomic>
#include <thread>
#include <fstream>

#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

cv::Point2f clickPoint(-1,-1);

std::atomic<bool> isClicked(false);
std::atomic<bool> isRunning(true);

std::mutex mtx;

void onMouse(int event, int x, int y,int, void *userdata){
    if(event == cv::EVENT_LBUTTONDOWN){
        std::lock_guard<std::mutex> lock(mtx);
        isClicked = true;

        cv::Point2f* p = (cv::Point2f*)userdata;
        p->x = x;
        p->y = y;

        // CSVファイルに書き込む
        std::ofstream ofs("./groundTruth.csv", std::ios::app); // 追加
        ofs << x << "," << y << std::endl; // 追加

        std::cout << "Clicked image coordinates: (" << x << ", " << y << ")" << std::endl;
    }
    return;
}

void displayImage(){
    std::string input_path = "./data/images/img";
    std::string png = ".png";
    std::string num;
    cv::Mat input;

    // image1: 0~ 310
    // image2: 1~ 705
    // image3: 0~ 335
    // image4: 1~518
    // image5: 0~603
    // image6: 0~277
    for(int i=0 ; i < 598 ; i++){
        num = std::to_string(i);
        input = cv::imread(input_path + num + png);
        if(input.empty()){
            std::cerr << "input_image is empty" << std::endl;
            return;
        }
        std::cout << "frame_number = " << num << std::endl;
        cv::imshow("Window",input);

        while (true){
            int key = cv::waitKey(1);
            if(key == 'q' || isClicked == true)break;
        }

        std::lock_guard<std::mutex> lock(mtx);
        isClicked = false;
    }
    return;
}


int main (void){
    cv::namedWindow("Window",cv::WINDOW_NORMAL);
    cv::setMouseCallback("Window", onMouse, &clickPoint);
    // スレッドを作成して関数を実行
    //std::thread clickThread(handleMouseClicks);

    displayImage();

    isRunning = false;
    // スレッドが終了するのを待つ
    //clickThread.join();
    cv::destroyAllWindows();

    return 0;
}
