cmake_minimum_required(VERSION 3.16)
set(OpenVINO_DIR "/home/gaoyuhang/.local/lib/python3.10/site-packages/openvino/cmake")
project(auto_aim)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. 获取 OpenCV 信息
find_package(PkgConfig REQUIRED)
pkg_check_modules(OPENCV REQUIRED opencv4)

# 2. 查找 yaml-cpp (只为了获取路径)
find_package(yaml-cpp REQUIRED)

# 3. 查找 OpenVINO
find_package(OpenVINO REQUIRED COMPONENTS Runtime)

# 4. 收集源文件
add_executable(main 
    main.cpp
    detector.cpp
    armor.cpp
    classifier.cpp
    tools/logger.cpp
    tools/img_tools.cpp
)

# 5. 【关键】构建明确的库列表
# 使用 ${OPENCV_LIBRARIES} 展开所有 opencv 库
# 使用 ${yaml-cpp_LIBRARIES} 或手动指定 yaml-cpp 路径
set(MY_LIBS
    ${OPENCV_LIBRARIES}
    ${yaml-cpp_LIBRARIES}  # 尝试使用 CMake 找到的变量
    openvino::runtime
    stdc++fs
)

# 如果上面 yaml-cpp 变量为空，手动 fallback 到常见路径 (可选)
if("${yaml-cpp_LIBRARIES}" STREQUAL "")
    list(APPEND MY_LIBS /lib/x86_64-linux-gnu/libyaml-cpp.so)
endif()

# 6. 链接库
target_link_libraries(main ${MY_LIBS})

# 7. 包含目录
target_include_directories(main PRIVATE
    ${OPENCV_INCLUDE_DIRS}
    ${yaml-cpp_INCLUDE_DIRS}
    /usr/include/eigen3
    ${CMAKE_SOURCE_DIR}
)

# 8. 打印调试信息
message(STATUS "=== DEBUG INFO ===")
message(STATUS "OpenCV Libs: ${OPENCV_LIBRARIES}")
message(STATUS "yaml-cpp Libs: ${yaml-cpp_LIBRARIES}")
message(STATUS "Final Link Libs: ${MY_LIBS}")
message(STATUS "==================")
