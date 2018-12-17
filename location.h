//=================================================================
//location.h
//CreateBy Croper
//last modified at Dec.17.2018
//ʵ���˵���࣬�������������κ�֧����������ı�����ʽ��Ĭ����֧��float���͵�loaction��֧��int���͵�location_int
//===================================================================

#pragma once
#define _LOCATION_H

#include "cprlib.h"
enum relatpos {pos_intersect=0,pos_tangency=1,pos_separation=2};//���λ�� pos_intersect�ཻ pos_tangency ���� pos_separation����

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
	template <typename T2> location_template<T>(const location_template<T2>&);  //���������Ͳ�ͬ��location���ำֵʱ�����õĹ��캯��
	~location_template();

	location_template<T>& operator=(location_template<T>);                   //����ù��캯�������Ͳ�ͬʱ����ȷ������֮���ܻ���ת��
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