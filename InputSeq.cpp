/*
 * InputSeq.cpp
 *
 *  Created on: Apr 7, 2021
 *      Author: lee
 */

#include "InputSeq.h"
#define MAXSIZE 10000000000

void input_seq(struct seq_ref *p, char* p_ref) //p_ref : path_reference
{
	string line;  //文件里每一行的字符串
	ifstream in(p_ref);
	uint32_t line_number = 0;  //文件里的行数
	while(getline(in,line)){
		line_number++;
//		cout<<"here!"<<endl;
	}
	in.close();
	cout<<"line numbers:"<<line_number<<endl;
	(*p).seq = (char**)malloc(sizeof(char*) * line_number);
	(*p).seq_len = (uint32_t*)malloc(sizeof(uint32_t)*line_number);
	(*p).seq_number = 0;
	ifstream in2(p_ref);
	if(in2)  //有该文件
	{
		uint32_t label = 0;
		uint64_t len_all = 0;
		while(getline (in2, line) )
		{
			cout << line <<endl;
			ReadSeq((*p).seq+label,(*p).seq_len+label,&line[0]);
			len_all += (*p).seq_len[label];
			label++;
			(*p).seq_number ++;
//			strcat(*seq,tem_seq) ;
		}
		cout<<"压缩前,序列总长度为:"<<len_all<<endl;
	}
}

