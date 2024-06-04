# $@  表示目标文件
# $^  表示所有的依赖文件
# $<  表示第一个依赖文件
# $?  表示比目标还要新的依赖文件列表
# Variable ===============================================================================
PHONY =
MODE = DEBUG
ifeq ($(MODE), DEBUG)
CFLAGS = -m64 -g -lcgraph -lgvc
else
CFLAGS = -m64 -Ofast -lcgraph -lgvc
endif

# build ==================================================================================
bitmatrix.o: bitmatrix.h utils.h bitmatrix.c
	gcc $(CFLAGS) -c bitmatrix.c -o bitmatrix.o
CGRA.o: CGRA.h utils.h CGRA.c
	gcc $(CFLAGS) -c CGRA.c -o CGRA.o
codegen.o: codegen.h utils.h codegen.c
	gcc $(CFLAGS) -c codegen.c -o codegen.o
dfg.o: dfg.h utils.h dfg.c
	gcc $(CFLAGS) -c dfg.c -o dfg.o
operation.o: operation.h utils.h operation.c
	gcc $(CFLAGS) -c operation.c -o operation.o
readdot.o: readdot.h utils.h readdot.c
	gcc $(CFLAGS) -c readdot.c -o readdot.o
utils.o: utils.h utils.c
	gcc $(CFLAGS) -c utils.c -o utils.o
VF3.o: VF3.h utils.h VF3.c
	gcc $(CFLAGS) -c VF3.c -o VF3.o
main.o: main.c utils.h bitmatrix.h CGRA.h codegen.h dfg.h operation.h readdot.h VF3.h
	gcc $(CFLAGS) -c ./main.c -o main.o
rpmalloc.o: ../../submodules/rpmalloc/rpmalloc/rpmalloc.c ../../submodules/rpmalloc/rpmalloc/rpmalloc.h
	gcc $(CFLAGS) -c ../../submodules/rpmalloc/rpmalloc/rpmalloc.c -o rpmalloc.o
argparse.o: ../../submodules/argparse/argparse.c ../../submodules/argparse/argparse.h
	gcc $(CFLAGS) -c ../../submodules/argparse/argparse.c  -o argparse.o
cjson.o: ../../submodules/cJSON/cJSON.c ../../submodules/cJSON/cJSON.h
	gcc $(CFLAGS) -c ../../submodules/cJSON/cJSON.c -o cjson.o
mapper.out:bitmatrix.o CGRA.o codegen.o dfg.o operation.o readdot.o utils.o VF3.o main.o rpmalloc.o argparse.o cjson.o
	gcc $^ $(CFLAGS) -o mapper.out
# Clean ==================================================================================
clean:
	rm -rf *.o *.out
PHONY += clean