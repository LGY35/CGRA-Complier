# **CGRA Compiler**

把benchmark生成.bc，然后放在test里面的test/dfg/src下，根据这个bc文件，以及dfg模块生成的可执行文件dfg.out，将bc文件转换成dfg图，这个output会被放在test/dfg/output里面。然后test/dfg/output会和test/dfg/bench对比，校验功能是否正确。



## 未解决的问题：

1.链接：编译dfg.out时的链接问题：现在链接了下面这么多没用到的文件，实际上很多都没有用

>  -L/home/luguangyang/clang+llvm-15.0.5-x86_64-linux-gnu-ubuntu-18.04/lib/ -lLLVMWindowsManifest -lLLVMWindowsDriver -lLLVMXRay -lLLVMLibDriver -lLLVMDlltoolDriver -lLLVMCoverage -lLLVMLineEditor -lLLVMXCoreDisassembler -lLLVMXCoreCodeGen -lLLVMXCoreDesc -lLLVMXCoreInfo -lLLVMX86TargetMCA -lLLVMX86Disassembler -lLLVMX86AsmParser -lLLVMX86CodeGen -lLLVMX86Desc -lLLVMX86Info -lLLVMWebAssemblyDisassembler -lLLVMWebAssemblyAsmParser -lLLVMWebAssemblyCodeGen -lLLVMWebAssemblyDesc -lLLVMWebAssemblyUtils -lLLVMWebAssemblyInfo -lLLVMVEDisassembler -lLLVMVEAsmParser -lLLVMVECodeGen -lLLVMVEDesc -lLLVMVEInfo -lLLVMSystemZDisassembler -lLLVMSystemZAsmParser -lLLVMSystemZCodeGen -lLLVMSystemZDesc -lLLVMSystemZInfo -lLLVMSparcDisassembler -lLLVMSparcAsmParser -lLLVMSparcCodeGen -lLLVMSparcDesc -lLLVMSparcInfo -lLLVMRISCVDisassembler -lLLVMRISCVAsmParser -lLLVMRISCVCodeGen -lLLVMRISCVDesc -lLLVMRISCVInfo -lLLVMPowerPCDisassembler -lLLVMPowerPCAsmParser -lLLVMPowerPCCodeGen -lLLVMPowerPCDesc -lLLVMPowerPCInfo -lLLVMNVPTXCodeGen -lLLVMNVPTXDesc -lLLVMNVPTXInfo -lLLVMMSP430Disassembler -lLLVMMSP430AsmParser -lLLVMMSP430CodeGen -lLLVMMSP430Desc -lLLVMMSP430Info -lLLVMMipsDisassembler -lLLVMMipsAsmParser -lLLVMMipsCodeGen -lLLVMMipsDesc -lLLVMMipsInfo -lLLVMLanaiDisassembler -lLLVMLanaiCodeGen -lLLVMLanaiAsmParser -lLLVMLanaiDesc -lLLVMLanaiInfo -lLLVMHexagonDisassembler -lLLVMHexagonCodeGen -lLLVMHexagonAsmParser -lLLVMHexagonDesc -lLLVMHexagonInfo -lLLVMBPFDisassembler -lLLVMBPFAsmParser -lLLVMBPFCodeGen -lLLVMBPFDesc -lLLVMBPFInfo -lLLVMAVRDisassembler -lLLVMAVRAsmParser -lLLVMAVRCodeGen -lLLVMAVRDesc -lLLVMAVRInfo -lLLVMARMDisassembler -lLLVMARMAsmParser -lLLVMARMCodeGen -lLLVMARMDesc -lLLVMARMUtils -lLLVMARMInfo -lLLVMAMDGPUTargetMCA -lLLVMAMDGPUDisassembler -lLLVMAMDGPUAsmParser -lLLVMAMDGPUCodeGen -lLLVMAMDGPUDesc -lLLVMAMDGPUUtils -lLLVMAMDGPUInfo -lLLVMAArch64Disassembler -lLLVMAArch64AsmParser -lLLVMAArch64CodeGen -lLLVMAArch64Desc -lLLVMAArch64Utils -lLLVMAArch64Info -lLLVMOrcJIT -lLLVMMCJIT -lLLVMJITLink -lLLVMInterpreter -lLLVMExecutionEngine -lLLVMRuntimeDyld -lLLVMOrcTargetProcess -lLLVMOrcShared -lLLVMDWP -lLLVMDebugInfoGSYM -lLLVMOption -lLLVMObjectYAML -lLLVMObjCopy -lLLVMMCA -lLLVMMCDisassembler -lLLVMLTO -lLLVMCFGuard -lLLVMFrontendOpenACC -lLLVMExtensions -lPolly -lPollyISL -lLLVMPasses -lLLVMObjCARCOpts -lLLVMCoroutines -lLLVMipo -lLLVMInstrumentation -lLLVMVectorize -lLLVMLinker -lLLVMFrontendOpenMP -lLLVMDWARFLinker -lLLVMGlobalISel -lLLVMMIRParser -lLLVMAsmPrinter -lLLVMSelectionDAG -lLLVMCodeGen -lLLVMIRReader -lLLVMAsmParser -lLLVMInterfaceStub -lLLVMFileCheck -lLLVMFuzzMutate -lLLVMTarget -lLLVMScalarOpts -lLLVMInstCombine -lLLVMAggressiveInstCombine -lLLVMTransformUtils -lLLVMBitWriter -lLLVMAnalysis -lLLVMProfileData -lLLVMSymbolize -lLLVMDebugInfoPDB -lLLVMDebugInfoMSF -lLLVMDebugInfoDWARF -lLLVMObject -lLLVMTextAPI -lLLVMMCParser -lLLVMMC -lLLVMDebugInfoCodeView -lLLVMBitReader -lLLVMFuzzerCLI -lLLVMCore -lLLVMRemarks -lLLVMBitstreamReader -lLLVMBinaryFormat -lLLVMTableGen -lLLVMSupport -lLLVMDemangle

2.警告：编译dfg.out时的两个警告

> ```
> /usr/bin/ld: warning: /usr/lib/gcc/x86_64-linux-gnu/7/libstdc++.so: unsupported GNU_PROPERTY_TYPE (5) type: 0xc0010001
> /usr/bin/ld: warning: /usr/lib/gcc/x86_64-linux-gnu/7/libstdc++.so: unsupported GNU_PROPERTY_TYPE (5) type: 0xc0010002
> ```
>
> 



# Benchmark优化

## 任务

benchmark的问题

* 循环嵌套

* 循环里面有函数

* 循环节点太多

一个取余数，一个取取余之外的且不等于0

要求：

> 60个节点以内
>
> 100个的可能跑不完
>
> 1分钟



## .bc文件生成

运行这个`CGRA/src/assembler/makefile`，benchmark都在`/CGRA/src/assembler/self_tests`下。

目前的makefile只是针对alg7生成bc，如果需要生成别的，需要改好几个数字，把alg7换成algx，后续进行更新。==此makefile待优化==

```
CFLAGS = -I/usr/include/x86_64-linux-gnu -I/usr/include/i386-linux-gnu -I/usr/include/x86_64-linux-gnu/c++/7 -I/usr/include/c++/7

alg7.bc: ./self_tests/src_huawei/alg7.cpp
	clang -emit-llvm -c './self_tests/src_huawei/alg7.cpp' $(CFLAGS) -o '../../test/dfg/src/alg7.bc' -O3  -fno-vectorize -fno-slp-vectorize -fno-unroll-loops -m32

```

* 问题：这里的include头文件都是g++的，这里include的路径都是usr下的，而llvm放在了home下。

  * 解答：**在环境变量PATH里面已经设置了**，所以可以调用（因为**用的clang**，所以直接就去了llvm路径下调用）。

    ```
    which clang
    /home/luguangyang/clang+llvm-15.0.5-x86_64-linux-gnu-ubuntu-18.04/bin/clang
    ```

  ​        可以看到，这里是正确调用了，所以是可以生成llvm的bc



## 代码优化

### alg5.cpp

源代码为两层的for循环，分别使用row-index和col-index

```c++
for(int RowIdx=0; RowIdx<ALG5_HEIGHT; RowIdx++) {
        for(int ColIdx=0; ColIdx<ALG5_WIDTH; ColIdx++) {
            int RowPos = RowIdx / 2;
            int ColPos = ColIdx / 2;
           
```

将其拆分为一个for循环，使用一个 i 变量，

```c++
for (int i = 0; i < ALG5_HEIGHT * ALG5_WIDTH; i++) {
        if (i % ALG5_WIDTH == 0) {
            RowIdx++; // CGRA 无法使用除法
        }
        int ColIdx = i % ALG5_WIDTH;
        int RowPos = RowIdx / 2;
        int ColPos = ColIdx / 2;
```

如果拆完之后的一个for循环太大，可以将内部的操作进一步拆分到几个for循环中。详见alg6.cpp的例子

<u>**这种优化方法的主要目的是通过分离计算步骤来减少每次循环迭代中的复杂度，从而提高编译器的优化效果。**</u>

* **减少每次循环的复杂度**：
  - 原始代码在一个循环中执行所有计算步骤，包含提取数据、线性变换、调整数据和剪裁数据。这样每次循环迭代的复杂度较高，增加了编译器优化的难度。
  - 优化后的代码将这些操作分解为多个循环，每个循环只执行一部分计算。这样每次循环迭代的复杂度降低，编译器可以更好地进行优化。
* **提高数据局部性**：
  - 在原始代码中，数据的读取和写入分布在每次迭代中，可能导致数据局部性较差。
  - 优化后的代码在每个循环中处理不同的通道数据，提高了数据局部性，减少了缓存失效的可能性。
* **利用编译器优化**：
  - 分离计算步骤后，每个循环的逻辑更为简单，编译器可以更容易地识别和应用优化技术，如循环展开、指令并行等。





### alg6.cpp

```c++
ext_d3[0] = (in_d2[0] * tran_mat[0] + in_d2[1] * tran_mat[1] + in_d2[2] * tran_mat[2]+64) >> 7;//最后的结果除以128，其中加上64实现对结果的四舍五入
```



拆分循环：

基本的两层for循环的拆分思路与之前一样。

这里还有一些调优，是把大的for循环继续拆分：比如下面这个，一个for循环内部就计算了3个/4个最终量

```c++
for (int i = 0; i < iHeight * iWidth; i++)
	{
		if (i % iWidth == 0 && i != 0) {	
            y++;
        }
        x = i % iWidth;

        int in_d2[3];         
        int ext_d3[3];         
		// 逻辑是从 d2_in 中提取三通道数据，通过一个转换矩阵 tran_mat 进行线性变换，生成新的 d3_1、d3_2 和 d3_3 数据。
        in_d2[0] = d2_in[y][x][0];	//这里是每个通道下，逐像素处理，所以这里还是需要放在循环体内
        in_d2[1] = d2_in[y][x][1];
        in_d2[2] = d2_in[y][x][2];
		// 线性变换
        ext_d3[0] = (in_d2[0] * tran_mat[0] + in_d2[1] * tran_mat[1] + in_d2[2] * tran_mat[2]+64) >> 7;//最后的结果除以128，其中加上64实现对结果的四舍五入
        ext_d3[1] = (in_d2[0] * tran_mat[3] + in_d2[1] * tran_mat[4] + in_d2[2] * tran_mat[5]+64) >> 7;//应该是因为tran mat的大小限制在128内
        ext_d3[2] = (in_d2[0] * tran_mat[6] + in_d2[1] * tran_mat[7] + in_d2[2] * tran_mat[8]+64) >> 7;
        // 数据调整
		ext_d3[0] = ext_d3[0];   // 
        ext_d3[1] = ext_d3[1] + (128 << 2);     // (128 << 2) 等价于 128 * 2^2，也就是 128 * 4，结果是 512。
        ext_d3[2] = ext_d3[2] + (128 << 2);     // （1）增加偏移量可以将数据调整到一个适合的范围。例如，如果转换后的数据需要在一个非负的范围内，增加一个常数偏移量可以确保数据不会出现负值。（2）在某些颜色空间转换（例如 RGB 转 YCbCr 或者类似的颜色空间转换）中，转换后的某些通道需要增加一个偏移量，以确保其值在某个范围内。例如，在 YCbCr 颜色空间中，Cr 和 Cb 通常会有一个偏移量，使其中心值在中间，而不是在 0。
        // 数据剪裁
		d3_1[iWidth*y + x] = clip_bits(ext_d3[0], 0, 1023);
        d4_dst[iWidth*y + x] = d3_1[iWidth*y + x];	//用于存储中间处理结果的数组。但在当前的代码片段中没有看到 d4_dst 的进一步使用
        d3_2[iWidth*y + x] = clip_bits(ext_d3[1], 0, 1023);
        d3_3[iWidth*y + x] = clip_bits(ext_d3[2], 0, 1023);
	}
```

那么对其进行拆分：d3_1和d4_dst在一个for循环中，d3_2和d3_3各一个for循环

```c++
	int iHeight = ALG6_HEIGHT;
	int iWidth = ALG6_WIDTH;
	int tran_mat[9] = { 38,75,15,-22,-42,64,64,-54,-10 };
    int x = 0, y = 0;
	for (int i = 0; i < iHeight * iWidth; i++)
	{
		if (i % iWidth == 0 && i != 0) {
            y++;
        }
        x = i % iWidth;

        int in_d2[3];         
        int ext_d3[3];         
        in_d2[0] = d2_in[y][x][0];
        in_d2[1] = d2_in[y][x][1];
        in_d2[2] = d2_in[y][x][2];
        ext_d3[0] = (in_d2[0] * tran_mat[0] + in_d2[1] * tran_mat[1] + in_d2[2] * tran_mat[2]+64) >> 7;
        d3_1[iWidth*y + x] = clip_bits(ext_d3[0], 0, 1023);
        d4_dst[iWidth*y + x] = d3_1[iWidth*y + x];
	}
    x = 0, y = 0;
	for (int i = 0; i < iHeight * iWidth; i++)
	{
		if (i % iWidth == 0 && i != 0) {
            y++;
        }
        x = i % iWidth;

        int in_d2[3];         
        int ext_d3[3];         
        in_d2[0] = d2_in[y][x][0];
        in_d2[1] = d2_in[y][x][1];
        in_d2[2] = d2_in[y][x][2];
        ext_d3[1] = (in_d2[0] * tran_mat[3] + in_d2[1] * tran_mat[4] + in_d2[2] * tran_mat[5]+64) >> 7;
        ext_d3[1] = ext_d3[1] + (128 << 2);
        d3_2[iWidth*y + x] = clip_bits(ext_d3[1], 0, 1023);
	}
    x = 0, y = 0;
	for (int i = 0; i < iHeight * iWidth; i++)
	{
		if (i % iWidth == 0 && i != 0) {
            y++;
        }
        x = i % iWidth;

        int in_d2[3];         
        int ext_d3[3];         
        in_d2[0] = d2_in[y][x][0];
        in_d2[1] = d2_in[y][x][1];
        in_d2[2] = d2_in[y][x][2];
        ext_d3[2] = (in_d2[0] * tran_mat[6] + in_d2[1] * tran_mat[7] + in_d2[2] * tran_mat[8]+64) >> 7;
        ext_d3[2] = ext_d3[2] + (128 << 2);     // 
        d3_3[iWidth*y + x] = clip_bits(ext_d3[2], 0, 1023);
	}
```









# 环境配置



`fatal error: graphviz/gvc.h: No such file or directory`

```
sudo apt-get install libgraphviz-dev
```

## LLVM：使用预编译包安装：

官方github[llvm/llvm-project: The LLVM Project is a collection of modular and reusable compiler and toolchain technologies. (github.com)](https://github.com/llvm/llvm-project)

[LLVM Download Page](https://releases.llvm.org/download.html)（更新：下载15.0.5中的x86_64_ubuntu18.04版本）

所有LLVM版本的下载列表, 从左到右，各列分别对应版本的发布时间、版本号、下载链接、发布说明(包含一些更新的信息)、开发文档[Download LLVM releases](https://releases.llvm.org/)

[第1章 编译和安装LLVM — Getting Started with LLVM Core Libraries 文档 (getting-started-with-llvm-core-libraries-zh-cn.readthedocs.io)](https://getting-started-with-llvm-core-libraries-zh-cn.readthedocs.io/zh-cn/latest/ch01.html#id2)

[一份关于各种安装LLVM的方法的总结_llvm官网-CSDN博客](https://blog.csdn.net/chikey/article/details/85004556)

[LLVM_Ubuntu安装_ubuntu llvm-CSDN博客](https://blog.csdn.net/qq_32460819/article/details/108449344)

` fatal error: llvm/Analysis/LoopInfo.h: No such file or directory`

> 系统信息：Ubuntu 18.04.6 LTS
>
> ```
> (base) luguangyang@GPUserver230:~/CGRA$ lsb_release -a
> No LSB modules are available.
> Distributor ID: Ubuntu
> Description:    Ubuntu 18.04.6 LTS
> Release:        18.04
> Codename:       bionic
> ```
>
> 



配置环境变量：[Linux添加环境变量-CSDN博客](https://blog.csdn.net/weixin_37825371/article/details/90752386)

```
export LLVM_HOME=/home/luguangyang/clang+llvm-15.0.5-x86_64-linux-gnu-ubuntu-18.04/bin
export PATH=$LLVM_HOME:$PATH
```

> ```
> 当前用户：
> vim ~/.bashrc
> source ~/.bashrc
> 
> 全局：
> sudo vim /etc/profile
> 
> 查看环境变量：
> echo $PATH
> ```
>
> 



## 报错问题与修改

### 报错1：头文件找不到——修改makefile

> ```
> g++ -m64 -g -I/home/luguangyang/clang+llvm-10.0.0-x86_64-linux-gnu-ubuntu-18.04/include/llvm/  -c output.cpp -o output.o
> In file included from output.h:1:0,
>               from output.cpp:1:
> utils.h:7:10: fatal error: llvm/IR/Constants.h: No such file or directory
> #include "llvm/IR/Constants.h"
>        ^~~~~~~~~~~~~~~~~~~~~
> compilation terminated.
> makefile:30: recipe for target 'output.o' failed
> make: *** [output.o] Error 1
> ```
>
> 编译器找不到 `llvm/IR/Constants.h` 文件。
>
> 已经将 LLVM 的包含路径设置为 `~/clang+llvm-10.0.0-x86_64-linux-gnu-ubuntu-18.04/include/llvm/`，这可能导致编译器在 `llvm` 目录下查找 `llvm/IR/Constants.h`，实际上这个文件路径应该是 `~/clang+llvm-10.0.0-x86_64-linux-gnu-ubuntu-18.04/include`。
>
> 所以makefile为：
>
> ```
> # Variable ===============================================================================
> PHONY =
> MODE = DEBUG
> HOSTNAME = $(shell hostname)
> 
> LLVM_INCLUDE_PATH = $(HOME)/clang+llvm-10.0.0-x86_64-linux-gnu-ubuntu-18.04/include
> LLVM_LIB_PATH = $(HOME)/clang+llvm-10.0.0-x86_64-linux-gnu-ubuntu-18.04/lib
> 
> ifeq ($(MODE), DEBUG)
> ifeq ($(HOSTNAME), shore-82wm)
> CFLAGS = -m64 -g -I$(LLVM_INCLUDE_PATH) 
> LDFLAGS = -L$(LLVM_LIB_PATH) -lLLVM
> else
> CFLAGS = -m64 -g -I$(LLVM_INCLUDE_PATH)  	
> LDFLAGS = -L$(LLVM_LIB_PATH) -lLLVM 	#-lLLVM-15
> endif
> else
> ifeq ($(HOSTNAME), shore-82wm)
> CFLAGS = -m64 -Ofast -I$(LLVM_INCLUDE_PATH) 
> LDFLAGS = -L$(LLVM_LIB_PATH) -lLLVM
> else
> CFLAGS = -m64 -Ofast -I$(LLVM_INCLUDE_PATH) 
> LDFLAGS = -L$(LLVM_LIB_PATH) -lLLVM 	#-lLLVM-15
> endif
> endif
> 
> # build ==================================================================================
> output.o: output.h output.cpp utils.h
> 	g++ $(CFLAGS) -c output.cpp -o output.o
> passes.o: passes.h passes.cpp utils.h
> 	g++ $(CFLAGS) -c passes.cpp -o passes.o
> spec_i.o: spec_i.h spec_i.cpp utils.h
> 	g++ $(CFLAGS) -c spec_i.cpp -o spec_i.o
> utils.o: utils.h utils.cpp
> 	g++ $(CFLAGS) -c utils.cpp -o utils.o
> visitor.o: visitor.h visitor.cpp utils.h
> 	g++ $(CFLAGS) -c visitor.cpp -o visitor.o
> main.o: main.cpp utils.h output.h passes.h spec_i.h visitor.h
> 	g++ $(CFLAGS) -c ./main.cpp -o main.o
> dfg.out:output.o passes.o spec_i.o utils.o visitor.o main.o
> 	g++ $^ $(LDFLAGS) -o dfg.out
> 
> # Clean ==================================================================================
> clean:
> 	rm -rf *.o *.out
> 
> PHONY += clean
> ```
>
> 

### 报错2：set没有找到

> ```
> g++ -m64 -g -I/home/luguangyang/clang+llvm-10.0.0-x86_64-linux-gnu-ubuntu-18.04/include          -c output.cpp -o output.o
> In file included from output.h:1:0,
>               from output.cpp:1:
> utils.h:97:13: error: ‘set’ in namespace ‘std’ does not name a template type
> extern std::set<llvm::BasicBlock*> un_condi_BB;
>           ^~~
> makefile:29: recipe for target 'output.o' failed
> make: *** [output.o] Error 1
> ```
>
> 增加 #include<set>

### 报错3：itostr没有定义

> 把itostr换成 std::to_string

### 报错4：getTopLevelLoops()找不到——LLVM版本修改（15.0.0）

[Release LLVM 15.0.5 · llvm/llvm-project (github.com)](https://github.com/llvm/llvm-project/releases/tag/llvmorg-15.0.5)

下载[clang+llvm-15.0.5-x86_64-linux-gnu-ubuntu-18.04.tar.xz](https://github.com/llvm/llvm-project/releases/download/llvmorg-15.0.5/clang+llvm-15.0.5-x86_64-linux-gnu-ubuntu-18.04.tar.xz)

> Ubuntu系统，应该下载x86_64架构的版本`clang+llvm-15.0.5-x86_64-linux-gnu-ubuntu-18.04.tar.xz`。15.0的好几个版本，找到15.0.5才有支持ubuntu的

> ```
> ./main.cpp: In function ‘int main(int, char**)’:
> ./main.cpp:50:34: error: ‘class llvm::LoopInfoBase<llvm::BasicBlock, llvm::Loop>’ has no member named ‘getTopLevelLoops’; did you mean ‘TopLevelLoops’?
>           loop_cnt = LoopInfo->getTopLevelLoops().size() - 1;
>                                ^~~~~~~~~~~~~~~~
>                                TopLevelLoops
> ./main.cpp:52:38: error: ‘class llvm::LoopInfoBase<llvm::BasicBlock, llvm::Loop>’ has no member named ‘getTopLevelLoops’; did you mean ‘TopLevelLoops’?
>           for (Loop *L : LoopInfo->getTopLevelLoops()) {      //对于LLVM IR，提取Loop
>                                    ^~~~~~~~~~~~~~~~
>                                    TopLevelLoops
> ```
>
> ![image-20240604173034883](C:\Users\LGY\AppData\Roaming\Typora\typora-user-images\image-20240604173034883.png)
>
> 就是说，还是没有正确包含llvm的头文件。
>
> 使用的10.0的版本太低，更换为15.0之后不再出错



### 报错4：链接出错/usr/bin/ld: cannot find -lllvm

使用 `llvm-config` 工具来获取正确的编译和链接选项：

```
/home/luguangyang/clang+llvm-15.0.5-x86_64-linux-gnu-ubuntu-18.04/bin/llvm-config --libs
```

> 输出：
>
> ```
> -lLLVMWindowsManifest -lLLVMWindowsDriver -lLLVMXRay -lLLVMLibDriver -lLLVMDlltoolDriver -lLLVMCoverage -lLLVMLineEditor -lLLVMXCoreDisassembler -lLLVMXCoreCodeGen -lLLVMXCoreDesc -lLLVMXCoreInfo -lLLVMX86TargetMCA -lLLVMX86Disassembler -lLLVMX86AsmParser -lLLVMX86CodeGen -lLLVMX86Desc -lLLVMX86Info -lLLVMWebAssemblyDisassembler -lLLVMWebAssemblyAsmParser -lLLVMWebAssemblyCodeGen -lLLVMWebAssemblyDesc -lLLVMWebAssemblyUtils -lLLVMWebAssemblyInfo -lLLVMVEDisassembler -lLLVMVEAsmParser -lLLVMVECodeGen -lLLVMVEDesc -lLLVMVEInfo -lLLVMSystemZDisassembler -lLLVMSystemZAsmParser -lLLVMSystemZCodeGen -lLLVMSystemZDesc -lLLVMSystemZInfo -lLLVMSparcDisassembler -lLLVMSparcAsmParser -lLLVMSparcCodeGen -lLLVMSparcDesc -lLLVMSparcInfo -lLLVMRISCVDisassembler -lLLVMRISCVAsmParser -lLLVMRISCVCodeGen -lLLVMRISCVDesc -lLLVMRISCVInfo -lLLVMPowerPCDisassembler -lLLVMPowerPCAsmParser -lLLVMPowerPCCodeGen -lLLVMPowerPCDesc -lLLVMPowerPCInfo -lLLVMNVPTXCodeGen -lLLVMNVPTXDesc -lLLVMNVPTXInfo -lLLVMMSP430Disassembler -lLLVMMSP430AsmParser -lLLVMMSP430CodeGen -lLLVMMSP430Desc -lLLVMMSP430Info -lLLVMMipsDisassembler -lLLVMMipsAsmParser -lLLVMMipsCodeGen -lLLVMMipsDesc -lLLVMMipsInfo -lLLVMLanaiDisassembler -lLLVMLanaiCodeGen -lLLVMLanaiAsmParser -lLLVMLanaiDesc -lLLVMLanaiInfo -lLLVMHexagonDisassembler -lLLVMHexagonCodeGen -lLLVMHexagonAsmParser -lLLVMHexagonDesc -lLLVMHexagonInfo -lLLVMBPFDisassembler -lLLVMBPFAsmParser -lLLVMBPFCodeGen -lLLVMBPFDesc -lLLVMBPFInfo -lLLVMAVRDisassembler -lLLVMAVRAsmParser -lLLVMAVRCodeGen -lLLVMAVRDesc -lLLVMAVRInfo -lLLVMARMDisassembler -lLLVMARMAsmParser -lLLVMARMCodeGen -lLLVMARMDesc -lLLVMARMUtils -lLLVMARMInfo -lLLVMAMDGPUTargetMCA -lLLVMAMDGPUDisassembler -lLLVMAMDGPUAsmParser -lLLVMAMDGPUCodeGen -lLLVMAMDGPUDesc -lLLVMAMDGPUUtils -lLLVMAMDGPUInfo -lLLVMAArch64Disassembler -lLLVMAArch64AsmParser -lLLVMAArch64CodeGen -lLLVMAArch64Desc -lLLVMAArch64Utils -lLLVMAArch64Info -lLLVMOrcJIT -lLLVMMCJIT -lLLVMJITLink -lLLVMInterpreter -lLLVMExecutionEngine -lLLVMRuntimeDyld -lLLVMOrcTargetProcess -lLLVMOrcShared -lLLVMDWP -lLLVMDebugInfoGSYM -lLLVMOption -lLLVMObjectYAML -lLLVMObjCopy -lLLVMMCA -lLLVMMCDisassembler -lLLVMLTO -lLLVMCFGuard -lLLVMFrontendOpenACC -lLLVMExtensions -lPolly -lPollyISL -lLLVMPasses -lLLVMObjCARCOpts -lLLVMCoroutines -lLLVMipo -lLLVMInstrumentation -lLLVMVectorize -lLLVMLinker -lLLVMFrontendOpenMP -lLLVMDWARFLinker -lLLVMGlobalISel -lLLVMMIRParser -lLLVMAsmPrinter -lLLVMSelectionDAG -lLLVMCodeGen -lLLVMIRReader -lLLVMAsmParser -lLLVMInterfaceStub -lLLVMFileCheck -lLLVMFuzzMutate -lLLVMTarget -lLLVMScalarOpts -lLLVMInstCombine -lLLVMAggressiveInstCombine -lLLVMTransformUtils -lLLVMBitWriter -lLLVMAnalysis -lLLVMProfileData -lLLVMSymbolize -lLLVMDebugInfoPDB -lLLVMDebugInfoMSF -lLLVMDebugInfoDWARF -lLLVMObject -lLLVMTextAPI -lLLVMMCParser -lLLVMMC -lLLVMDebugInfoCodeView -lLLVMBitReader -lLLVMFuzzerCLI -lLLVMCore -lLLVMRemarks -lLLVMBitstreamReader -lLLVMBinaryFormat -lLLVMTableGen -lLLVMSupport -lLLVMDemangle
> ```
>
> 

#### **修改环境变量，更新LD_LIBRARY_PATH**:	在bashrc中加入语句：

```
export LD_LIBRARY_PATH=$HOME/clang+llvm-15.0.5-x86_64-linux-gnu-ubuntu-18.04/lib:$LD_LIBRARY_PATH
```



#### 使用 /etc/ld.so.conf 配置文件

```
sudo echo '/home/luguangyang/clang+llvm-15.0.5-x86_64-linux-gnu-ubuntu-18.04/lib/' >> /etc/ld.so.conf
```

> 要将 `$HOME/clang+llvm-15.0.5-x86_64-linux-gnu-ubuntu-18.04/lib/` 添加到 `ld.so.conf` 中，您可以按以下步骤进行：
>
> 1. **编辑 `ld.so.conf` 或创建一个新的配置文件**： 您可以直接编辑 `/etc/ld.so.conf` 文件，或者更推荐的是在 `/etc/ld.so.conf.d/` 目录下创建一个新的配置文件，以便更容易管理。
>
> 2. **创建一个新的配置文件**： 例如，您可以创建一个名为 `llvm.conf` 的新文件：
>
>    ```
>    sh
>    复制代码
>    sudo nano /etc/ld.so.conf.d/llvm.conf
>    ```
>
> 3. **在文件中添加新的库路径**： 在打开的文件中，添加以下内容：
>
>    ```
>    bash
>    复制代码
>    /home/luguangyang/clang+llvm-15.0.5-x86_64-linux-gnu-ubuntu-18.04/lib/
>    ```
>
>    确保路径中的 `$HOME` 被替换为实际的用户目录路径（例如 `/home/luguangyang/`）。
>
> 4. **保存并关闭文件**： 保存文件并退出编辑器。
>
> 5. **更新动态链接器缓存**： 运行以下命令以更新动态链接器缓存，使新路径生效：
>
>    ```
>    sh
>    复制代码
>    sudo ldconfig
>    ```
>
> 完成上述步骤后，您的系统将能够找到在新路径中的库文件。

**检查GCC版本兼容性**: 错误信息中提到 `/usr/lib/gcc/x86_64-linux-gnu/7/libstdc++.so` 的警告，确认您的GCC版本与LLVM版本兼容。



### 报错5：

使用llvm

```
/usr/bin/ld: warning: /usr/lib/gcc/x86_64-linux-gnu/7/libstdc++.so: unsupported GNU_PROPERTY_TYPE (5) type: 0xc0010001
/usr/bin/ld: warning: /usr/lib/gcc/x86_64-linux-gnu/7/libstdc++.so: unsupported GNU_PROPERTY_TYPE (5) type: 0xc0010002
main.o:(.data.rel.ro._ZTIN4llvm2cl15OptionValueCopyINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEEE[_ZTIN4llvm2cl15OptionValueCopyINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEEE]+0x10): undefined reference to `typeinfo for llvm::cl::GenericOptionValue'
collect2: error: ld returned 1 exit status
makefile:57: recipe for target 'dfg.out' failed
make: *** [dfg.out] Error 1
```

关键错误是：`(.data.rel.ro._ZTIN4llvm2cl15OptionValueCopyINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEEE[_ZTIN4llvm2cl15OptionValueCopyINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEEE]+0x10): undefined reference to `typeinfo for llvm::cl::GenericOptionValue'`

查找之后发现:[编译选项导致的 undefined reference to `typeinfo XXX`_cmake出现fno-rtti-CSDN博客](https://blog.csdn.net/qq_51470638/article/details/128978453)现在的项目中需要开启RTTI,链接的外部库是no-RTTI编译的,在现在的工程中重载外部库的带虚函数的类,连接的时候报错.

==**因此编译的时候，把原来加上的 `-frtti` 改成 `-fno-rtti`，也就是不启用( no )rtti功能，就编译通过了。**==



### 警告：

```
/usr/bin/ld: warning: /usr/lib/gcc/x86_64-linux-gnu/7/libstdc++.so: unsupported GNU_PROPERTY_TYPE (5) type: 0xc0010001
/usr/bin/ld: warning: /usr/lib/gcc/x86_64-linux-gnu/7/libstdc++.so: unsupported GNU_PROPERTY_TYPE (5) type: 0xc0010002
```





## 技巧：



**查看当前使用的编译器、链接器**

`which lld`

/home/luguangyang/clang+llvm-10.0.0-x86_64-linux-gnu-ubuntu-18.04/bin/lld

`which g++`

/usr/bin/g++

`which clang`
		/home/luguangyang/clang+llvm-15.0.5-x86_64-linux-gnu-ubuntu-18.04/bin/clang











































# 20240528会议记录

两部分：

* DFG：把代码变成数据流图

* mapper：把数据流图映射到CGRA上



```
make src/dfg/dfg.out
```



> itostr找不到：
>
> 使用std::to_string





```
make run_test
```



### DFG

输出llvm IR

```
llvm-dis ./test/dfg/src/alg1.bc -o alg1.ll
```

simulator/src下有C代码，alg1.ll为llvm IR



phi是一个取值的节点

block：代码是顺序执行。%10只可以被赋值一次，是单赋值的。

为了保证%8每次开始的时候都被运行，并且只会被赋值一次，从label2 进来的时候（图中的箭头）%8的值为0，而从label33进来的时候，值是%15

<img src="C:\Users\LGY\AppData\Roaming\Typora\typora-user-images\image-20240604111520593.png" alt="image-20240604111520593" style="zoom:67%;" />

%也是类似，如果是从%33进入，那这个值就是%34，34%就是%9加1，所以是自加。所以%9就是for循环中的 i 。

所有的数据都是PE之间互传，只有store对外部数据有影响。如果为真，存储到真实地址，否则存储到一个虚拟的地址，这样就不会对外部有影响。



打开编译出来的dot文件：

```
xdot ./test/dfg/output/alg1_loop_0.dot &
```



### mapper

![image-20240604113816578](C:\Users\LGY\AppData\Roaming\Typora\typora-user-images\image-20240604113816578.png)



先把信息提取出来

主要是VF3mapping，排序和剪枝的算法（可以搜到：子图同构VF3）

> 先初始化内存
>
> sort排序

==寄存器的分配与子图同构是同步进行的。==

然后输出一些信息。

最终生成汇编文件。asm



selftest里面是benchmark。之前是DFG太大，搞不定。跑通了165。

怎么把循环变小。for循环拆开（看之前的跑通的例子）



dfg编译出来的内容进行测试：

```
./dfg.out -o "alg1" ./self_tests/src_huawei/alg1.cpp
```



C代码编译出bc文件，就是llvm IR。bc文件用下面的代码获取：

```
clang -emit -llvm -c './self_tests/src_huawei/alg1.cpp' -o 'alg1.bc' -O3 -fpg......//未完，在makefile中
```

然后run_test

```
alg7.bc: ./self_tests/src_huawei/alg7.cpp
	clang -emit-llvm -c './self_tests/src_huawei/alg7.cpp' -o 'alg7.bc' -O3 -fno-vectorize -fno-slp-vectorize -fno-unroll-loops -m32
```

