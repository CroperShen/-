//=================================================================
//location.h
//CreateBy Croper
//last modified at Dec.17.2018
//实现了点的类，点的坐标可以是任何支持四则运算的变量格式。默认有支持float类型的loaction和支持int类型的location_int
//===================================================================

#pragma once
#define _LOCATION_H

#include "cprlib.h"
enum relatpos {pos_intersect=0,pos_tangency=1,pos_separation=2};//相对位置 pos_intersect相交 pos_tangency 相切 pos_separation相离

template <typename T> class location_template;

typedef location_template<float> location;
typedef location_template<int> location_int;

template <typename T> class location_template
{
public:
	T x;
	T y;
	location_template();
	location_template(T,T);
	location_template<T>(const location_template<T>&);
	template <typename T2> location_template<T>(const location_template<T2>&);  //当两个类型不同的location互相赋值时，调用的构造函数
	~location_template();

	location_template<T>& operator=(location_template<T>);                   //会调用构造函数，类型不同时，请确保类型之间能互相转换
};

template <typename T> location_template<T>::location_template()
{
	x =(T)0;
	y =(T)0;
}
template <typename T> location_template<T>::location_template(T x0,T y0)
{
	x = x0;
	y = y0;
}

template <typename T> location_template<T>::location_template(const location_template<T>& loc0)
{
	x = loc0.x;
	y = loc0.y;
}

template <typename T> template <typename T2> location_template<T>::location_template(const location_template<T2>& loc0)
{
	x = loc0.x;
	y = loc0.y;
}

template <typename T> location_template<T>::~location_template(){}

template <typename T> location_template<T>& location_template<T>::operator=(location_template<T> loc0)
{
	x = loc0.x;
	y = loc0.y;
	return *this;
}