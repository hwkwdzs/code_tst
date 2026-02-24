import re

with open('detector.cpp', 'r') as f:
    content = f.read()

# 替换 1: 时间格式化 fmt::format("{:%Y-%m-%d...}", chrono...) -> 使用 strftime
# 这是一个特例，比较复杂，我们先用占位符，稍后手动处理或简单替换
# 这里我们直接用 sprintf 风格替代简单的字符串拼接

# 替换 2: 简单的字符串拼接 fmt::format("{}_{}", a, b) -> a + "_" + b
# 由于正则比较复杂，我们针对你报错的几行进行精准替换

# 针对报错行 348: 时间格式化
content = re.sub(
    r'fmt::format\("\{:%Y-%m-%d_%H-%M-%S\}", std::chrono::system_clock::now\(\)\)',
    '[]', # 暂时替换为空，或者用固定字符串，稍后我们写个函数
    content
)

# 针对报错行 349: 路径拼接
# fmt::format("{}/{}_{}.jpg", save_path_, ARMOR_NAMES[armor.name], file_name)
# 替换为: save_path_ + "/" + ARMOR_NAMES[armor.name] + "_" + file_name + ".jpg"
# 这个正则太难写，我们直接手动修改这几行更稳妥
print("检测到复杂替换，建议手动修改 detector.cpp 的以下几行")

with open('detector.cpp', 'w') as f:
    f.write(content)

print("初步替换完成，请检查")
