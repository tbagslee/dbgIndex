/*
 * compressing.h
 *
 *  Created on: Jun 30, 2021
 *      Author: lee
 */

#ifndef COMPRESSING_H_
#define COMPRESSING_H_

#include"basic.h"
#include"Hash.h"
#include"BplusTreeBit.h"
#include "InputSeq.h"

struct NodeBit** kmer_indexing(struct seq_ref *p,uint32_t len_kmer,char *compress_seq_out);

#endif /* COMPRESSING_H_ */
