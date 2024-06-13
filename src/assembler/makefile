
alg6_loop_0.dot alg6_loop_1.dot:dfg.out ./self_tests/src_huawei/alg6.cpp
	./dfg.out -o "alg6" ./self_tests/src_huawei/alg6.cpp
run_alg6: alg6_loop_0.dot alg6_loop_1.dot mapper.out
	./mapper.out -d alg6_loop_0.dot -l 5971968 -a alg6_loop_0.asm -s
	./mapper.out -d alg6_loop_1.dot -l 2985984 -a alg6_loop_1.asm -s


CFLAGS = -I/usr/include/x86_64-linux-gnu -I/usr/include/i386-linux-gnu -I/usr/include/x86_64-linux-gnu/c++/7 -I/usr/include/c++/7


## 生成bc
alg7.bc: ./self_tests/src_huawei/alg7.cpp
	clang -emit-llvm -c './self_tests/src_huawei/alg7.cpp' $(CFLAGS) -o '../../test/dfg/src/alg7.bc' -O3  -fno-vectorize -fno-slp-vectorize -fno-unroll-loops -m32

# Clean ==================================================================================
clean:
	-rm *.asm *.dot
	
