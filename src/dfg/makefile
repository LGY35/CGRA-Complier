# Variable ===============================================================================
PHONY =
MODE = DEBUG
HOSTNAME = $(shell hostname)


# LLVM_INCLUDE_PATH = $(HOME)/clang+llvm-15.0.5-x86_64-linux-gnu-ubuntu-18.04/include
# LLVM_LIB_PATH = $(HOME)/clang+llvm-15.0.5-x86_64-linux-gnu-ubuntu-18.04/lib/
# LLVM_LIBS = $(shell $(HOME)/clang+llvm-15.0.5-x86_64-linux-gnu-ubuntu-18.04/bin/llvm-config --libs all)
# LLVM_LDFLAGS = $(shell $(HOME)/clang+llvm-15.0.5-x86_64-linux-gnu-ubuntu-18.04/bin/llvm-config --ldflags)

LLVM_INCLUDE_PATH = /usr/lib/llvm-16/include
LLVM_LIB_PATH = /usr/lib/llvm-16/lib
LLVM_LIBS = $(shell llvm-config-16 --libs all)
LLVM_LDFLAGS = $(shell llvm-config-16 --ldflags)

# LLVM_INCLUDE_PATH = /usr/lib/llvm-6.0/include
# LLVM_LIB_PATH = /usr/lib/llvm-6.0/lib
# LLVM_LIBS = $(shell llvm-config-6.0 --libs all)
# LLVM_LDFLAGS = $(shell llvm-config-6.0 --ldflags)

# LLVM_LIBS = -lLLVM

# 添加 -lpthread 以解决与线程相关的链接错误。

ifeq ($(MODE), DEBUG)
ifeq ($(HOSTNAME), shore-82wm)
CFLAGS = -m64 -g -fno-rtti -I$(LLVM_INCLUDE_PATH) 
LDFLAGS = -L$(LLVM_LIB_PATH) $(LLVM_LIBS) -lpthread		#-lLLVM
else
CFLAGS = -m64 -g -fno-rtti -I$(LLVM_INCLUDE_PATH)  	
LDFLAGS = -L$(LLVM_LIB_PATH) $(LLVM_LIBS) -lpthread		#-lLLVM-15
endif
else
ifeq ($(HOSTNAME), shore-82wm)
CFLAGS = -m64 -g -Ofast -fno-rtti -I$(LLVM_INCLUDE_PATH) 
LDFLAGS = -L$(LLVM_LIB_PATH) $(LLVM_LIBS) -lpthread		#-lLLVM
else
CFLAGS = -m64 -g -Ofast -fno-rtti -I$(LLVM_INCLUDE_PATH) 
LDFLAGS = -L$(LLVM_LIB_PATH) $(LLVM_LIBS) -lpthread		#-lLLVM-15
endif
endif

# build ==================================================================================
output.o: output.h output.cpp utils.h
	clang++ $(CFLAGS) -c output.cpp -o output.o
#	g++ $(CFLAGS) -c output.cpp -o output.o
passes.o: passes.h passes.cpp utils.h
	clang++ $(CFLAGS) -c passes.cpp -o passes.o
#	g++ $(CFLAGS) -c passes.cpp -o passes.o
spec_i.o: spec_i.h spec_i.cpp utils.h
	clang++ $(CFLAGS) -c spec_i.cpp -o spec_i.o
#	g++ $(CFLAGS) -c spec_i.cpp -o spec_i.o
utils.o: utils.h utils.cpp
	clang++ $(CFLAGS) -c utils.cpp -o utils.o
#	g++ $(CFLAGS) -c utils.cpp -o utils.o
visitor.o: visitor.h visitor.cpp utils.h
	clang++ $(CFLAGS) -c visitor.cpp -o visitor.o
#	g++ $(CFLAGS) -c visitor.cpp -o visitor.o
main.o: main.cpp utils.h output.h passes.h spec_i.h visitor.h
	clang++ $(CFLAGS) -c ./main.cpp -o main.o
#	g++ $(CFLAGS) -c ./main.cpp -o main.o
dfg.out:output.o passes.o spec_i.o utils.o visitor.o main.o
	clang++ $^ $(LDFLAGS) -o dfg.out
#	g++ $^ $(LDFLAGS) -o dfg.out

# Clean ==================================================================================
clean:
	rm -rf *.o *.out

PHONY += clean