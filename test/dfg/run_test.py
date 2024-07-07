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


# import os
# import subprocess

# # Set current working directory to directory of this Python file
# os.chdir(os.path.dirname(os.path.abspath(__file__)))

# input_dir = "./bench"
# output_dir = "./output"
# log_dir = "./logs"

# if not os.path.exists(output_dir):
#     os.makedirs(output_dir)

# if not os.path.exists(log_dir):
#     os.makedirs(log_dir)

# failed_times = 0

# # Generate DFG and log results
# for srcname in os.listdir("./src"):
#     if srcname.endswith(".bc"):
#         print_name = os.path.splitext(srcname)[0]
#         output_path = os.path.join(output_dir, print_name)
#         src_path = os.path.join("./src", srcname)
#         log_file_path = os.path.join(log_dir, print_name + ".log")
        
#         with open(log_file_path, 'w') as log_file:
#             print(f"Processing: {src_path}")
#             # Build command
#             command = f"../../src/dfg/dfg.out -o \"{output_path}\" {src_path}"
#             print("Running command:", command)
#             # Execute command
#             result = subprocess.run(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, universal_newlines=True)
            
#             # Log output and errors
#             log_file.write(f"Output:\n{result.stdout}\n")
#             log_file.write(f"Errors:\n{result.stderr}\n")
            
#             if result.returncode != 0:
#                 failed_times += 1
#                 print(f"FAILED processing {srcname}, check log {log_file_path}")
#             else:
#                 print(f"{srcname}: PASSED")

# # Check outputs
# for filename in os.listdir(input_dir):
#     try:
#         with open(os.path.join(input_dir, filename), "r") as f:
#             input_dot = f.read()
#         with open(os.path.join(output_dir, filename), "r") as f:
#             output_dot = f.read()
#         if input_dot == output_dot:
#             print(f"{filename}: PASSED")
#         else:
#             print(colored(f"{filename}: FAILED", "red"))
#     except Exception as e:
#         print(colored(f"Error processing {filename}: {str(e)}", "red"))

# if failed_times > 0:
#     print("Some tests failed.")
#     exit(1)
