/*
 * compressing.cpp
 *
 *  Created on: Jun 30, 2021
 *      Author: lee
 */

#include "compressing.h"

struct NodeBit** kmer_indexing(struct seq_ref *p, uint32_t len_kmer,char *compress_seq_out) {
	string ref_compress;  //压缩后的字符串
	uint64_t *p_kmer1; //将kmer转化为整数指针
	uint64_t *p_kmer2;
	p_kmer1 = (uint64_t*) malloc(sizeof(uint64_t) * 4);
	p_kmer2 = (uint64_t*) malloc(sizeof(uint64_t) * 4);
	struct bit256KmerPara para;
	get_para(&para, len_kmer);  //给定长度kmer的参数化
	char *p_ref_tmp;    //临时的一条参考序列
	//(1) 初始化B+树
	struct NodeBit **p_tmp;
	p_tmp = bit256initialHashFTable();
	//B+树上的ID
	uint64_t arrayId = 0;
	//判断kmer是否在B+树时接受的返回值
	int64_t x;
	int64_t count = 0;  // 记录字符$的个数
	for (uint32_t i = 0; i < (*p).seq_number; i++) {
		p_ref_tmp = (*p).seq[i];
		cal_hash_value_directly_256bit(p_ref_tmp, p_kmer1, para); //计算序列上首个kmer使用的函数
		struct nodeBit c_tmp_hashtable; //B+树上的每个结点
		c_tmp_hashtable.hashValue = p_kmer1;
		x = getHashFTableValue(p_tmp, p_kmer1, para);
		if (x != -1) {
			//如果当前kmer存在于B+树上
			if (ref_compress.length() != 0) //并且当前ref_compress不为空
			{ //判断目前最后一个字符是否为$,如果是$,跳过该kmer什么也不做;不是$的时候,插入$
				if (ref_compress[ref_compress.length() - 1] != '$') {
					ref_compress.push_back('$');
					count++;
				}
			}
		} else {
			//如果当前kmer不在B+树上
			c_tmp_hashtable.arrayID = arrayId;
			if (0 == ref_compress.length() || ref_compress[ref_compress.length()-1] == '$') { // 最开始的时候，kmer 不在B+树上 且 ref_compress为空
				ref_compress.append(p_ref_tmp, 0, len_kmer);
//				strncpy(&ref_compress[0],p_ref_tmp,len_kmer);
			} else {
				//kmer 不在B+树上 但 ref_compress不为空
				ref_compress.push_back(p_ref_tmp[len_kmer - 1]);
			}
			bit256insertHashFTable(p_tmp, c_tmp_hashtable, para);  //插入到B+树
			arrayId++;
		}
		for (uint32_t j = 1; j < (*p).seq_len[i] - len_kmer + 1; j++) {
			cal_hash_value_indirectly_256bit(p_ref_tmp+j, p_kmer1, p_kmer2, para);
			//对每一个文件处理
//			cout<<"111:"<<p_kmer2[0]<<endl;
			c_tmp_hashtable.hashValue = p_kmer2;
			x = getHashFTableValue(p_tmp, p_kmer2, para);
			if (x != -1) {
				//如果当前kmer存在于B+树上
				if (ref_compress.length() != 0)  //并且当前ref_compress不为空
						{  //判断最后一个字符是否为$,如果是$,跳过该kmer(什么都不做); 不是$的时候,放入一个$
					if (ref_compress[ref_compress.length() - 1] != '$') {
						ref_compress.push_back('$');
						count++;
					}
				}
			} else {
				//如果当前kmer不在B+树上
				c_tmp_hashtable.arrayID = arrayId;
				if (ref_compress[ref_compress.length()-1] == '$') { // 最开始的时候，kmer 不在B+树上 且 ref_compress为空
					ref_compress.append(p_ref_tmp, j, len_kmer);
	//				strncpy(&ref_compress[0],p_ref_tmp,len_kmer);
				} else {
					//kmer 不在B+树上 但 ref_compress不为空
					ref_compress.push_back(p_ref_tmp[j+len_kmer - 1]);
				}
				bit256insertHashFTable(p_tmp, c_tmp_hashtable, para);  //插入到B+树
				arrayId++;
			}
			uint64_t *p = p_kmer1;
			p_kmer1 = p_kmer2;
			p_kmer2 = p;
		}
	}
//	ref_compress.erase(ref_compress.end()-1);   //删除掉最后的$
//	count--;    //count也要相应的-1个
	cout << "正在将压缩后的字符串保存到文件中..." << endl;
	ofstream fout;
	fout.open(compress_seq_out);
	if (fout.is_open()) {
		fout << ref_compress << endl;
		fout.close();
	}
	cout<< "保存成功!"<<endl;
	cout<<"该文件中字符$的个数:"<<count<<endl;
	cout<<"该文件中的字符串长度为:"<<ref_compress.length()<<endl;
	return p_tmp;
}

