# 这些是编译命令   没有用cmake

# 重新编译
cd ~/code_tst
g++ -std=c++17 -O2 main.cpp detector.cpp armor.cpp classifier.cpp tools/logger.cpp tools/img_tools.cpp -I/usr/include/opencv4 -I/usr/include/yaml-cpp -I/usr/include/eigen3 -I. -o main -lyaml-cpp -lopencv_dnn -lopencv_objdetect -lopencv_calib3d -lopencv_videoio -lopencv_imgcodecs -lopencv_highgui -lopencv_imgproc -lopencv_core -lstdc++fs -ldl -lpthread

# 运行
./main