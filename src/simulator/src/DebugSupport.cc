
#include "../include/DebugSupport.hh"
#include "../include/CGRA_define.hh"
#include "../include/WIRE.hh"
#include "../include/PEA.hh"
#include "../include/CU.hh"

#include "../include/PE.hh"
#include "../include/GR.hh"
#include "./alg0.hh"
#include "./alg1.hh"
#include "./alg2.hh"
#include "./alg3.hh"
#include "./alg4.hh"
#include "./alg5.hh"
#include "./alg6.hh"
#include "./alg7.hh"
#include "assert.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <unistd.h> //for pause();
using namespace std;
//==========isp code=============
static unsigned short src_d1_data[SIZE_D1_H][SIZE_D1_W] = { 0 };
static unsigned short dst_d1_data[SIZE_D1_H][SIZE_D1_W] = { 0 };
static unsigned short src_d2_data[SIZE_D1_H][SIZE_D1_W][3] = {0};
static unsigned short dst_d2_data[D2_HEIGHT_OUT][D2_WIDTH_OUT][3] = { 0 };
static unsigned short src_d3_data[SIZE_D1_H/2 * SIZE_D1_W/2 * 2]= { 0 };
static unsigned short dst_d3_data[SIZE_D1_H / 2 * SIZE_D1_W / 2 * 2]= { 0 };
static unsigned short d4_dst[SIZE_D1_H*SIZE_D1_W]= { 0 };
int out_data[GRID_H][GRID_W] = { 0 };
float si;
#define clip_bits(X, MIN, MAX)  (((X) < (MIN)) ? (MIN) : (((X) > (MAX)) ? (MAX) : (X)))
//==========isp code=============
void debug_to_file(char* filename, std::string debuginfo)
{
    std::ofstream ofs;
	ofs.open(filename,ios::out | ios::app);
    if(!ofs){
        cout<<"Error can't open debug path"<<endl;
    }
	assert(ofs);
    ofs<<debuginfo<<endl;
    ofs.close();
}
/*
@param char* f_name: file path of rawfile of alg1_func1 algorithm output
@param RceSimResource res: RceSimResource is a struct that encapsule a abstract memory
@param DebugParam_t * debug: DebugParam_t is a struct that contains a function pointer for memory address mapping, see static void *addrMapper(DATAWIDTH_0 addr, DATAWIDTH_0 len)
*/
int get_resource(char *f_name, RceSimResource &res, DebugParam_t *debug)
{
	logi("Memread : preprocessing of algorithm:\n");
	//fetch input data: run isp code from the beginning until acquire expeted algorithm input
	isp_main();
	int address_count = 0;
	//-----------------ALG5_FUNC0/1/2/3/4/+ALG1_FUNC1+ALG6_FUNC0/1/2/3/4---------
	//preprocess of alg5_func input data
	std::vector<unsigned short> res_src_d1_data; //Input of alg5_func
	std::vector<unsigned short> res_src_d2_data(3 * D2_HEIGHT_IN * D2_WIDTH_IN);// Output of alg5_func, input of alg1_func1
	std::vector<unsigned short> res_dst_d2_data(D2_HEIGHT_OUT * D2_WIDTH_OUT *  3);// Output of alg1_func1, input of alg6_func
	std::vector<unsigned short> res_src_d3_data(SIZE_D1_H/2 * SIZE_D1_W/2 * 2);// Output of alg6_func1
	std::vector<unsigned short> alg5_c1(SIZE_D1_H / 2 * SIZE_D1_W / 2);
	std::vector<unsigned short> alg5_c2(SIZE_D1_H / 2 * SIZE_D1_W / 2);
	std::vector<unsigned short> alg5_c3(SIZE_D1_H / 2 * SIZE_D1_W / 2);
	std::vector<unsigned short> alg5_c4(SIZE_D1_H / 2 * SIZE_D1_W / 2);
	std::vector<unsigned short> alg6_dst_d4(SIZE_D1_H*SIZE_D1_W );
	std::vector<unsigned short> alg6_d3_1(ALG6_HEIGHT * ALG6_WIDTH);
	std::vector<unsigned short> alg6_d3_2(ALG6_HEIGHT * ALG6_WIDTH);
	std::vector<unsigned short> alg6_d3_3(ALG6_HEIGHT * ALG6_WIDTH);
	std::vector<unsigned short> alg6_d3_2_dst(ALG6_HEIGHT * ALG6_WIDTH / 2);
	std::vector<unsigned short> alg6_d3_3_dst(ALG6_HEIGHT * ALG6_WIDTH / 2);
	//---------------read file:input of alg5_func------------------
	FILE* fp = NULL;
	char alg5_func_input_path[100] = { "../dst_pic/alg4_func_output.raw" };
	fopen_s(&fp, alg5_func_input_path, "rb");
	if (fp == NULL) {
		logi("can not open file path %s\n",f_name);
		pause();//pause();//system("pause");
		return -1;
	}
	else {
		unsigned short* ptr = NULL;
		ptr = (unsigned short*)malloc(sizeof(unsigned short));
		for (int i = 0; i < SIZE_D1_H; i++) 
		{
			for (int j = 0; j < SIZE_D1_W; j++) 
			{				
				size_t sizeRead = fread(ptr, 2, 1, fp);
				if(sizeRead != 1) {logi("fread error! \n"); pause();} 
				unsigned short temp = *ptr;
				res_src_d1_data.push_back(temp);
			}
		}	
		fclose(fp);
		free(ptr);
		ptr = NULL;
		
	}
	
	res.mem.insert(res.mem.begin(),res_src_d1_data.begin(),res_src_d1_data.end());
	cout << "res_src_d1_data.size() = " << std::dec << res_src_d1_data.size() << " 	  ";
	cout << "res_src_d1_data.base_addr = " << "(" << std::dec << address_count << ")";
	cout << "0X"<<std::hex << std::setw(8) << setfill('0') << address_count << "  " << endl;
	address_count =  sizeof(unsigned short) * res.mem.size();
	cout << "res_src_d2_data.size() = " << std::dec << res_src_d2_data.size() << " 	  ";
	cout << "res_src_d2_data.base_addr = " << "(" << std::dec << address_count << ")";
	cout << "0X"<<std::hex << std::setw(8) << setfill('0') << address_count << "  " << endl;
	res.mem.insert(res.mem.end(),res_src_d2_data.begin(),res_src_d2_data.end());
	address_count =  sizeof(unsigned short) * res.mem.size();
	cout << "res_dst_d2_data.size() = " << std::dec << res_dst_d2_data.size() << " 	  ";
	cout << "res_dst_d2_data.base_addr = " << "(" << std::dec << address_count << ")";
	cout << "0X"<<std::hex << std::setw(8) << setfill('0') << address_count << "  " << endl;
	res.mem.insert(res.mem.end(),res_dst_d2_data.begin(),res_dst_d2_data.end());
	address_count =  sizeof(unsigned short) * res.mem.size();
	cout << "res_src_d3_data.size() = " << std::dec << res_src_d3_data.size() << " 	  ";
	cout << "res_src_d3_data.base_addr = " << "(" << std::dec << address_count << ")";
	cout << "0X"<<std::hex << std::setw(8) << setfill('0') << address_count << "  " << endl;
	res.mem.insert(res.mem.end(),res_src_d3_data.begin(),res_src_d3_data.end());
	address_count =  sizeof(unsigned short) * res.mem.size();
	cout << "alg5_c1.size() = " << std::dec << alg5_c1.size() << " 	  ";
	cout << "alg5_c1.base_addr = " << "(" << std::dec << address_count << ")";
	cout << "0X"<<std::hex << std::setw(8) << setfill('0') << address_count << "  " << endl;
	res.mem.insert(res.mem.end(),alg5_c1.begin(),alg5_c1.end());
	address_count =  sizeof(unsigned short) * res.mem.size();
	cout << "alg5_c2.size() = " << std::dec << alg5_c2.size() << " 	  ";
	cout << "alg5_c2.base_addr = " << "(" << std::dec << address_count << ")";
	cout << "0X"<<std::hex << std::setw(8) << setfill('0') << address_count << "  " << endl;
	res.mem.insert(res.mem.end(),alg5_c2.begin(),alg5_c2.end());
	address_count =  sizeof(unsigned short) * res.mem.size();
	cout << "alg5_c3.size() = " << std::dec << alg5_c3.size() << " 	  ";
	cout << "alg5_c3.base_addr = " << "(" << std::dec << address_count << ")";
	cout << "0X"<<std::hex << std::setw(8) << setfill('0') << address_count << "  " << endl;
	res.mem.insert(res.mem.end(),alg5_c3.begin(),alg5_c3.end());
	address_count =  sizeof(unsigned short) * res.mem.size();
	cout << "alg5_c4.size() = " << std::dec << alg5_c4.size() << " 	  ";
	cout << "alg5_c4.base_addr = " << "(" << std::dec << address_count << ")";
	cout << "0X"<<std::hex << std::setw(8) << setfill('0') << address_count << "  " << endl;
	res.mem.insert(res.mem.end(),alg5_c4.begin(),alg5_c4.end());
	address_count =  sizeof(unsigned short) * res.mem.size();
	cout << "alg6_dst_d4.size() = " << std::dec << alg6_dst_d4.size() << " 	  ";
	cout << "alg6_dst_d4.base_addr = " << "(" << std::dec << address_count << ")";
	cout << "0X"<<std::hex << std::setw(8) << setfill('0') << address_count << "  " << endl;
	res.mem.insert(res.mem.end(),alg6_dst_d4.begin(),alg6_dst_d4.end());
	address_count =  sizeof(unsigned short) * res.mem.size();
	unsigned short dump_slot = 0;
	res.mem.push_back(dump_slot);
	cout << "dump.base_addr = " << "(" << std::dec << address_count << ")";
	cout << "0X"<<std::hex << std::setw(8) << setfill('0') << address_count << "  " << endl;
	address_count =  sizeof(unsigned short) * res.mem.size();
	cout << "alg6_d3_1.size() = " << std::dec << alg6_d3_1.size() << " 	  ";
	cout << "alg6_d3_1.base_addr = " << "(" << std::dec << address_count << ")";
	cout << "0X"<<std::hex << std::setw(8) << setfill('0') << address_count << "  " << endl;
	res.mem.insert(res.mem.end(),alg6_d3_1.begin(),alg6_d3_1.end());
	address_count =  sizeof(unsigned short) * res.mem.size();
	cout << "alg6_d3_2.size() = " << std::dec << alg6_d3_2.size() << " 	  ";
	cout << "alg6_d3_2.base_addr = " << "(" << std::dec << address_count << ")";
	cout << "0X"<<std::hex << std::setw(8) << setfill('0') << address_count << "  " << endl;
	res.mem.insert(res.mem.end(),alg6_d3_2.begin(),alg6_d3_2.end());
	address_count =  sizeof(unsigned short) * res.mem.size();
	cout << "alg6_d3_3.size() = " << std::dec << alg6_d3_3.size() << " 	  ";
	cout << "alg6_d3_3.base_addr = " << "(" << std::dec << address_count << ")";
	cout << "0X"<<std::hex << std::setw(8) << setfill('0') << address_count << "  " << endl;
	res.mem.insert(res.mem.end(),alg6_d3_3.begin(),alg6_d3_3.end());
	address_count =  sizeof(unsigned short) * res.mem.size();
	cout << "alg6_d3_2_dst.size() = " << std::dec << alg6_d3_2_dst.size() << " 	  ";
	cout << "alg6_d3_2_dst.base_addr = " << "(" << std::dec << address_count << ")";
	cout << "0X"<<std::hex << std::setw(8) << setfill('0') << address_count << "  " << endl;
	res.mem.insert(res.mem.end(),alg6_d3_2_dst.begin(),alg6_d3_2_dst.end());
	address_count =  sizeof(unsigned short) * res.mem.size();
	cout << "alg6_d3_3_dst.size() = " << std::dec << alg6_d3_3_dst.size() << " 	  ";
	cout << "alg6_d3_3_dst.base_addr = " << "(" << std::dec << address_count << ")";
	cout << "0X"<<std::hex << std::setw(8) << setfill('0') << address_count << "  " << endl;
	res.mem.insert(res.mem.end(),alg6_d3_3_dst.begin(),alg6_d3_3_dst.end());
	address_count =  sizeof(unsigned short) * res.mem.size();
	return 0;
}


/*
@param int taskid: ID of compilation task
@param DebugParam_t * debug: DebugParam_t is a struct that contains a function pointer for memory address mapping, see static void *addrMapper(DATAWIDTH_0 addr, DATAWIDTH_0 len)
*/
void write_result_to_file(int taskid, DebugParam_t *debug) {
		enum BASEADDR {
			RES_SRC_D1_DATA = 0,//Input of alg5_func
			RES_SRC_D2_DATA = 23887872,// Output of alg5_func, input of alg1_func1
			RES_DES_D2_DATA = 95551488,// Output of alg1_func1, input of alg6_func
			RES_SRC_D3_DATA = 113467392,// Output of alg6_func1
			RES_C1_DATA = 125051328,
			RES_C2_DATA = 131023296,
			RES_C3_DATA = 136995264,
			RES_C4_DATA = 142967232,
			RES_D4_DST_DATA = 148939200,
			RES_D3_1_DATA = 172827074,
			RES_D3_2_DATA = 178799042,
			RES_D3_3_DATA = 184771010,
			RES_D3_2_DST_DATA = 190742978,
			RES_D3_3_DST_DATA = 193728962

			} ;
		enum SIZE {
			RES_SRC_D1_DATA_SIZE = (SIZE_D1_H * SIZE_D1_W),
			RES_SRC_D2_DATA_SIZE = (3 * SIZE_D1_H * SIZE_D1_W),
			RES_DST_D2_DATA_SIZE = (D2_HEIGHT_OUT * D2_WIDTH_OUT *  3),
			RES_SRC_D3_DATA_SIZE = (SIZE_D1_H/2 * SIZE_D1_W/2 * 2),
			RES_C1_DATA_SIZE = (SIZE_D1_H * SIZE_D1_W / 4),
			RES_C2_DATA_SIZE = (SIZE_D1_H * SIZE_D1_W / 4),
			RES_C3_DATA_SIZE = (SIZE_D1_H * SIZE_D1_W / 4),
			RES_C4_DATA_SIZE = (SIZE_D1_H * SIZE_D1_W / 4),
			RES_D4_DST_DATA_SIZE = SIZE_D1_H*SIZE_D1_W,
			RES_D3_1_DATA_SIZE = 2985984,
			RES_D3_2_DATA_SIZE = 2985984,
			RES_D3_3_DATA_SIZE = 2985984,
			RES_D3_2_DST_DATA_SIZE = 1492992,
			RES_D3_3_DST_DATA_SIZE = 1492992
			};
	if(taskid == 0){
		cout<<"---------------------------------------------------------------------"<<endl;
		char write_file_path[256] = { "../dst_pic/cgra_alg5_func_c1_output.raw" };
		cout<<"TASK["<<taskid<<"] :write "<< write_file_path <<" BEGIN"<<endl;
		BASEADDR result_base = RES_C1_DATA;
		SIZE result_size = RES_C1_DATA_SIZE;
		FILE *fp = NULL;
		fopen_s(&fp, write_file_path, "wb");
		if (fp == NULL)
		{
			cout<<"failed to open file:"<<write_file_path<<endl;
			pause();//pause();//system("pause");
			fclose(fp);
			return;
		}
		else {
			for (int i = 0; i < (int)result_size; i++)
			{
					DATAWIDTH_0 write_addr;
					write_addr = result_base + i*sizeof(unsigned short);
					unsigned short temp = *(unsigned short*)((debug)->addr_map(write_addr, sizeof(unsigned short)));
					fwrite(&temp, sizeof(unsigned short), 1, fp);
					//if(i<10) {cout<<"write to file: "<<write_file_path<<", addr("<<dec<<write_addr<<"), data("<<dec<<temp<<")"<<endl;}
			}
		}
		fclose(fp);
		cout<<"TASK["<<taskid<<"] :write "<< write_file_path <<" END"<<endl;

		char write_file_path1[256] = { "../dst_pic/cgra_alg5_func_c2_output.raw" };
		cout<<"TASK["<<taskid<<"] :write "<< write_file_path1 <<" BEGIN"<<endl;
		result_base = RES_C2_DATA;
		result_size = RES_C2_DATA_SIZE;
		fopen_s(&fp, write_file_path1, "wb");
		if (fp == NULL)
		{
			cout<<"failed to open file:"<<write_file_path1<<endl;
			pause();//pause();//system("pause");
			fclose(fp);
			return;
		}
		else {
			for (int i = 0; i < (int)result_size; i++)
			{
					DATAWIDTH_0 write_addr;
					write_addr = result_base + i*sizeof(unsigned short);
					unsigned short temp = *(unsigned short*)((debug)->addr_map(write_addr, sizeof(unsigned short)));
					fwrite(&temp, sizeof(unsigned short), 1, fp);
					//if(i<10) {cout<<"write to file: "<<write_file_path1<<", addr("<<dec<<write_addr<<"), data("<<dec<<temp<<")"<<endl;}
			}
		}
		fclose(fp);
		cout<<"TASK["<<taskid<<"] :write "<< write_file_path1 <<" END"<<endl;
		cout<<"---------------------------------------------------------------------"<<endl;
		return;	
	}else if(taskid == 1)
	{
		cout<<"---------------------------------------------------------------------"<<endl;
		char write_file_path[256] = { "../dst_pic/cgra_alg5_func_c3_output.raw" };
		cout<<"TASK["<<taskid<<"] :write "<< write_file_path <<" BEGIN"<<endl;
		BASEADDR result_base = RES_C3_DATA;
		SIZE result_size = RES_C3_DATA_SIZE;
		FILE *fp = NULL;
		fopen_s(&fp, write_file_path, "wb");
		if (fp == NULL)
		{
			cout<<"failed to open file:"<<write_file_path<<endl;
			pause();//pause();//system("pause");
			fclose(fp);
			return;
		}
		else {
			for (int i = 0; i < (int)result_size; i++)
			{
					DATAWIDTH_0 write_addr;
					write_addr = result_base + i*sizeof(unsigned short);
					unsigned short temp = *(unsigned short*)((debug)->addr_map(write_addr, sizeof(unsigned short)));
					fwrite(&temp, sizeof(unsigned short), 1, fp);
					//if(i<10) {cout<<"write to file: "<<write_file_path<<", addr("<<dec<<write_addr<<"), data("<<dec<<temp<<")"<<endl;}
			}
		}
		fclose(fp);
		cout<<"TASK["<<taskid<<"] :write "<< write_file_path <<" END"<<endl;

		char write_file_path1[256] = { "../dst_pic/cgra_alg5_func_c4_output.raw" };
		cout<<"TASK["<<taskid<<"] :write "<< write_file_path1 <<" BEGIN"<<endl;
		result_base = RES_C4_DATA;
		result_size = RES_C4_DATA_SIZE;
		fopen_s(&fp, write_file_path1, "wb");
		if (fp == NULL)
		{
			cout<<"failed to open file:"<<write_file_path1<<endl;
			pause();//pause();//system("pause");
			fclose(fp);
			return;
		}
		else {
			for (int i = 0; i < (int)result_size; i++)
			{
					DATAWIDTH_0 write_addr;
					write_addr = result_base + i*sizeof(unsigned short);
					unsigned short temp = *(unsigned short*)((debug)->addr_map(write_addr, sizeof(unsigned short)));
					fwrite(&temp, sizeof(unsigned short), 1, fp);
					//if(i<10) {cout<<"write to file: "<<write_file_path1<<", addr("<<dec<<write_addr<<"), data("<<dec<<temp<<")"<<endl;}
			}
		}
		fclose(fp);
		cout<<"TASK["<<taskid<<"] :write "<< write_file_path1 <<" END"<<endl;
		cout<<"---------------------------------------------------------------------"<<endl;
		return;	
	}else if(taskid == 2 || taskid == 3 || taskid == 4)
	{
		cout<<"---------------------------------------------------------------------"<<endl;
		char write_file_path[256] = { "../dst_pic/cgra_alg5_func_src_d2_data.raw" };
		cout<<"TASK["<<taskid<<"] :write "<< write_file_path <<" BEGIN"<<endl;
		BASEADDR result_base = RES_SRC_D2_DATA;
		SIZE result_size = RES_SRC_D2_DATA_SIZE;
		FILE *fp = NULL;
		fopen_s(&fp, write_file_path, "wb");
		if (fp == NULL)
		{
			cout<<"failed to open file:"<<write_file_path<<endl;
			pause();//pause();//system("pause");
			fclose(fp);
			return;
		}
		else {
			for (int i = 0; i < (int)result_size; i++)
			{
					DATAWIDTH_0 write_addr;
					write_addr = result_base + i*sizeof(unsigned short);
					unsigned short temp = *(unsigned short*)((debug)->addr_map(write_addr, sizeof(unsigned short)));
					fwrite(&temp, sizeof(unsigned short), 1, fp);
					//if(i<10) {cout<<"write to file: "<<write_file_path<<", addr("<<dec<<write_addr<<"), data("<<dec<<temp<<")"<<endl;}
			}
		}
		fclose(fp);
		cout<<"TASK["<<taskid<<"] :write "<< write_file_path <<" END"<<endl;
		cout<<"---------------------------------------------------------------------"<<endl;
		return;	
	}else if(taskid == 5)
	{
		cout<<"---------------------------------------------------------------------"<<endl;
		char write_file_path[256] = { "../dst_pic/cgra_alg1_func1_dst_d2_data.raw" };
		cout<<"TASK["<<taskid<<"] :write "<< write_file_path <<" BEGIN"<<endl;
		BASEADDR result_base = RES_DES_D2_DATA;
		SIZE result_size = RES_DST_D2_DATA_SIZE;
		FILE *fp = NULL;
		fopen_s(&fp, write_file_path, "wb");
		if (fp == NULL)
		{
			cout<<"failed to open file:"<<write_file_path<<endl;
			pause();//pause();//system("pause");
			fclose(fp);
			return;
		}
		else {
			for (int i = 0; i < (int)result_size; i++)
			{
					DATAWIDTH_0 write_addr;
					write_addr = result_base + i*sizeof(unsigned short);
					unsigned short temp = *(unsigned short*)((debug)->addr_map(write_addr, sizeof(unsigned short)));
					fwrite(&temp, sizeof(unsigned short), 1, fp);
					//if(i<10) {cout<<"write to file: "<<write_file_path<<", addr("<<dec<<write_addr<<"), data("<<dec<<temp<<")"<<endl;}
			}
		}
		fclose(fp);
		cout<<"TASK["<<taskid<<"] :write "<< write_file_path <<" END"<<endl;
		cout<<"---------------------------------------------------------------------"<<endl;
		return;	
	}else if(taskid == 6){
		cout<<"---------------------------------------------------------------------"<<endl;
		char write_file_path[256] = { "../dst_pic/cgra_alg6_func_d3_1_data.raw" };
		cout<<"TASK["<<taskid<<"] :write "<< write_file_path <<" BEGIN"<<endl;
		BASEADDR result_base = RES_D3_1_DATA;
		SIZE result_size = RES_D3_1_DATA_SIZE;
		FILE *fp = NULL;
		fopen_s(&fp, write_file_path, "wb");
		if (fp == NULL)
		{
			cout<<"failed to open file:"<<write_file_path<<endl;
			pause();//pause();//system("pause");
			fclose(fp);
			return;
		}
		else {
			for (int i = 0; i < (int)result_size; i++)
			{
					DATAWIDTH_0 write_addr;
					write_addr = result_base + i*sizeof(unsigned short);
					unsigned short temp = *(unsigned short*)((debug)->addr_map(write_addr, sizeof(unsigned short)));
					fwrite(&temp, sizeof(unsigned short), 1, fp);
					//if(i<10) {cout<<"write to file: "<<write_file_path<<", addr("<<dec<<write_addr<<"), data("<<dec<<temp<<")"<<endl;}
			}
		}
		fclose(fp);
		cout<<"TASK["<<taskid<<"] :write "<< write_file_path <<" END"<<endl;
		cout<<"---------------------------------------------------------------------"<<endl;
		return;	
	}else if(taskid == 7){
		cout<<"---------------------------------------------------------------------"<<endl;
		char write_file_path[256] = { "../dst_pic/cgra_alg6_func_d3_2_data.raw" };
		cout<<"TASK["<<taskid<<"] :write "<< write_file_path <<" BEGIN"<<endl;
		BASEADDR result_base = RES_D3_2_DATA;
		SIZE result_size = RES_D3_2_DATA_SIZE;
		FILE *fp = NULL;
		fopen_s(&fp, write_file_path, "wb");
		if (fp == NULL)
		{
			cout<<"failed to open file:"<<write_file_path<<endl;
			pause();//pause();//system("pause");
			fclose(fp);
			return;
		}
		else {
			for (int i = 0; i < (int)result_size; i++)
			{
					DATAWIDTH_0 write_addr;
					write_addr = result_base + i*sizeof(unsigned short);
					unsigned short temp = *(unsigned short*)((debug)->addr_map(write_addr, sizeof(unsigned short)));
					fwrite(&temp, sizeof(unsigned short), 1, fp);
					//if(i<10) {cout<<"write to file: "<<write_file_path<<", addr("<<dec<<write_addr<<"), data("<<dec<<temp<<")"<<endl;}
			}
		}
		fclose(fp);
		cout<<"TASK["<<taskid<<"] :write "<< write_file_path <<" END"<<endl;
		cout<<"---------------------------------------------------------------------"<<endl;
		return;	
	}else if(taskid == 8){
		cout<<"---------------------------------------------------------------------"<<endl;
		char write_file_path[256] = { "../dst_pic/cgra_alg6_func_d3_3_data.raw" };
		cout<<"TASK["<<taskid<<"] :write "<< write_file_path <<" BEGIN"<<endl;
		BASEADDR result_base = RES_D3_3_DATA;
		SIZE result_size = RES_D3_3_DATA_SIZE;
		FILE *fp = NULL;
		fopen_s(&fp, write_file_path, "wb");
		if (fp == NULL)
		{
			cout<<"failed to open file:"<<write_file_path<<endl;
			pause();//pause();//system("pause");
			fclose(fp);
			return;
		}
		else {
			for (int i = 0; i < (int)result_size; i++)
			{
					DATAWIDTH_0 write_addr;
					write_addr = result_base + i*sizeof(unsigned short);
					unsigned short temp = *(unsigned short*)((debug)->addr_map(write_addr, sizeof(unsigned short)));
					fwrite(&temp, sizeof(unsigned short), 1, fp);
					//if(i<10) {cout<<"write to file: "<<write_file_path<<", addr("<<dec<<write_addr<<"), data("<<dec<<temp<<")"<<endl;}
			}
		}
		fclose(fp);
		cout<<"TASK["<<taskid<<"] :write "<< write_file_path <<" END"<<endl;
		cout<<"---------------------------------------------------------------------"<<endl;
		return;	
	}else if(taskid == 9){
		cout<<"---------------------------------------------------------------------"<<endl;
		char write_file_path[256] = { "../dst_pic/cgra_alg6_func_d3_2_dst_data.raw" };
		cout<<"TASK["<<taskid<<"] :write "<< write_file_path <<" BEGIN"<<endl;
		BASEADDR result_base = RES_D3_2_DST_DATA;
		SIZE result_size = RES_D3_2_DST_DATA_SIZE;
		FILE *fp = NULL;
		fopen_s(&fp, write_file_path, "wb");
		if (fp == NULL)
		{
			cout<<"failed to open file:"<<write_file_path<<endl;
			pause();//pause();//system("pause");
			fclose(fp);
			return;
		}
		else {
			for (int i = 0; i < (int)result_size; i++)
			{
					DATAWIDTH_0 write_addr;
					write_addr = result_base + i*sizeof(unsigned short);
					unsigned short temp = *(unsigned short*)((debug)->addr_map(write_addr, sizeof(unsigned short)));
					fwrite(&temp, sizeof(unsigned short), 1, fp);
					//if(i<10) {cout<<"write to file: "<<write_file_path<<", addr("<<dec<<write_addr<<"), data("<<dec<<temp<<")"<<endl;}
			}
		}
		fclose(fp);
		cout<<"TASK["<<taskid<<"] :write "<< write_file_path <<" END"<<endl;

		char write_file_path1[256] = { "../dst_pic/alg6_func_d3_3_dst_data.raw" };
		cout<<"TASK["<<taskid<<"] :write "<< write_file_path1 <<" BEGIN"<<endl;
		result_base = RES_D3_3_DST_DATA;
		result_size = RES_D3_3_DST_DATA_SIZE;

		fopen_s(&fp, write_file_path1, "wb");
		if (fp == NULL)
		{
			cout<<"failed to open file:"<<write_file_path1<<endl;
			pause();//pause();//system("pause");
			fclose(fp);
			return;
		}
		else {
			for (int i = 0; i < (int)result_size; i++)
			{
					DATAWIDTH_0 write_addr;
					write_addr = result_base + i*sizeof(unsigned short);
					unsigned short temp = *(unsigned short*)((debug)->addr_map(write_addr, sizeof(unsigned short)));
					fwrite(&temp, sizeof(unsigned short), 1, fp);
					//if(i<10) {cout<<"write to file: "<<write_file_path1<<", addr("<<dec<<write_addr<<"), data("<<dec<<temp<<")"<<endl;}
			}
		}
		fclose(fp);
		cout<<"TASK["<<taskid<<"] :write "<< write_file_path1 <<" END"<<endl;
		cout<<"---------------------------------------------------------------------"<<endl;
		return;	
	
	}else if(taskid == 10)
	{
		cout<<"---------------------------------------------------------------------"<<endl;
		char write_file_path[256] = { "../dst_pic/cgra_alg6_func_src_d3_output.raw" };
		cout<<"TASK["<<taskid<<"] :write "<< write_file_path <<" BEGIN"<<endl;
		BASEADDR result_base = RES_SRC_D3_DATA;
		SIZE result_size = RES_SRC_D3_DATA_SIZE;
		FILE *fp = NULL;
		fopen_s(&fp, write_file_path, "wb");
		if (fp == NULL)
		{
			cout<<"failed to open file:"<<write_file_path<<endl;
			pause();//pause();//system("pause");
			fclose(fp);
			return;
		}
		else {
			for (int i = 0; i < (int)result_size; i++)
			{
					DATAWIDTH_0 write_addr;
					write_addr = result_base + i*sizeof(unsigned short);
					unsigned short temp = *(unsigned short*)((debug)->addr_map(write_addr, sizeof(unsigned short)));
					fwrite(&temp, sizeof(unsigned short), 1, fp);
			}
		}
		fclose(fp);
		cout<<"TASK["<<taskid<<"] :write "<< write_file_path <<" END"<<endl;

		char write_file_path1[256] = { "../dst_pic/cgra_alg6_func_d4_dst_output.raw" };
		cout<<"TASK["<<taskid<<"] :write "<< write_file_path1 <<" BEGIN"<<endl;
		result_base = RES_D4_DST_DATA;
		result_size = RES_D4_DST_DATA_SIZE;

		fopen_s(&fp, write_file_path1, "wb");
		if (fp == NULL)
		{
			cout<<"failed to open file:"<<write_file_path1<<endl;
			pause();//pause();//system("pause");
			fclose(fp);
			return;
		}
		else {
			for (int i = 0; i < (int)result_size; i++)
			{
					DATAWIDTH_0 write_addr;
					write_addr = result_base + i*sizeof(unsigned short);
					unsigned short temp = *(unsigned short*)((debug)->addr_map(write_addr, sizeof(unsigned short)));
					fwrite(&temp, sizeof(unsigned short), 1, fp);
			}
		}
		fclose(fp);
		cout<<"TASK["<<taskid<<"] :write "<< write_file_path1 <<" END"<<endl;
		cout<<"---------------------------------------------------------------------"<<endl;
		return;
	}else{
		return;
	}
}

void perf_to_file(char* filename, DebugParam_t *debug){
	cout<<"writing simulation result to "<<filename<<endl;
    std::ofstream ofs;
	ofs.open(filename,ios::out | ios::app);
    if(!ofs){
        cout<<"Error can't open debug path"<<endl;
    }
	assert(ofs);
	int32_t total_powerestimate_corelogic = 0;
	for(int i = 0; i < (int)debug->perf.size(); i++){
		ofs<<std::setw(32)<<std::setiosflags(ios::left)<<"task_id:"							<<debug->perf[i].task_id<<endl;
		ofs<<std::setw(32)<<std::setiosflags(ios::left)<<"execution_cycle:"					<<debug->perf[i].execution_cycle				<<endl;	
		ofs<<std::setw(32)<<std::setiosflags(ios::left)<<"idle_pe_num:"						<<debug->perf[i].idle_pe_num					<<endl;
		ofs<<std::setw(32)<<std::setiosflags(ios::left)<<"active_pe_num:"					<<debug->perf[i].active_pe_num					<<endl;
		ofs<<std::setw(32)<<std::setiosflags(ios::left)<<"operation_write_immreg:"			<<debug->perf[i].operation_write_immreg			<<endl;
		ofs<<std::setw(32)<<std::setiosflags(ios::left)<<"memory_load_count:"				<<debug->perf[i].memory_load_count				<<endl;
		ofs<<std::setw(32)<<std::setiosflags(ios::left)<<"memory_store_count:"				<<debug->perf[i].memory_store_count				<<endl;
		ofs<<std::setw(32)<<std::setiosflags(ios::left)<<"lsu_load_count:"					<<debug->perf[i].lsu_load_count					<<endl;
		ofs<<std::setw(32)<<std::setiosflags(ios::left)<<"lsu_store_count:"					<<debug->perf[i].lsu_store_count				<<endl;
		ofs<<std::setw(32)<<std::setiosflags(ios::left)<<"operation_lessthan:"				<<debug->perf[i].operation_lessthan				<<endl;
		ofs<<std::setw(32)<<std::setiosflags(ios::left)<<"operation_lessthanequal:"			<<debug->perf[i].operation_lessthanequal		<<endl;
		ofs<<std::setw(32)<<std::setiosflags(ios::left)<<"operation_equal:"					<<debug->perf[i].operation_equal				<<endl;
		ofs<<std::setw(32)<<std::setiosflags(ios::left)<<"operation_equalone:"				<<debug->perf[i].operation_equalone				<<endl;
		ofs<<std::setw(32)<<std::setiosflags(ios::left)<<"operation_read_localreg:"			<<debug->perf[i].operation_read_localreg		<<endl;
		ofs<<std::setw(32)<<std::setiosflags(ios::left)<<"operation_read_immreg:"			<<debug->perf[i].operation_read_immreg			<<endl;
		ofs<<std::setw(32)<<std::setiosflags(ios::left)<<"operation_read_globalreg:"		<<debug->perf[i].operation_read_globalreg		<<endl;
		ofs<<std::setw(32)<<std::setiosflags(ios::left)<<"operation_read_peinterconnect:"	<<debug->perf[i].operation_read_peinterconnect	<<endl;
		ofs<<std::setw(32)<<std::setiosflags(ios::left)<<"operation_write_localreg:"		<<debug->perf[i].operation_write_localreg		<<endl;
		ofs<<std::setw(32)<<std::setiosflags(ios::left)<<"operation_write_globalreg:"		<<debug->perf[i].operation_write_globalreg		<<endl;
		ofs<<std::setw(32)<<std::setiosflags(ios::left)<<"operation_write_peinterconnect:"	<<debug->perf[i].operation_write_peinterconnect	<<endl;
		ofs<<std::setw(32)<<std::setiosflags(ios::left)<<"operation_arith_sadd:"			<<debug->perf[i].operation_arith_sadd			<<endl;
		ofs<<std::setw(32)<<std::setiosflags(ios::left)<<"operation_arith_ssub:"			<<debug->perf[i].operation_arith_ssub			<<endl;
		ofs<<std::setw(32)<<std::setiosflags(ios::left)<<"operation_arith_sabs:"			<<debug->perf[i].operation_arith_sabs			<<endl;
		ofs<<std::setw(32)<<std::setiosflags(ios::left)<<"operation_arith_neg:"				<<debug->perf[i].operation_arith_neg			<<endl;
		ofs<<std::setw(32)<<std::setiosflags(ios::left)<<"operation_arith_smul:"			<<debug->perf[i].operation_arith_smul			<<endl;
		ofs<<std::setw(32)<<std::setiosflags(ios::left)<<"operation_arith_smac:"			<<debug->perf[i].operation_arith_smac			<<endl;
		ofs<<std::setw(32)<<std::setiosflags(ios::left)<<"operation_arith_smod:"			<<debug->perf[i].operation_arith_smod			<<endl;
		ofs<<std::setw(32)<<std::setiosflags(ios::left)<<"operation_logic_and:"				<<debug->perf[i].operation_logic_and			<<endl;
		ofs<<std::setw(32)<<std::setiosflags(ios::left)<<"operation_logic_or:"				<<debug->perf[i].operation_logic_or				<<endl;
		ofs<<std::setw(32)<<std::setiosflags(ios::left)<<"operation_logic_not:"				<<debug->perf[i].operation_logic_not			<<endl;
		ofs<<std::setw(32)<<std::setiosflags(ios::left)<<"operation_logic_xor:"				<<debug->perf[i].operation_logic_xor			<<endl;
		ofs<<std::setw(32)<<std::setiosflags(ios::left)<<"operation_shifter_sll:"			<<debug->perf[i].operation_shifter_sll			<<endl;
		ofs<<std::setw(32)<<std::setiosflags(ios::left)<<"operation_shifter_sra:"			<<debug->perf[i].operation_shifter_sra			<<endl;
		ofs<<std::setw(32)<<std::setiosflags(ios::left)<<"operation_shifter_srl:"			<<debug->perf[i].operation_shifter_srl			<<endl;
		ofs<<endl;
		//--------------------------------------------
		int32_t powerestimate_corelogic = 0;
		powerestimate_corelogic += debug->perf[i].operation_write_immreg 		*NORMALIZED_POW_WRITE_REG;		
		powerestimate_corelogic += debug->perf[i].memory_load_count				*NORMALIZED_POW_MEM_READ
		powerestimate_corelogic += debug->perf[i].memory_store_count			*NORMALIZED_POW_MEM_WRITE	
		powerestimate_corelogic += debug->perf[i].lsu_load_count				*NORMALIZED_POW_LSU_LOAD	
		powerestimate_corelogic += debug->perf[i].lsu_store_count				*NORMALIZED_POW_LSU_STORE
		powerestimate_corelogic += debug->perf[i].operation_lessthan			*NORMALIZED_POW_LESSTHAN	
		powerestimate_corelogic += debug->perf[i].operation_lessthanequal		*NORMALIZED_POW_LESSTHANEQUAL
		powerestimate_corelogic += debug->perf[i].operation_equal				*NORMALIZED_POW_EQU
		powerestimate_corelogic += debug->perf[i].operation_equalone			*NORMALIZED_POW_EQUONE	
		powerestimate_corelogic += debug->perf[i].operation_read_localreg		*NORMALIZED_POW_READ_REG
		powerestimate_corelogic += debug->perf[i].operation_read_immreg			*NORMALIZED_POW_READ_REG
		powerestimate_corelogic += debug->perf[i].operation_read_globalreg		*NORMALIZED_POW_READ_REG
		powerestimate_corelogic += debug->perf[i].operation_read_peinterconnect	*NORMALIZED_POW_READ_FROM_PE
		powerestimate_corelogic += debug->perf[i].operation_write_localreg		*NORMALIZED_POW_WRITE_REG
		powerestimate_corelogic += debug->perf[i].operation_write_globalreg		*NORMALIZED_POW_WRITE_REG
		powerestimate_corelogic += debug->perf[i].operation_write_peinterconnect*NORMALIZED_POW_WRITE_TO_PE	
		powerestimate_corelogic += debug->perf[i].operation_arith_sadd			*NORMALIZED_POW_SADD
		powerestimate_corelogic += debug->perf[i].operation_arith_ssub			*NORMALIZED_POW_SSUB
		powerestimate_corelogic += debug->perf[i].operation_arith_sabs			*NORMALIZED_POW_SABS
		powerestimate_corelogic += debug->perf[i].operation_arith_neg			*NORMALIZED_POW_NEG
		powerestimate_corelogic += debug->perf[i].operation_arith_smul			*NORMALIZED_POW_SMUL
		powerestimate_corelogic += debug->perf[i].operation_arith_smac			*NORMALIZED_POW_SMAC
		powerestimate_corelogic += debug->perf[i].operation_arith_smod			*NORMALIZED_POW_SMOD
		powerestimate_corelogic += debug->perf[i].operation_logic_and			*NORMALIZED_POW_AND
		powerestimate_corelogic += debug->perf[i].operation_logic_or			*NORMALIZED_POW_OR	
		powerestimate_corelogic += debug->perf[i].operation_logic_not			*NORMALIZED_POW_NOT
		powerestimate_corelogic += debug->perf[i].operation_logic_xor			*NORMALIZED_POW_XOR
		powerestimate_corelogic += debug->perf[i].operation_shifter_sll			*NORMALIZED_POW_SLL
		powerestimate_corelogic += debug->perf[i].operation_shifter_sra			*NORMALIZED_POW_SRA
		powerestimate_corelogic += debug->perf[i].operation_shifter_srl			*NORMALIZED_POW_SRL
		ofs<<"powerestimate_corelogic:"<<powerestimate_corelogic<<endl;
		total_powerestimate_corelogic+=powerestimate_corelogic;
	}
	ofs<<"---------------------------------------------------"<<endl;
	ofs<<"total_powerestimate_corelogic:"<<total_powerestimate_corelogic<<endl;
    ofs.close();
}

void isp_main()
{
	FILE* fp = NULL;
	unsigned int i, j,c;
	unsigned int height = SIZE_D1_H;
	unsigned int width = SIZE_D1_W;
	char src_path[256] = { "../test_pic/test_pic.raw" };
	fopen_s(&fp, src_path, "rb");
	if (fp == NULL) {
		logi("can not open the testimage\n");
		pause();//system("pause");
		return;
	}
	else {
		logi("read testimage OK\n");
	}
	unsigned short* ptr = NULL;
	ptr = (unsigned short*)malloc(sizeof(unsigned short));
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			size_t sizeRead = fread(ptr, 2, 1, fp);
			if(sizeRead != 1) {logi("fread error! \n"); pause();} 
			src_d1_data[i][j] = *ptr;
			//ptr_temp++;
		}
	}
	fclose(fp);
	free(ptr);
	ptr = NULL;

	printf("processing alg0_func\r\n");
	alg0_func(&src_d1_data[0][0], &dst_d1_data[0][0], width, height);
	
	

	logi("write the output of alg0_func to file alg0_func_output.raw\n");
	char alg0_dst_path[256]= {"../dst_pic/alg0_func_output.raw"};
	fopen_s(&fp, alg0_dst_path, "wb");
	if(fp==NULL)
	{
		logi("can not write the alg0_func_output\n");
		pause();//system("pause");
		return;
	}
	else{
		logi("read alg0_func_output file pointer OK\n");
		for(i = 0; i < SIZE_D1_H; i++)
		{
			for(j = 0 ; j < SIZE_D1_W; j++)
			{
				fwrite(&dst_d1_data[i][j],2,1,fp);
			}
		}
	}
	fclose(fp);
	printf("processing alg1_func\r\n");
	alg1_func2(&out_data[0][0], &dst_d1_data[0][0]);
	logi("write the output of alg1_func2 to file alg1_func2_output.raw\n");
	char alg1_func2_dst_path[256]= {"../dst_pic/alg1_func2_output.raw"};
	fopen_s(&fp, alg1_func2_dst_path, "wb");
	if(fp==NULL)
	{
		logi("can not write the alg1_func2_output\n");
		pause();//system("pause");
		return;
	}
	else{
		logi("read alg1_func2_output file pointer OK\n");
		for(i = 0; i < GRID_H; i++)
		{
			for(j = 0 ; j < GRID_W; j++)
			{
				fwrite(&out_data[i][j],4,1,fp);
			}
		}
		
	}
	fclose(fp);
	int max = out_data[0][0];
	for (i = 0; i < GRID_H; i++) {
		for (int j = 0; j < GRID_W; j++) {
			if (out_data[i][j] > max) max = out_data[i][j];
		}
	}
	if (max > 20000) {
		si = 1.6;
	}
	else {
		si = 2.0;
	}
	printf("processing alg2_func\r\n");
	alg2_func(&dst_d1_data[0][0], &src_d1_data[0][0], width, height, si);
	logi("write the output of alg2_func to file alg2_func_output.raw\n");
	char alg2_func_dst_path[256]= {"../dst_pic/alg2_func_output.raw"};
	fopen_s(&fp, alg2_func_dst_path, "wb");
	if(fp==NULL)
	{
		logi("can not write the alg2_func_output\n");
		fclose(fp);
		pause();//system("pause");
		return;
	}
	else{
		logi("read alg2_func_output file pointer OK\n");
		for(i = 0; i < SIZE_D1_H; i++)
		{
			for(j = 0 ; j < SIZE_D1_W; j++)
			{
				fwrite(&src_d1_data[i][j],2,1,fp);
			}
		}
		
	}
	fclose(fp);
	printf("processing alg3_func\r\n");
	alg3_func(&src_d1_data[0][0], &dst_d1_data[0][0], width, height);
	logi("write the output of alg3_func to file alg3_func_output.raw\n");
	char alg3_func_dst_path[256]= {"../dst_pic/alg3_func_output.raw"};
	fopen_s(&fp, alg3_func_dst_path, "wb");
	if(fp==NULL)
	{
		logi("can not write the alg3_func_output\n");
		pause();//system("pause");
		fclose(fp);
		return;
	}
	else{
		logi("read alg3_func_output file pointer OK\n");
		for(i = 0; i < SIZE_D1_H; i++)
		{
			for(j = 0 ; j < SIZE_D1_W; j++)
			{
				fwrite(&dst_d1_data[i][j],2,1,fp);
			}
		}
	}
	fclose(fp);
	printf("processing alg4_func\r\n");
	alg4_func(&dst_d1_data[0][0], &src_d1_data[0][0], width, height);
	logi("write the output of alg4_func to file alg4_func_output.raw\n");
	char alg4_func_dst_path[256]= {"../dst_pic/alg4_func_output.raw"};
	fopen_s(&fp, alg4_func_dst_path, "wb");
	if(fp==NULL)
	{
		logi("can not write the alg4_func_output\n");
		pause();//system("pause");
		return;
	}
	else{
		logi("read alg4_func_output file pointer OK\n");
		for(i = 0; i < SIZE_D1_H; i++)
		{
			for(j = 0 ; j < SIZE_D1_W; j++)
			{
				fwrite(&src_d1_data[i][j],2,1,fp);
			}
		}
		fclose(fp);
	}
	printf("processing alg5_func\r\n");
	alg5_func(src_d1_data, src_d2_data);
	logi("write the output of alg5_func to file alg5_func_output.raw\n");
	char alg5_func_dst_path[256]= {"../dst_pic/alg5_func_output.raw"};
	fopen_s(&fp, alg5_func_dst_path, "wb");
	if(fp==NULL)
	{
		logi("can not write the alg5_func_output\n");
		pause();//system("pause");
		return;
	}
	else{
		logi("read alg5_func_output file pointer OK\n");
		for(i = 0; i < SIZE_D1_H; i++)
		{
			for(j = 0 ; j < SIZE_D1_W; j++)
			{
				for(c = 0 ; c < 3 ; c++)
				{
					fwrite(&src_d2_data[i][j][c],2,1,fp);
				}	
			}
		}
	fclose(fp);
	}
	printf("processing alg1_func1\r\n");
	alg1_func1(dst_d2_data, src_d2_data);
	logi("writing the output of alg1_func1 to project/dst_pic/alg1_func1_output.raw\nS");
	char alg1_func1_dst_path[256] = { "../dst_pic/alg1_func1_output.raw" };
	fopen_s(&fp, alg1_func1_dst_path, "wb");
	if (fp == NULL) {
		logi("can not write the alg1_func1_output\n");
		pause();//system("pause");
		return;
	}
	else{
		logi("read alg1_func1_output file pointer OK\n");
		for (int i = 0; i < D2_HEIGHT_OUT; i++){
			for (int j = 0; j < D2_WIDTH_OUT; j++) {
				 for (int c = 0; c < 3; c++) {
					fwrite(&dst_d2_data[i][j][c], 2, 1, fp);
				}
			}
		}	
	}
	fclose(fp);
    printf("processing alg6_func\r\n");
	alg6_func(src_d3_data, d4_dst,dst_d2_data);
	char alg6_func_dst_path1[256] = { "../dst_pic/alg6_func_src_d3_output.raw" };
	fopen_s(&fp, alg6_func_dst_path1, "wb");
	if (fp == NULL) {
		logi("can not write the image1\n");
		pause();//system("pause");
		return ;
	}
	for (i = 0; i < width / 2 * height / 2 * 2; i++) {
		fwrite(&src_d3_data[i], 2, 1, fp);
	}
	fclose(fp);

	char alg6_func_dst_path2[256] = { "../dst_pic/alg6_func_d4_dst_output.raw" };
	fopen_s(&fp, alg6_func_dst_path2, "wb");
	if (fp == NULL) {
		logi("can not write the image1\n");
		pause();//system("pause");
		return ;
	}
	for (i = 0; i < SIZE_D1_H*SIZE_D1_W; i++) {
		fwrite(&d4_dst[i], 2, 1, fp);
	}
	fclose(fp);
	printf("processing alg7_func\r\n");
	alg7_func(d4_dst, dst_d3_data);
	logi("pls input image2 path for save:");
	char dst_path2[256] = { "../dst_pic/alg7_func_dst_d3_output.raw" };
	fopen_s(&fp, dst_path2, "wb");
	if (fp == NULL) {
		logi("can not write the image2\n");
		pause();//system("pause");
		return;
	}
	for (i = 0; i < width/2*height/2*2; i++) {
		fwrite(&dst_d3_data[i], 2, 1, fp);
	}
	fclose(fp);
	//std::cout << "结束了" << std::endl;
	//system("pause");//为了让代码运行结束后不会一闪就关
	return;
}

void verify_result(int taskid)
{
	unsigned short (*c1_from_algorithm) [SIZE_D1_W/2];
	unsigned short (*c2_from_algorithm) [SIZE_D1_W/2];
	unsigned short (*c3_from_algorithm) [SIZE_D1_W/2];
	unsigned short (*c4_from_algorithm) [SIZE_D1_W/2];
	
	if(taskid == 0){
		c1_from_algorithm = (unsigned short(*)[SIZE_D1_W/2])malloc(SIZE_D1_H/2 * sizeof(unsigned short[SIZE_D1_W/2]));
		c2_from_algorithm = (unsigned short(*)[SIZE_D1_W/2])malloc(SIZE_D1_H/2 * sizeof(unsigned short[SIZE_D1_W/2]));
		cout<<"---------------------------------------------------------------------"<<endl;
		cout<<"TASK["<<dec<<taskid<<"] verify c1/c2 result_to_file BEGIN"<<endl;
		FILE* fp = NULL;
		int mismatchcount = 0;
		int matchcount = 0;
		//read isp output - c1
		char src_c1_path[256] = { "../dst_pic/isp_alg5_func_c1_output.raw" };
		logi("reading alg5 c1 output reference : %s\n",src_c1_path);
		fopen_s(&fp, src_c1_path, "rb");
		if (fp == NULL) {
			logi("can not open the file path: %s\n", src_c1_path);
			pause();//system("pause");
			return;
		}
		unsigned short* ptr = NULL;
		unsigned short readresult;
		ptr = (unsigned short*)malloc(sizeof(unsigned short));
		
		for (int i = 0; i < SIZE_D1_H/2; i++) {
			for (int j = 0; j < SIZE_D1_W/2; j++) {	
					size_t sizeRead = fread(ptr, 2, 1, fp);
					if(sizeRead != 1) {logi("fread error! \n"); pause();} 
					*(*(c1_from_algorithm+i)+j) = *ptr;
			}
		}	
		fclose(fp);
		free(ptr);
		ptr = NULL;
		//read isp output -c2 
		char src_c2_path[256] = { "../dst_pic/isp_alg5_func_c2_output.raw" };
		logi("reading alg5 c2 output reference : %s\n",src_c2_path);
		fopen_s(&fp, src_c2_path, "rb");
		if (fp == NULL) 
		{
			logi("can not open the file path: %s\n", src_c2_path);
			pause();//system("pause");
			return;
		}
		unsigned short* ptr_c2;
		ptr_c2 = (unsigned short*)malloc(sizeof(unsigned short));

		for (int i = 0; i < SIZE_D1_H/2; i++) 
		{
			for (int j = 0; j < SIZE_D1_W/2; j++) 
			{
					size_t sizeRead = fread(ptr_c2, 2, 1, fp);
					if(sizeRead != 1) {logi("fread error! \n"); pause();} 
					unsigned short temp = *ptr_c2;
					*(*(c2_from_algorithm+i)+j) = temp;
			}
		}	
		fclose(fp);
		free(ptr_c2);
		ptr_c2 = NULL;
		//read CGRA output -c1
		char src_cgra_c1_path[256] = { "../dst_pic/cgra_alg5_func_c1_output.raw" };
		logi("reading simulation result: %s\n",src_cgra_c1_path);
		fopen_s(&fp, src_cgra_c1_path, "rb");
		if (fp == NULL) {
			logi("can not open the file path: %s\n",src_cgra_c1_path);
			pause();//system("pause");
			return;
		}
		unsigned short* ptr1 = NULL;
		ptr1 = (unsigned short*)malloc(sizeof(unsigned short));
		for (int i = 0; i < SIZE_D1_H/2; i++) {
			for (int j = 0; j < SIZE_D1_W/2; j++) {
				
					size_t sizeRead = fread(ptr1, 2, 1, fp);
					if(sizeRead != 1) {logi("fread error! \n"); pause();} 
					readresult = *ptr1;
					if(c1_from_algorithm[i][j]!=readresult)
					{
						if(mismatchcount < 20 )
						cout <<"mismatch result Error: isp reference("<<src_c1_path<<")["<<std::dec<<i<<"][" \
						<<std::dec<<j<<"]: "<<*(*(c1_from_algorithm+i)+j) \
						<<" mismatch cgra result("<<src_cgra_c1_path<<")["<<std::dec<<i<<"]["<<std::dec<<j<<"]:" \
						<<std::dec<<readresult<<", mismatch count ="  \
						<<mismatchcount<<endl;
						mismatchcount++;
					}else{
						matchcount++;
					}
			}
		}	
		fclose(fp);
		free(ptr1);
		ptr1 = NULL;
		free(c1_from_algorithm);
		c1_from_algorithm = NULL;
		cout <<"Compare between reference(" <<src_c1_path<< ") and simulation result("<<src_cgra_c1_path<<	\
		")  : mismatch count = "<<mismatchcount<<", match count ="<<matchcount<<endl;

		//read CGRA output -c2
		mismatchcount = 0;
		matchcount = 0;
		char src_cgra_c2_path[256] = { "../dst_pic/cgra_alg5_func_c2_output.raw" };
		logi("reading simulation result: %s\n",src_cgra_c2_path);
		fopen_s(&fp, src_cgra_c2_path, "rb");
		if (fp == NULL) {
			logi("can not open the file path: %s\n",src_cgra_c2_path);
			pause();//system("pause");
			return;
		}
		ptr1 = (unsigned short*)malloc(sizeof(unsigned short));
		 for (int i = 0; i < SIZE_D1_H/2; i++) 
		 {
		 	for (int j = 0; j < SIZE_D1_W/2; j++) 
			{
		 			size_t sizeRead = fread(ptr1, 2, 1, fp);
					if(sizeRead != 1) {logi("fread error! \n"); pause();} 
		 			readresult = *ptr1;
					if(c2_from_algorithm[i][j]!=readresult)
					{
						if(mismatchcount < 20 ){
							cout <<"mismatch result Error: isp reference("<<src_c2_path<<")["<<std::dec<<i<<"][" \
						<<std::dec<<j<<"]: "<<*(*(c2_from_algorithm+i)+j) \
						<<" mismatch cgra result("<<src_cgra_c2_path<<")["<<std::dec<<i<<"]["<<std::dec<<j<<"]:" \
						<<std::dec<<readresult<<", mismatch count ="  \
						<<mismatchcount<<endl;
						}
						mismatchcount++;
					}else{
						matchcount++;
					}
		 	}
		 }	
		cout <<"Compare between reference(" <<src_c2_path<< ") and simulation result("<<src_cgra_c2_path<<	\
		")  : mismatch count = "<<mismatchcount<<", match count ="<<matchcount<<endl;
		fclose(fp);
		free(ptr1);
		free(c2_from_algorithm);
		c2_from_algorithm = NULL;
		ptr1 = NULL;
		cout<<"TASK["<<dec<<taskid<<"] verify c1/c2 result_to_file END"<<endl;
		cout<<"---------------------------------------------------------------------"<<endl;
		
		return;
	}else if(taskid == 1){
		c3_from_algorithm = (unsigned short(*)[SIZE_D1_W/2])malloc(SIZE_D1_H/2 * sizeof(unsigned short[SIZE_D1_W/2]));
		c4_from_algorithm = (unsigned short(*)[SIZE_D1_W/2])malloc(SIZE_D1_H/2 * sizeof(unsigned short[SIZE_D1_W/2]));
		cout<<"---------------------------------------------------------------------"<<endl;
		cout<<"TASK["<<dec<<taskid<<"] verify c3/c4 result_to_file BEGIN"<<endl;
		FILE* fp = NULL;
		int mismatchcount = 0;
		int matchcount = 0;

		//read isp output - c3
		char src_c3_path[256] = { "../dst_pic/isp_alg5_func_c3_output.raw" };
		logi("reading alg5 c3 output reference : %s\n",src_c3_path);
		fopen_s(&fp, src_c3_path, "rb");
		if (fp == NULL) {
			logi("can not open the file path: %s\n", src_c3_path);
			pause();//system("pause");
			return;
		}
		unsigned short* ptr = NULL;
		unsigned short readresult;
		ptr = (unsigned short*)malloc(sizeof(unsigned short));
		
		for (int i = 0; i < SIZE_D1_H/2; i++) {
			for (int j = 0; j < SIZE_D1_W/2; j++) {	
					size_t sizeRead = fread(ptr, 2, 1, fp);
					if(sizeRead != 1) {logi("fread error! \n"); pause();} 
					*(*(c3_from_algorithm+i)+j) = *ptr;
			}
		}	
		fclose(fp);
		free(ptr);
		ptr = NULL;

		//read isp output -c4 
		char src_c4_path[256] = { "../dst_pic/isp_alg5_func_c4_output.raw" };
		logi("reading alg5 c4 output reference : %s\n",src_c4_path);
		fopen_s(&fp, src_c4_path, "rb");
		if (fp == NULL) 
		{
			logi("can not open the file path: %s\n", src_c4_path);
			pause();//system("pause");
			return;
		}

		unsigned short* ptr_c4;
		ptr_c4 = (unsigned short*)malloc(sizeof(unsigned short));

		for (int i = 0; i < SIZE_D1_H/2; i++) 
		{
			for (int j = 0; j < SIZE_D1_W/2; j++) 
			{
					size_t sizeRead = fread(ptr_c4, 2, 1, fp);
					if(sizeRead != 1) {logi("fread error! \n"); pause();} 
					unsigned short temp = *ptr_c4;
					*(*(c4_from_algorithm+i)+j) = temp;
			}
		}	
		// unsigned short temp = c4_from_algorithm[9][9];
		// cout<<temp<<endl;
		fclose(fp);
		free(ptr_c4);
		ptr_c4 = NULL;
		
		//read CGRA output -c3
		char src_cgra_c3_path[256] = { "../dst_pic/cgra_alg5_func_c3_output.raw" };
		logi("reading simulation result: %s\n",src_cgra_c3_path);
		fopen_s(&fp, src_cgra_c3_path, "rb");
		if (fp == NULL) {
			logi("can not open the file path: %s\n",src_cgra_c3_path);
			pause();//system("pause");
			return;
		}
		unsigned short* ptr1 = NULL;
		ptr1 = (unsigned short*)malloc(sizeof(unsigned short));
		for (int i = 0; i < SIZE_D1_H/2; i++) {
			for (int j = 0; j < SIZE_D1_W/2; j++) {
				
					size_t sizeRead =  fread(ptr1, 2, 1, fp);
					if(sizeRead != 1) {logi("fread error! \n"); pause();} 
					readresult = *ptr1;

					if(c3_from_algorithm[i][j]!=readresult)
					{
						if(mismatchcount < 20 ){
							cout <<"mismatch result Error: isp reference("<<src_c3_path<<")["<<std::dec<<i<<"][" \
							<<std::dec<<j<<"]: "<<*(*(c3_from_algorithm+i)+j) \
							<<" mismatch cgra result("<<src_cgra_c3_path<<")["<<std::dec<<i<<"]["<<std::dec<<j<<"]:" \
							<<std::dec<<readresult<<", mismatch count ="  \
							<<mismatchcount<<endl;
						}
						
						mismatchcount++;

					}else{
						matchcount++;
					}
					
			}
		}	
		fclose(fp);
		free(ptr1);
		ptr1 = NULL;
		free(c3_from_algorithm);
		c3_from_algorithm = NULL;
		cout <<"Compare between reference(" <<src_c3_path<< ") and simulation result("<<src_cgra_c3_path<<	\
		")  : mismatch count = "<<mismatchcount<<", match count ="<<matchcount<<endl;

		//read CGRA output -c4
		mismatchcount = 0;
		matchcount = 0;
		char src_cgra_c4_path[256] = { "../dst_pic/cgra_alg5_func_c4_output.raw" };
		logi("reading simulation result: %s\n",src_cgra_c4_path);
		fopen_s(&fp, src_cgra_c4_path, "rb");
		if (fp == NULL) {
			logi("can not open the file path: %s\n",src_cgra_c4_path);
			pause();//system("pause");
			return;
		}
		ptr1 = (unsigned short*)malloc(sizeof(unsigned short));
		 for (int i = 0; i < SIZE_D1_H/2; i++) 
		 {
		 	for (int j = 0; j < SIZE_D1_W/2; j++) 
			{
		 			size_t sizeRead =  fread(ptr1, 2, 1, fp);
					if(sizeRead != 1) {logi("fread error! \n"); pause();} 
		 			readresult = *ptr1;
					//unsigned short temp = c4_from_algorithm[i][j];
					//cout<<temp<<endl;
					if(c4_from_algorithm[i][j]!=readresult)
					{
						if(mismatchcount < 20 ){
							cout <<"mismatch result Error: isp reference("<<src_c4_path<<")["<<std::dec<<i<<"][" \
							<<std::dec<<j<<"]: "<<*(*(c4_from_algorithm+i)+j) \
							<<" mismatch cgra result("<<src_cgra_c4_path<<")["<<std::dec<<i<<"]["<<std::dec<<j<<"]:" \
							<<std::dec<<readresult<<", mismatch count ="  \
							<<mismatchcount<<endl;
						}
						mismatchcount++;
					}else{
						matchcount++;
					}
		 	}
		 }	
		cout <<"Compare between reference(" <<src_c4_path<< ") and simulation result("<<src_cgra_c4_path<<	\
		")  : mismatch count = "<<mismatchcount<<", match count ="<<matchcount<<endl;
		fclose(fp);
		free(ptr1);
		free(c4_from_algorithm);
		ptr1 = NULL;
		cout<<"TASK["<<dec<<taskid<<"] verify c3/c4 result_to_file END"<<endl;
		cout<<"---------------------------------------------------------------------"<<endl;
		return;
	}else if(taskid == 2)
	{
		cout<<"---------------------------------------------------------------------"<<endl;
		cout<<"TASK["<<dec<<taskid<<"] verify src_d2_data result_to_file BEGIN"<<endl;
		//read isp result
		FILE* fp = NULL;
		int mismatchcount = 0;
		int matchcount = 0;
		char src_path[256] = { "../dst_pic/alg5_func_output.raw" };
		logi("reading alg5 output reference : %s\n",src_path);
		fopen_s(&fp, src_path, "rb");
		if (fp == NULL) {
			logi("can not open the file path: %s\n", src_path);
			pause();//system("pause");
			return;
		}
		unsigned short* ptr = NULL;
		unsigned short readresult;
		ptr = (unsigned short*)malloc(sizeof(unsigned short));
		for (int i = 0; i < SIZE_D1_H; i++) {
			for (int j = 0; j < SIZE_D1_W; j++) {
				for (int c = 0; c < 3; c++) {
					size_t sizeRead = fread(ptr, 2, 1, fp);
					if(sizeRead != 1) {logi("fread error! \n"); pause();} 
					src_d2_data[i][j][c]=*ptr;
				}
			}
		}	
		fclose(fp);
		free(ptr);
		ptr = NULL;

		//read CGRA output 
		char src_path1[256] = { "../dst_pic/cgra_alg5_func_src_d2_data.raw" };
		logi("reading simulation result: %s\n",src_path1);
		fopen_s(&fp, src_path1, "rb");
		if (fp == NULL) {
			logi("can not open the file path: %s\n",src_path1);
			pause();//system("pause");
			return;
		}
		unsigned short* ptr1;
		ptr1 = (unsigned short*)malloc(sizeof(unsigned short));
		for (int i = 0; i < SIZE_D1_H; i++) {
			for (int j = 0; j < SIZE_D1_W; j++) {
				for (int c = 0; c < 3; c++) {
					size_t sizeRead =  fread(ptr1, 2, 1, fp);
					if(sizeRead != 1) {logi("fread error! \n"); pause();} 
					readresult = *ptr1;
					if(i % 2 == 0 && j % 2 == 0)
					{					
						if(src_d2_data[i][j][c]!=readresult)
						{
							if(mismatchcount < 20 ){
									cout <<"mismatch result Error: reference("<<src_path<<")["<<std::dec<<i<<"][" \
									<<std::dec<<j<<"]["<<std::dec<<c<<"]: "<<src_d2_data[i][j][c] \
									<<" mismatch result("<<src_path1<<")["<<std::dec<<i<<"]["<<std::dec<<j<<"]["	  \
									<<std::dec<<c<<"]:"<<std::dec<<readresult<<", mismatch count ="  \
									<<mismatchcount<<endl;
							}
							mismatchcount++;
						}else{
							matchcount++;
						}
					}
					
				}
			}
		}	
		cout <<"Compare between reference(" <<src_path<< ") and simulation result("<<src_path1<<	\
		")  : mismatch count = "<<mismatchcount<<", match count ="<<matchcount<<endl;

		cout<<"TASK["<<dec<<taskid<<"] verify src_d2_data result_to_file END"<<endl;
		cout<<"---------------------------------------------------------------------"<<endl;
		fclose(fp);
		free(ptr1);
		ptr1 = NULL;
		return;
		//------------alg5_func------------------
	}else if(taskid == 3)
	{	
		cout<<"---------------------------------------------------------------------"<<endl;
		cout<<"TASK["<<dec<<taskid<<"] verify src_d2_data result_to_file BEGIN"<<endl;
		//read isp result
		FILE* fp = NULL;
		int mismatchcount = 0;
		int matchcount = 0;
		char src_path[256] = { "../dst_pic/alg5_func_output.raw" };
		logi("reading alg5 output reference : %s\n",src_path);
		fopen_s(&fp, src_path, "rb");
		if (fp == NULL) {
			logi("can not open the file path: %s\n", src_path);
			pause();//system("pause");
			return;
		}
		unsigned short* ptr = NULL;
		unsigned short readresult;
		ptr = (unsigned short*)malloc(sizeof(unsigned short));
		for (int i = 0; i < SIZE_D1_H; i++) {
			for (int j = 0; j < SIZE_D1_W; j++) {
				for (int c = 0; c < 3; c++) {
					size_t sizeRead = fread(ptr, 2, 1, fp);
					if(sizeRead != 1) {logi("fread error! \n"); pause();} 
					src_d2_data[i][j][c]=*ptr;
				}
			}
		}	
		fclose(fp);
		free(ptr);
		ptr = NULL;

		//read CGRA output 
		char src_path1[256] = { "../dst_pic/cgra_alg5_func_src_d2_data.raw" };
		logi("reading simulation result: %s\n",src_path1);
		fopen_s(&fp, src_path1, "rb");
		if (fp == NULL) {
			logi("can not open the file path: %s\n",src_path1);
			pause();//system("pause");
			return;
		}
		unsigned short* ptr1;
		ptr1 = (unsigned short*)malloc(sizeof(unsigned short));
		for (int i = 0; i < SIZE_D1_H; i++) {
			for (int j = 0; j < SIZE_D1_W; j++) {
				for (int c = 0; c < 3; c++) {
					size_t sizeRead =  fread(ptr1, 2, 1, fp);
					if(sizeRead != 1) {logi("fread error! \n"); pause();} 
					readresult = *ptr1;
					if(( i % 2 == 0 && j % 2 == 1 ) || ( i % 2 == 1 && j % 2 == 0 ))
					{

						if(src_d2_data[i][j][c]!=readresult)
						{
							if(mismatchcount < 20 ){
									cout <<"mismatch result Error: reference("<<src_path<<")["<<std::dec<<i<<"][" \
									<<std::dec<<j<<"]["<<std::dec<<c<<"]: "<<src_d2_data[i][j][c] \
									<<" mismatch result("<<src_path1<<")["<<std::dec<<i<<"]["<<std::dec<<j<<"]["	  \
									<<std::dec<<c<<"]:"<<std::dec<<readresult<<", mismatch count ="  \
									<<mismatchcount<<endl;
							}
						
							mismatchcount++;
						}else{
							matchcount++;
						}
					}
					
				}
			}
		}	
		cout <<"Compare between reference(" <<src_path<< ") and simulation result("<<src_path1<<	\
		")  : mismatch count = "<<mismatchcount<<", match count ="<<matchcount<<endl;

		cout<<"TASK["<<dec<<taskid<<"] verify src_d2_data result_to_file END"<<endl;
		cout<<"---------------------------------------------------------------------"<<endl;
		fclose(fp);
		free(ptr1);
		ptr1 = NULL;
		return;
		//------------alg5_func------------------
	}else if(taskid == 4)
	{
		cout<<"---------------------------------------------------------------------"<<endl;
		cout<<"TASK["<<dec<<taskid<<"] verify src_d2_data result_to_file BEGIN"<<endl;
		//read isp result
		FILE* fp = NULL;
		int mismatchcount = 0;
		int matchcount = 0;
		char src_path[256] = { "../dst_pic/alg5_func_output.raw" };
		logi("reading alg5 output reference : %s\n",src_path);
		fopen_s(&fp, src_path, "rb");
		if (fp == NULL) {
			logi("can not open the file path: %s\n", src_path);
			pause();//system("pause");
			return;
		}
		unsigned short* ptr = NULL;
		unsigned short readresult;
		ptr = (unsigned short*)malloc(sizeof(unsigned short));
		for (int i = 0; i < SIZE_D1_H; i++) {
			for (int j = 0; j < SIZE_D1_W; j++) {
				for (int c = 0; c < 3; c++) {
					size_t sizeRead = fread(ptr, 2, 1, fp);
					if(sizeRead != 1) {logi("fread error! \n"); pause();} 
					src_d2_data[i][j][c]=*ptr;
				}
			}
		}	
		fclose(fp);
		free(ptr);
		ptr = NULL;

		//read CGRA output 
		char src_path1[256] = { "../dst_pic/cgra_alg5_func_src_d2_data.raw" };
		logi("reading simulation result: %s\n",src_path1);
		fopen_s(&fp, src_path1, "rb");
		if (fp == NULL) {
			logi("can not open the file path: %s\n",src_path1);
			pause();//system("pause");
			return;
		}
		unsigned short* ptr1;
		ptr1 = (unsigned short*)malloc(sizeof(unsigned short));
		for (int i = 0; i < SIZE_D1_H; i++) {
			for (int j = 0; j < SIZE_D1_W; j++) {
				for (int c = 0; c < 3; c++) {
					size_t sizeRead =  fread(ptr1, 2, 1, fp);
					if(sizeRead != 1) {logi("fread error! \n"); pause();} 
					readresult = *ptr1;
					if(( i % 2 == 1 && j % 2 == 1 ) )
					{
						if(src_d2_data[i][j][c]!=readresult)
						{
							if(mismatchcount < 20 ){
									cout <<"mismatch result Error: reference("<<src_path<<")["<<std::dec<<i<<"][" \
									<<std::dec<<j<<"]["<<std::dec<<c<<"]: "<<src_d2_data[i][j][c] \
									<<" mismatch result("<<src_path1<<")["<<std::dec<<i<<"]["<<std::dec<<j<<"]["	  \
									<<std::dec<<c<<"]:"<<std::dec<<readresult<<", mismatch count ="  \
									<<mismatchcount<<endl;
							}
						
							mismatchcount++;
						}else{
							matchcount++;
						}
					}
					
				}
			}
		}	
		cout <<"Compare between reference(" <<src_path<< ") and simulation result("<<src_path1<<	\
		")  : mismatch count = "<<mismatchcount<<", match count ="<<matchcount<<endl;

		cout<<"TASK["<<dec<<taskid<<"] verify src_d2_data result_to_file END"<<endl;
		cout<<"---------------------------------------------------------------------"<<endl;
		fclose(fp);
		free(ptr1);
		ptr1 = NULL;
		return;
		//------------alg5_func-------------------------
	}else if(taskid == 5)
	{
		cout<<"---------------------------------------------------------------------"<<endl;
		cout<<"TASK["<<dec<<taskid<<"] verify dst_d2_data result_to_file BEGIN"<<endl;
			//--------------alg1_func1---------------
			FILE* fp = NULL;
			int mismatchcount = 0;
			int matchcount = 0;
			char src_path[256] = { "../dst_pic/alg1_func1_output.raw" };
			logi("reading alg1 output reference : %s\n",src_path);
			fopen_s(&fp, src_path, "rb");
			if (fp == NULL) {
				logi("can not open the file path: %s\n", src_path);
				pause();//system("pause");
				return;
			}
			unsigned short* ptr = NULL;
			unsigned short readresult;
			ptr = (unsigned short*)malloc(sizeof(unsigned short));
			unsigned short* ptr_temp = NULL;
			ptr_temp = ptr;
			for (int i = 0; i < D2_HEIGHT_OUT; i++) {
				for (int j = 0; j < D2_WIDTH_OUT; j++) {
					for (int c = 0; c < 3; c++) {
						size_t sizeRead = fread(ptr_temp, 2, 1, fp);
						if(sizeRead != 1) {logi("fread error! \n"); pause();} 
						dst_d2_data[i][j][c]=*ptr_temp;
					}
				}
			}	
			fclose(fp);
			free(ptr);
			ptr = NULL;
			ptr_temp = NULL;
			//read CGRA output 

			char src_path1[256] = { "../dst_pic/cgra_alg1_func1_dst_d2_data.raw" };
			logi("reading simulation result: %s\n",src_path1);
			fopen_s(&fp, src_path1, "rb");
			if (fp == NULL) {
				logi("can not open the file path: %s\n",src_path1);
				pause();//system("pause");
				return;
			}
			unsigned short* ptr1;
			ptr1 = (unsigned short*)malloc(sizeof(unsigned short));
			for (int i = 0; i < D2_HEIGHT_OUT; i++) {
				for (int j = 0; j < D2_WIDTH_OUT; j++) {
					for (int c = 0; c < 3; c++) {
						size_t sizeRead =  fread(ptr1, 2, 1, fp);
						if(sizeRead != 1) {logi("fread error! \n"); pause();} 
						readresult = *ptr1;

						if(dst_d2_data[i][j][c]!=readresult)
						{
							if(mismatchcount < 20 )
							cout <<"mismatch result Error: reference("<<src_path<<")["<<std::dec<<i<<"]["<<std::dec<<j<<"]["<<std::dec<<c<<"]: "<<dst_d2_data[i][j][c] \
							<<" mismatch result("<<src_path1<<")["<<std::dec<<i<<"]["<<std::dec<<j<<"]["<<std::dec<<c<<"]:"<<std::dec<<readresult<<", mismatch count ="<<mismatchcount<<endl;
							mismatchcount++;
						}else{
						matchcount++;
						}
					}
				}
			}	



			cout <<"Compare between reference(" <<src_path<< ") and simulation result("<<src_path1<<	\
		")  : mismatch count = "<<mismatchcount<<", match count ="<<matchcount<<endl;
			fclose(fp);
			free(ptr1);
			ptr1 = NULL;
			cout<<"TASK["<<dec<<taskid<<"] verify dst_d2_data result_to_file END"<<endl;
			cout<<"---------------------------------------------------------------------"<<endl;
	}
	else if(taskid == 10)
	{
		cout<<"---------------------------------------------------------------------"<<endl;
		cout<<"TASK["<<dec<<taskid<<"] verify src_d3_data result_to_file BEGIN"<<endl;
		FILE* fp = NULL;
		
		char src_path[256] = { "../dst_pic/alg6_func_src_d3_output.raw" };
		logi("reading alg6 output reference : %s\n",src_path);
		fopen_s(&fp, src_path, "rb");
		if (fp == NULL) {
			logi("can not open the file path: %s\n", src_path);
			pause();//system("pause");
			return;
		}
		unsigned short* ptr = NULL;
		unsigned short readresult;
		ptr = (unsigned short*)malloc(sizeof(unsigned short));
		for (int i = 0; i < SIZE_D1_H/2 * SIZE_D1_W/2 * 2; i++) 
		{
				size_t sizeRead = fread(ptr, 2, 1, fp);
				if(sizeRead != 1) {logi("fread error! \n"); pause();} 
				src_d3_data[i]=*ptr;
		}
		fclose(fp);
		free(ptr);
		ptr = NULL;
		//read CGRA output 

		char src_path1[256] = { "../dst_pic/cgra_alg6_func_src_d3_output.raw" };
		logi("reading simulation result: %s\n",src_path1);
		fopen_s(&fp, src_path1, "rb");
		if (fp == NULL) {
			logi("can not open the file path: %s\n",src_path1);
			pause();//system("pause");
			return;
		}
		unsigned short* ptr1;
		int mismatchcount = 0;
		int matchcount = 0;
		ptr1 = (unsigned short*)malloc(sizeof(unsigned short));
		for (int i = 0; i < SIZE_D1_H/2 * SIZE_D1_W/2 * 2; i++) {
				size_t sizeRead =  fread(ptr1, 2, 1, fp);
				if(sizeRead != 1) {logi("fread error! \n"); pause();} 
				readresult = *ptr1;
				if(src_d3_data[i]!=readresult){
					if(mismatchcount<10)
					cout <<"mismatch result Error: reference("<<src_path<<")["<<std::dec<<i<<"]:"<<src_d3_data[i]<<" mismatch result("<<src_path1<<")["<<std::dec<<i<<"]:"<<std::dec<<readresult<<endl;
					mismatchcount++;
				}else{
					matchcount++;
				}
		}
		cout <<"Compare between reference(" <<src_path<< ") and simulation result("<<src_path1<<	\
		")  : mismatch count = "<<mismatchcount<<", match count ="<<matchcount<<endl;
		fclose(fp);
		free(ptr1);
		ptr1 = NULL;
		cout<<"TASK["<<dec<<taskid<<"] verify src_d3_data result_to_file END"<<endl;

		cout<<"TASK["<<dec<<taskid<<"] verify dst_d4 data result_to_file BEGIN"<<endl;
		mismatchcount = 0;
		matchcount = 0;
		char src_path2[256] = { "../dst_pic/alg6_func_d4_dst_output.raw" };
		logi("reading alg6 output reference : %s\n",src_path2);
		fopen_s(&fp, src_path2, "rb");
		if (fp == NULL) {
			logi("can not open the file path: %s\n", src_path2);
			pause();//system("pause");
			return;
		}
		unsigned short* ptr2 = (unsigned short*)malloc(sizeof(unsigned short));
		for (int i = 0; i < SIZE_D1_H/2 *SIZE_D1_W/2; i++) 
		{
				size_t sizeRead = fread(ptr2, 2, 1, fp);
				if(sizeRead != 1) {logi("fread error! \n"); pause();} 
				d4_dst[i]=*ptr2;
		}
		fclose(fp);
		free(ptr2);
		ptr2 = NULL;

		//read CGRA output 
		char src_path3[256] = { "../dst_pic/cgra_alg6_func_d4_dst_output.raw" };
		logi("reading simulation result: %s\n",src_path3);
		fopen_s(&fp, src_path3, "rb");
		if (fp == NULL) {
			logi("can not open the file path: %s\n",src_path3);
			pause();//system("pause");
			return;
		}
		unsigned short* ptr3 = (unsigned short*)malloc(sizeof(unsigned short));
		for (int i = 0; i < SIZE_D1_H/2 *SIZE_D1_W/2; i++) {
				size_t sizeRead = fread(ptr3, 2, 1, fp);
				if(sizeRead != 1) {logi("fread error! \n"); pause();} 
				readresult = *ptr3;
				if(d4_dst[i]!=readresult){
					if(mismatchcount<10)
					cout <<"mismatch result Error: reference("<<src_path2<<")["<<std::dec<<i<<"]:"<<d4_dst[i]<<" mismatch result("<<src_path3<<")["<<std::dec<<i<<"]:"<<std::dec<<readresult<<endl;
					mismatchcount++;
				}else{
					matchcount++;
				}
		}
		cout <<"Compare between reference(" <<src_path2<< ") and simulation result("<<src_path3<<	\
		")  : mismatch count = "<<mismatchcount<<", match count ="<<matchcount<<endl;
		fclose(fp);
		free(ptr3);
		ptr3 = NULL;
		cout<<"TASK["<<dec<<taskid<<"] verify d4_dst result_to_file END"<<endl;
		cout<<"---------------------------------------------------------------------"<<endl;
		//--------------alg6--------------
	return;
	}else{
		return;
	}
	
	
}


