#ifndef BOUNDED_H
#define BOUNDED_H

#include <algorithm>
#include <type_traits>

template<typename T> class bounded
{
private:
	T upperBound,value,lowerBound;
public:
	bounded(T a,T b,T v);
	T getUBound() {return this->upperBound;}
	T getLBound() {return this->lowerBound;}
	T getValue() {return this->value;}
	void checkBounds();
	void setUBound(T x);
	void setLBound(T x);
	void checkValue();
	void setValue(T x);
	bool isFull() {return this->value==this->upperBound;}
	bool isEmpty() {return this->value==this->lowerBound;}
	bool isFixed() {return this->upperBound==this->lowerBound;}
};

template<typename T> bounded<T>::bounded(T a,T b,T v)
{
	if(!std::is_arithmetic<T>::value)
		throw "UNABLE_TO_SET_BOUND_BY_THIS_TYPE";
	this->upperBound = a;
	this->lowerBound = b;
	this->checkBounds(); // auto-swap
	this->value = v;
	this->checkValue();
}

template<typename T> void bounded<T>::checkBounds()
{
	if(this->upperBound < this->lowerBound)
		std::swap(this->upperBound,this->lowerBound);
	return;
}
template<typename T> void bounded<T>::setUBound(T x)
{
	this->upperBound = x;
	this->checkBounds();
	return;
}
template<typename T> void bounded<T>::setLBound(T x)
{
	this->lowerBound = x;
	this->checkBounds();
	return;
}

template<typename T> void bounded<T>::checkValue()
{
	if(this->value < this->lowerBound)
		this->value = this->lowerBound;
	if(this->value > this->upperBound)
		this->value = this->upperBound;
	return;
}
template<typename T> void bounded<T>::setValue(T x)
{
	this->value = x;
	this->checkValue();
	return;
}

#endif
