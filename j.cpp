#include <opencv2/opencv.hpp>
#include <iostream>
int main() {
// 读取图片,注意example.jpg改成一个真实的图片路径,或者直接把一个叫example.jpg的图片丢到源文件所在的文件夹
cv::Mat image = cv::imread("hello.png");
// 检查图片是否成功加载
if (image.empty()) {
std::cout << "无法加载图片！" << std::endl;
return -1;
}
// 显示图片
cv::imshow("Display Image", image);
// 等待按键
cv::waitKey(0);
return 0;
}
