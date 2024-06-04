
alg6_loop_0.dot alg6_loop_1.dot:dfg.out ./self_tests/src_huawei/alg6.cpp
	./dfg.out -o "alg6" ./self_tests/src_huawei/alg6.cpp
run_alg6: alg6_loop_0.dot alg6_loop_1.dot mapper.out
	./mapper.out -d alg6_loop_0.dot -l 5971968 -a alg6_loop_0.asm -s
	./mapper.out -d alg6_loop_1.dot -l 2985984 -a alg6_loop_1.asm -s
	
# Clean ==================================================================================
clean:
	-rm *.asm *.dot
	
