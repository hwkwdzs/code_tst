// 【关键修复】强制先加载并锁定标准库，防止 fmt 污染
#include <iostream>
#include <string>
#include <vector>
#include <locale>
#include <sstream>
#include <iomanip>
#include <clocale>

// 现在再包含其他头文件
#include <opencv2/opencv.hpp>
#include <yaml-cpp/yaml.h>
#include <numeric>  // 用于 std::accumulate

// ... 下面是你原来的代码 ...// 1. 先包含标准库头文件
#include <iostream>
#include <string>
#include <locale>
#include <sstream>

// 2. 再包含 OpenCV
#include <opencv2/opencv.hpp>

// 3. 最后包含项目头文件
#include "detector.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>
#include "detector.hpp"

int main()
{
    std::cout << "=== 装甲板视觉检测 ===" << std::endl;
    
    // 1. 创建检测器（需要配置文件）
    std::string config_path = "./config.yaml";
    auto_aim::Detector detector(config_path, true);  // true = 调试模式（显示窗口）
    std::cout << "✅ 检测器初始化成功" << std::endl;
    
    // 2. 打开视频
    cv::VideoCapture cap("./demo.avi");
    if (!cap.isOpened()) {
        std::cerr << "❌ 无法打开视频：demo.avi" << std::endl;
        return -1;
    }
    
    std::cout << "📹 视频：" 
              << cap.get(cv::CAP_PROP_FRAME_WIDTH) << "x" 
              << cap.get(cv::CAP_PROP_FRAME_HEIGHT) << " @ " 
              << cap.get(cv::CAP_PROP_FPS) << "fps" << std::endl;
    
    // 3. 逐帧处理
    cv::Mat frame;
    int frame_count = 0;
    
    while (cap.read(frame)) {
        frame_count++;
        if (frame.empty()) break;
        
        std::cout << "\r处理帧：" << frame_count << std::flush;
        
        // 4. 检测装甲板（detector.cpp 中的 detect 函数）
        auto armors = detector.detect(frame, frame_count);
        
        // 5. 显示结果（调试模式下 detector 内部已显示）
        cv::imshow("Video", frame);
        
        // 6. 按 ESC 退出
        if (cv::waitKey(30) == 27) {
            std::cout << "\n用户退出" << std::endl;
            break;
        }
    }
    
    cap.release();
    cv::destroyAllWindows();
    std::cout << "\n✅ 完成，共处理 " << frame_count << " 帧" << std::endl;
    
    return 0;
}
