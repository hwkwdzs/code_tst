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
    
    // 2. 打开视频 修改
    cv::VideoCapture cap("./demo.avi");
    if (!cap.isOpened()) {
        std::cerr << "❌ 无法打开视频：demo.avi" << std::endl;
        return -1;
    }
    
    std::cout << "📹 视频：" 
              << cap.get(cv::CAP_PROP_FRAME_WIDTH) << "x" 
              << cap.get(cv::CAP_PROP_FRAME_HEIGHT) << " @ " 
              << cap.get(cv::CAP_PROP_FPS) << "fps" << std::endl;
    
       // ... (前面的初始化代码不变)

    cv::Mat frame;
    int frame_count = 0;
    bool is_paused = false; // 暂停标志位

    // 修改点：把 while 条件改为 true，手动控制读取
    while (true) {
        // 【关键修复】只有在非暂停状态下才读取新帧
        if (!is_paused) {
            if (!cap.read(frame)) {
                std::cout << "\n视频结束或读取失败" << std::endl;
                break;
            }
            if (frame.empty()) break;
            
            frame_count++;
            std::cout << "\r处理帧：" << frame_count << std::flush;
            
            // 4. 检测装甲板 (只有非暂停时才检测)
            auto armors = detector.detect(frame, frame_count);
        } else {
            // 暂停时：在画面上添加一个醒目的 "PAUSED" 水印
            cv::putText(frame, "PAUSED", cv::Point(50, 80), 
                        cv::FONT_HERSHEY_SIMPLEX, 2, cv::Scalar(0, 0, 255), 3);
        }

        // 5. 显示结果 (无论是否暂停都显示，暂停时显示的是旧 frame + 文字)
        // 注意：detector 内部也会 imshow，这里主要为了统一控制
        // 如果 detector 内部已经显示了 detection 窗口，这里可以注释掉，或者只显示原始 frame
        // cv::imshow("Video", frame); 

        // --- 按键监听 ---
        int key = cv::waitKey(30); 
        
        if (key == 27 || key == 'q') { // ESC 或 q 退出
            std::cout << "\n用户退出" << std::endl;
            break;
        }
        
        if (key == 'p' || key == 'P') { // P 键切换暂停
            is_paused = !is_paused;
            if (is_paused) {
                std::cout << "\n[已暂停] 画面冻结。按 'P' 继续，按 'ESC' 退出。" << std::endl;
            } else {
                std::cout << "\n[继续运行]" << std::endl;
            }
        }
    }

    // ... (后面的清理代码不变)
    
    cap.release();
    cv::destroyAllWindows();
    std::cout << "\n✅ 完成，共处理 " << frame_count << " 帧" << std::endl;
    
    return 0;
}
