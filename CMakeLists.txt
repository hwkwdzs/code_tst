cmake_minimum_required(VERSION 3.16)
set(OpenVINO_DIR "/home/gaoyuhang/.local/lib/python3.10/site-packages/openvino/cmake")
project(auto_aim)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. 使用 pkg-config 获取 OpenCV 信息 (最可靠)
find_package(PkgConfig REQUIRED)
pkg_check_modules(OPENCV REQUIRED opencv4)

# 2. 查找其他库
find_package(yaml-cpp REQUIRED)
find_package(OpenVINO REQUIRED COMPONENTS Runtime)

# 3. 收集源文件
add_executable(main 
    main.cpp
    detector.cpp
    armor.cpp
    classifier.cpp
    tools/logger.cpp
    tools/img_tools.cpp
)

# 4. 【关键】显式链接所有需要的库
# 注意顺序：依赖多的在前，依赖少的在后
target_link_libraries(main 
    # OpenCV 核心模块 (按依赖关系排序)
    ${OPENCV_LIBRARIES} 
    
    # yaml-cpp
    yaml-cpp
    
    # OpenVINO
    openvino::runtime
    
    # C++ 文件系统支持
    stdc++fs
)

# 5. 包含目录
target_include_directories(main PRIVATE
    ${OPENCV_INCLUDE_DIRS}
    /usr/include/yaml-cpp
    /usr/include/eigen3
    ${CMAKE_SOURCE_DIR}
)

# 6. 【关键】强制链接器去正确的目录找库
link_directories(${OPENCV_LIBRARY_DIRS})

# 7. 打印调试信息 (方便查看到底链接了什么)
message(STATUS "OpenCV Libraries: ${OPENCV_LIBRARIES}")
message(STATUS "OpenCV Include Dirs: ${OPENCV_INCLUDE_DIRS}")
message(STATUS "OpenCV Library Dirs: ${OPENCV_LIBRARY_DIRS}")
