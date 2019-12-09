#ifndef GENE_H
#define GENE_H
#include "picosha2.h"
#include <cstring>

#define __CeS constexpr static
#define __CS const static

class geneSeq
{
public:
	__CeS int SHASIZE = picosha2::k_digest_size;
	__CeS int ULLSIZE = sizeof(unsigned long long);
	__CeS double ULLMAX = 18446744073709551615.0;
	__CS int SEQLEN = 64;
	__CS int DEFAULT_BLOCK_LEN = 4;
	__CS int DEFAULT_REPEAT = 16;
private:
	typedef unsigned char byte;
	byte seq[SEQLEN];
	inline int bound(int i) {i%=SEQLEN;return i<0?(i+SEQLEN)%SEQLEN:i;}
	double translate(int begin,int len,byte salt);
public:
	geneSeq();
	geneSeq(byte *begin,int len=SEQLEN);
	geneSeq(const geneSeq &parent);
	virtual ~geneSeq() {};
	int express(int range,int bias=0,byte salt=0,
		int begin=0,int block_len=DEFAULT_BLOCK_LEN,int repeat=DEFAULT_REPEAT);
	byte getbyte(int i) {i=bound(i);return this->seq[i];}
	void setbyte(int i,byte j) {i=bound(i);this->seq[i]=j;}
};

geneSeq::geneSeq()
{
	std::memset(this->seq,0,sizeof(this->seq));
}
geneSeq::geneSeq(byte *begin,int len)
{
	std::memset(this->seq,0,sizeof(this->seq));
	for(int i=0;i<len;i++) this->seq[i] = begin[i];
}
geneSeq::geneSeq(const geneSeq &parent)
{
	for(int i=0;i<SEQLEN;i++) this->seq[i] = parent.seq[i];
}

double geneSeq::translate(int begin,int len,byte salt)
{
	byte s[len+1];
	for(int i=0;i<len;i++) s[i] = this->seq[(begin+i)%SEQLEN];
	s[len] = salt;
	byte hash[SHASIZE];
	picosha2::hash256(s,s+len+1,hash,hash+ULLSIZE);
	unsigned long long x = 0;
	for(int i=0;i<ULLSIZE;i++)
	{
		x <<= i?8:0;
		x += (int)hash[i];
	}
	return (double)x / ULLMAX;
}
int geneSeq::express(int range,int bias,byte salt,int begin,int block_len,int repeat)
{
	double x = 0;
	for(int i=0;i<repeat;i++)
		x += this->translate(begin+i*block_len,block_len,salt);
	int y = x*(double)range/(double)repeat;
	if(y>=range) y=range-1; //Extremely rare but could be possible
	return y+bias;
}

#endif
