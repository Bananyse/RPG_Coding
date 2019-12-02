#ifndef BOUNDED_H
#define BOUNDED_H

#include <algorithm>
#include <type_traits>

template<typename T> class bounded
{
private:
	T upperBound,value,lowerBound;
	void checkBounds();
	void checkValue();
public:
	bounded(T a,T b,T v);
	const T getUBound() {return this->upperBound;}
	const T getLBound() {return this->lowerBound;}
	const T getValue() {return this->value;}
	const bool isFull() {return this->value==this->upperBound;}
	const bool isEmpty() {return this->value==this->lowerBound;}
	const bool isFixed() {return this->upperBound==this->lowerBound;}
	void setUBound(T x);
	void setLBound(T x);
	void setValue(T x);
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
