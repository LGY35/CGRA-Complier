import os
from termcolor import colored

# Set current working directory to directory of this Python file
os.chdir(os.path.dirname(os.path.abspath(__file__)))

input_dir = "./bench"
output_dir = "./output"
if not os.path.exists(output_dir):
    os.mkdir(output_dir)

failed_times = 0

# Generate DFG
for srcname in os.listdir("./src"):
    if srcname.endswith(".bc"):
        print_name = os.path.splitext(srcname)[0]
        print("../../src/dfg/dfg.out -o \"" + output_dir + "/" + print_name + "\" ./src/" + srcname)
        if os.system("../../src/dfg/dfg.out -o \"" + output_dir + "/" + print_name + "\" ./src/" + srcname) != 0:
            failed_times += 1
            print("FAILED")


for filename in os.listdir(input_dir):
    # compare dot files under input_dir and output_dir
    with open(os.path.join(input_dir, filename), "r") as f:
        input_dot = f.read()
    with open(os.path.join(output_dir, filename), "r") as f:
        output_dot = f.read()
    if input_dot == output_dot:
        print(f"{filename}: PASSED")
    else:
        print(colored(f"{filename}: FAILED", "red"))

if failed_times > 0:
    exit(1)