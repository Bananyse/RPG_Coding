#ifndef DICE_H
#define DICE_H

#include "mt19937.h"
#include <algorithm>

class dint
{
public:
	__CS int DEFAULT_MAX = 20;
private:
	int dMax;
	int dVal;
	MT19937 *randCore;
public:
	dint(MT19937 *rC,int dM=DEFAULT_MAX);
	const int getMax() { return this->dMax; }
	const int getVal() { return this->dVal; }
	enum rType {DEFAULT,TAKEMAX,TAKEMIN};
	int roll(rType rT = DEFAULT);
	int roll(int count);
	void setMax(int dM);
};

dint::dint(MT19937 *rC,int dM)
{
	this->randCore = rC;
	this->dMax = dM;
	this->dVal = this->roll();
}

int dint::roll(rType rT)
{
	int r = abs(this->randCore->getRand());
	r = r % this->dMax + 1;
	if(rT==DEFAULT) this->dVal=r;
	else
	{
		int s = abs(this->randCore->getRand());
		s = s % this->dMax + 1;
		if(rT==TAKEMAX)
			this->dVal=std::max(r,s);
		else if(rT==TAKEMIN)
			this->dVal=std::min(r,s);
	}
	return this->dVal;
}
int dint::roll(int count)
{
	int sum = 0;
	for(int i=0;i<count;i++)
		sum += this->roll();
	return sum;
}

void dint::setMax(int dM)
{
	this->dMax = dM;
	this->dVal = this->roll();
	return;
}

#endif
