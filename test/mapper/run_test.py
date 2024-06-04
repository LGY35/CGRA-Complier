import os
from termcolor import colored

# Set current working directory to directory of this Python file
os.chdir(os.path.dirname(os.path.abspath(__file__)))

input_dir = "./bench"
output_dir = "./output"
if not os.path.exists(output_dir):
    os.mkdir(output_dir)

failed_times = 0

# 遍历文件夹
for srcname in os.listdir("./src"):
    # 打开文件并读取第一行
    with open(os.path.join("./src", srcname), 'r') as f:
        first_line = f.readline().strip()

    # 检查该行是否以 "//" 开头
    if first_line.startswith('//'):
        # 删除 "//" 并保存剩余的部分
        command = first_line[2:].strip()

        # 在 shell 中执行该行
        if os.system(command) != 0:
            failed_times += 1
            print("FAILED")

# compare all the .asm files under input_dir and output_dir, and check if they are the same
for filename in os.listdir(input_dir):
    # for .asm files, compare
    if filename.endswith(".asm"):
        with open(os.path.join(input_dir, filename), "r") as f:
            input_asm = f.read()
        with open(os.path.join(output_dir, filename), "r") as f:
            output_asm = f.read()
        if input_asm == output_asm:
            print(f"{filename}: PASSED")
        else:
            print(colored(f"{filename}: FAILED", "red"))
            failed_times += 1
    # for .map files, compare the lines after "tot time:"
    if filename.endswith(".map"):
        with open(os.path.join(input_dir, filename), "r") as f:
            for line in f:
                if line.startswith("tot time:"):
                    input_map = f.readlines()  # Read all lines after "tot time:"
                    break
        with open(os.path.join(output_dir, filename), "r") as f:
            for line in f:
                if line.startswith("tot time:"):
                    output_map = f.readlines()  # Read all lines after "tot time:"
                    break
        if input_map == output_map:
            print(f"{filename}.map: PASSED")
        else:
            print(colored(f"{filename}.map: FAILED", "red"))
            failed_times += 1

if failed_times > 0:
    exit(1)