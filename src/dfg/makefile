# Variable ===============================================================================
PHONY =
MODE = DEBUG
HOSTNAME = $(shell hostname)

LLVM_INCLUDE_PATH = $(HOME)/clang+llvm-10.0.0-x86_64-linux-gnu-ubuntu-18.04/include
LLVM_LIB_PATH = $(HOME)/clang+llvm-10.0.0-x86_64-linux-gnu-ubuntu-18.04/lib

ifeq ($(MODE), DEBUG)
ifeq ($(HOSTNAME), shore-82wm)
CFLAGS = -m64 -g -I$(LLVM_INCLUDE_PATH) 
LDFLAGS = -L$(LLVM_LIB_PATH) -lLLVM
else
CFLAGS = -m64 -g -I$(LLVM_INCLUDE_PATH)  	
LDFLAGS = -L$(LLVM_LIB_PATH) -lLLVM 	#-lLLVM-15
endif
else
ifeq ($(HOSTNAME), shore-82wm)
CFLAGS = -m64 -Ofast -I$(LLVM_INCLUDE_PATH) 
LDFLAGS = -L$(LLVM_LIB_PATH) -lLLVM
else
CFLAGS = -m64 -Ofast -I$(LLVM_INCLUDE_PATH) 
LDFLAGS = -L$(LLVM_LIB_PATH) -lLLVM 	#-lLLVM-15
endif
endif

# build ==================================================================================
output.o: output.h output.cpp utils.h
	g++ $(CFLAGS) -c output.cpp -o output.o
passes.o: passes.h passes.cpp utils.h
	g++ $(CFLAGS) -c passes.cpp -o passes.o
spec_i.o: spec_i.h spec_i.cpp utils.h
	g++ $(CFLAGS) -c spec_i.cpp -o spec_i.o
utils.o: utils.h utils.cpp
	g++ $(CFLAGS) -c utils.cpp -o utils.o
visitor.o: visitor.h visitor.cpp utils.h
	g++ $(CFLAGS) -c visitor.cpp -o visitor.o
main.o: main.cpp utils.h output.h passes.h spec_i.h visitor.h
	g++ $(CFLAGS) -c ./main.cpp -o main.o
dfg.out:output.o passes.o spec_i.o utils.o visitor.o main.o
	g++ $^ $(LDFLAGS) -o dfg.out

# Clean ==================================================================================
clean:
	rm -rf *.o *.out

PHONY += clean