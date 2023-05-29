/*
 * InputSeq.h
 *
 *  Created on: Apr 7, 2021
 *      Author: lee
 */

#ifndef INPUTSEQ_H_
#define INPUTSEQ_H_
#include "basic.h"
//#include <string.h>

struct seq_ref{
	char ** seq;
	uint32_t * seq_len;
	uint32_t seq_number;
};

void input_seq(struct seq_ref *p, char* p_ref);



#endif /* INPUTSEQ_H_ */
