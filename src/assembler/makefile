
# 直接生成全部bc的命令 ==================================================================================

# 源文件目录
SRC_DIR = ./self_tests/src_huawei
# 输出目录
OUT_DIR = ../../test/dfg/src

# 查找所有的源文件
SOURCES := $(wildcard $(SRC_DIR)/alg*.cpp)
# 将每个源文件路径转换为目标 .bc 文件路径
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(OUT_DIR)/%.bc,$(SOURCES))

# 默认目标
all: $(OBJECTS)

# 通用规则，用于从 .cpp 文件生成 .bc 文件
$(OUT_DIR)/%.bc: $(SRC_DIR)/%.cpp
	clang++ -emit-llvm -c $< $(CFLAGS) -o $@ -O3 -fno-vectorize -fno-slp-vectorize -fno-unroll-loops -m32


# 单独生成一个bc的命令 ==================================================================================

# CFLAGS = -I/usr/include/x86_64-linux-gnu -I/usr/include/x86_64-linux-gnu/c++/9 -I/usr/include/c++/9
# CFLAGS = -I/usr/include/x86_64-linux-gnu -I/usr/include/i386-linux-gnu -I/usr/include/x86_64-linux-gnu/c++/7 -I/usr/include/c++/7

## 生成bc的脚本
%.bc: ./self_tests/src_huawei/%.cpp
	clang++ -emit-llvm -c $< $(CFLAGS) -o '../../test/dfg/src/$@' -O3  -fno-vectorize -fno-slp-vectorize -fno-unroll-loops -m32 
#	clang++ -emit-llvm -c '$^' $(CFLAGS) -o '../../test/dfg/src/$@' -O3  -fno-vectorize -fno-slp-vectorize -fno-unroll-loops -m32
# $@ 为目标名称   @^ 先决条件  $<: 第一个先决条件的自动变量，对于模式规则来说，这表示与模式匹配的源文件。在这个规则中，它将代表匹配到的 %.cpp 文件。
# -Wall -Wextra


alg6_loop_0.dot alg6_loop_1.dot:dfg.out ./self_tests/src_huawei/alg6.cpp
	./dfg.out -o "alg6" ./self_tests/src_huawei/alg6.cpp
run_alg6: alg6_loop_0.dot alg6_loop_1.dot mapper.out
	./mapper.out -d alg6_loop_0.dot -l 5971968 -a alg6_loop_0.asm -s
	./mapper.out -d alg6_loop_1.dot -l 2985984 -a alg6_loop_1.asm -s


# Clean ==================================================================================
clean:
	-rm *.asm *.dot
	-rm $(OBJECTS)
	
