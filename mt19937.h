#ifndef MT19937_H
#define MT19937_H
 
#define __CS const static
typedef unsigned int uint;
typedef unsigned long long ull;

/*
HOW TO USE mt19937.h:
	Case 1:
		MT19937 RCORE((unsigned)time(NULL));
	Case 2:
		ull __declspec() RDTSC() {__asm("rdtsc");}
		MT19937 RCORE(RDTSC());
	Case 3:
		MT19937 RCORE(---any seed---)
	Personally I prefer using
		RDTSC()^(unsigned)time(NULL)
*/

class MT19937
{
public:
	__CS int N=624,M=397;
	__CS uint UPPER=0x80000000,LOWER=0x7FFFFFFF;
	__CS uint C1=0x6C078965,C2=0x9908B0DF;
	__CS int W=11,X=7,Y=15,Z=18;
	__CS uint R=0xFFFFFFFF,S=0x9D2C5680,T=0xEFC60000;
private:
	int idx;
	uint MT[N];
	void twist();
public:
	MT19937(unsigned s)
	{
		//ull __declspec() rdtsc() {__asm("rdtsc");}
		//this->srand((unsigned)time(NULL));
		this->srand(s);
	}
	void srand(int seed);
	uint getRand();
};

void MT19937::twist()
{
	for(int i=0;i<N;i++)
	{
		int nxt = (i+1) % N;
		uint y = (this->MT[i]&UPPER)+(this->MT[nxt]&LOWER);
		int jmp = (i+M) % N;
		this->MT[i] = this->MT[jmp] ^ (y>>1);
		if(y&1) this->MT[i] ^= C2;
	}
	return;
}

void MT19937::srand(int seed)
{
	this->idx = 0;
	this->MT[0] = (uint)seed;
	for(int i=1;i<N;i++)
	{
		uint tmp = this->MT[i-1];
		uint t = C1*(tmp^(tmp>>30))+i;
		this->MT[i] = t & 0xFFFFFFFF;
	}
	return;
}

uint MT19937::getRand()
{
	if(this->idx==0) this->twist();
	uint y = this->MT[idx];
	y ^= (y>>W)&R;
	y ^= (y<<X)&S;
	y ^= (y<<Y)&T;
	y ^= (y>>Z);
	idx = (idx+1) % N;
	return y;
}
#endif
