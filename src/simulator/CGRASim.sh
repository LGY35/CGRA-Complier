#!/bin/bash
echo running PROJECT/CGRASIM.sh
#rm ./build/*
#rm ./LOG/*
#rm ./dst_pic/*
cd ./build
cmake ..
make clean
make

# @param argv[0] Executable
# @param argv[1] Path of algorithm input raw file
# @param argv[2] Number of tasks
# @param argv[3] path of Simulation Instruction decode trace file
# @param argv[4] path of Simulation statistic reference file
# @param argv[5] DebugFlag output flag, default to false(0), set 1 to display debug trace during simulation
# @param argv[6] path of instruction file
# @param argv[7] path of instruction file
#./CGRA_Simulator ../dst_pic/alg1_func1_output.raw 2 ../LOG/cgrar_debug_log.txt ../LOG/performance_reference.txt 1   ../CompilerOut/alg6_loop_1.txt  ../CompilerOut/alg6_loop_0.txt 

#valgrind --tool=massif ./CGRA_Simulator ../dst_pic/alg1_func1_output.raw 2 ../LOG/cgrar_debug_log.txt ../LOG/performance_reference.txt 0   ../CompilerOut/alg6_loop_1.txt  ../CompilerOut/alg6_loop_0.txt 

#valgrind --leak-check=full --show-leak-kinds=all --log-file=output.txt ./CGRA_Simulator ../dst_pic/alg5_func_output.raw 1 ../LOG/cgrar_debug_log.txt ../LOG/performance_reference.txt 0 ../CompilerOut/alg1_loop_0.txt

#./CGRA_Simulator ../dst_pic/alg5_func_output.raw 11 ../LOG/cgrar_debug_log.txt ../LOG/performance_reference.txt 0 ../CompilerOut/alg5_loop_0.txt ../CompilerOut/alg5_loop_1.txt ../CompilerOut/alg5_loop_2.txt ../CompilerOut/alg5_loop_3.txt ../CompilerOut/alg5_loop_4.txt ../CompilerOut/alg1_loop_0.txt ../CompilerOut/alg6_loop_0.txt ../CompilerOut/alg6_loop_1.txt ../CompilerOut/alg6_loop_2.txt ../CompilerOut/alg6_loop_3.txt ../CompilerOut/alg6_loop_4.txt


./CGRA_Simulator ../dst_pic/alg5_func_output.raw 11 ../LOG/cgrar_debug_log.txt ../LOG/performance_reference.txt 0 ../CompilerOut/alg5_loop_0.txt ../CompilerOut/alg5_loop_1.txt ../CompilerOut/alg5_loop_2.txt ../CompilerOut/alg5_loop_3.txt ../CompilerOut/alg5_loop_4.txt ../CompilerOut/alg1_loop_0.txt ../CompilerOut/alg6_loop_0.txt ../CompilerOut/alg6_loop_1.txt ../CompilerOut/alg6_loop_2.txt ../CompilerOut/alg6_loop_3.txt ../CompilerOut/alg6_loop_4.txt



