/*
 * Main.cpp
 *
 *  Created on: Apr 7, 2021
 *      Author: lee
 */

#include "basic.h"
#include "InputSeq.h"
#include "compressing.h"

int main(int argc, char **argv)
{
	char *p_seq_path = NULL;
	uint32_t len_kmer = 0;
	char *compress_seq_out = NULL;

	for(int32_t i = 1; i < argc;i=i+2)
	{
		if(argv[i][0] == '-' && argv[i][1] == 'r')
		{
			p_seq_path = argv[i+1];
		}
		if(argv[i][0] == '-' && argv[i][1] == 'k')
		{
			len_kmer = atoi(argv[i+1]);
		}
		if(argv[i][0] == '-' && argv[i][1] == 'o')
		{
			compress_seq_out = argv[i+1];
		}
	}

	struct timeval tvs,tve;
	gettimeofday(&tvs,NULL);
	cout <<"start..."<<endl;
//	char *p_seq;
	struct seq_ref p;
	input_seq(&p,p_seq_path);
	struct NodeBit** p_tmp = kmer_indexing(&p,len_kmer,compress_seq_out);
	cout << "end..."<< endl;
	gettimeofday(&tve,NULL);
	double span = tve.tv_sec-tvs.tv_sec + (tve.tv_usec-tvs.tv_usec)/1000000.0;
	cout << "total time is:" << span << endl;
	return 0;

}


