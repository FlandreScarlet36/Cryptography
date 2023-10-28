import subprocess  # 导入subprocess模块，用于执行外部命令
import random  # 导入random模块，用于生成随机数据

# 生成指定长度的随机二进制字符串
def generate_random_binary_string(length=16):
    return ''.join(random.choice('01') for _ in range(length))

executable_file_path = "./SPN.exe"  # 定义外部可执行文件的路径
num_pairs = 16000  # 定义要生成的数据对数

# 打开文件以写入生成的数据对，"pairs.txt"是文件名
with open("./data/pairs.txt", "w") as file:
    for _ in range(num_pairs):  # 生成指定数量的数据对
        input_data = generate_random_binary_string()  # 生成随机的输入数据

        # 运行外部可执行文件并将输入数据传递给它
        result = subprocess.run([executable_file_path], input=input_data.encode(), stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        output_data = result.stdout.decode().strip()  # 获取外部命令的标准输出

        # 将生成的输入数据和外部命令的输出数据写入文件
        file.write(input_data + "\n")
        file.write(output_data + "\n")
