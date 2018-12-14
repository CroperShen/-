//linkedset.h
//Created by Croper
//last modified in Dec.13.2018
//以链表形式储存的集合

#pragma once
#include "linkedlist.h"

template <typename T> class linkedset;

template <typename T> class linkedset :private linkedlist<T>
{
    template <typename T> friend const bool operator<(const T&,const linkedset<T>&);
	template <typename T> friend const bool operator>(const T&,const linkedset<T>&);
public:
	linkedset() {}                                          //构造函数
	linkedset(const std::initializer_list<T>&);             //构造函数

	const bool empty() const;
	const int count() const;                              //返回集合的大小
	const T&  top() const;                                //返回第一个元素，如果为空会报错
	const T&  buttom() const;                             //返回第最后元素，如果为空会报错
	const T&  ele(int) const;                             //返回某一个元素，如果为空会报错

	const bool Add(const T&);                           //添加一个元素,返回是否添加成功
	template <typename TArr> void AddArr(const TArr&);  //添加数组内的多个元素
	const bool Remove(const T&);                        //删除一个元素，返回是否删除成功

	void operator=(const std::initializer_list<T>&);     //使用初始化表复制

	const bool operator==(const linkedset<T>&) const;     //两集合是否相等;
	const bool operator!=(const linkedset<T>&) const;     //两集合不相等;
	const bool operator<(const linkedset<T>&)  const;     //是否是真子集
	const bool operator<=(const linkedset<T>&) const;     //是否是子集
	const bool operator>(const linkedset<T>&)  const;     //是否是真父集
	const bool operator>=(const linkedset<T>&) const;     //是否是父集

	linkedset<T>& operator+(const linkedset<T>&)const;      //求并集
	linkedset<T>& operator-(const linkedset<T>&)const;      //求相对补集

	linkedset<T>& operator&&(const linkedset<T>&)const;     //求并集
	linkedset<T>& operator||(const linkedset<T>&)const;     //求交集
};


template <typename T> linkedset<T>::linkedset(const std::initializer_list<T>& initlist)
{
	for (auto pt = initlist.begin(); pt != initlist.end(); pt++)
	{
		Add(*pt);
	}
}

template <typename T> const bool operator<(const T& t, const linkedset<T>& set)
{
	for (int i = 0; i < set.count(); i++)
	{
		if (t == set.ele(i)) return true;
	}
	return false;
}

template <typename T> const bool operator>(const T& t,const linkedset<T>& set)
{
	for (int i = 0; i < set.count(); i++)
	{
		if (t == set.ele(i)) return false;
	}
	return true;
}

template <typename T> const bool linkedset<T>::Add(const T& t) //添加一个元素,返回是否添加成功
{
	if (t < (*this)) return false;
	linkedlist<T>::Append(t);
	return true;
}

template <typename T> template <typename TArr> void linkedset<T>::AddArr(const TArr& Arr)
{
	int n = sizeof(Arr) / sizeof(Arr[0]);
	for (int i = 0; i < n; i++)
	{
		Add(Arr[i]);
	}
}
template <typename T>  const bool linkedset<T>::Remove(const T& t) //删除一个元素，返回是否删除成功
{
	for (int i = 0; i < count(); i++)
	{
		if (t == ele(i))
		{
			linkedlist<T>::Delete(i);
			return true;
		}
	}
	return false;
}


template <typename T> const T& linkedset<T>::top() const           //返回第一个元素，如果为空会报错
{
	return this->head();
}
template <typename T> const T& linkedset<T>::buttom() const        //返回最后一个元素，如果为空会报错
{
	return this->tail();
}
template <typename T> const T& linkedset<T>::ele(int i)  const      //返回某一个元素，如果为空会报错
{
	return this->value(i);
}

template <typename T> const bool linkedset<T>::empty() const
{
	return linkedlist<T>::empty();
}

template <typename T>  const int linkedset<T>::count() const       //返回集合的大小
{
	return this->length();
}

template <typename T> void linkedset<T>::operator=(const std::initializer_list<T>& initlist)
{
	this->Clear();
	T tTemp;
	for (auto pt = initlist.begin(); pt != initlist.end(); pt++)
	{
		tTemp = *pt;
		Add(tTemp);
	}
}

template <typename T>  const bool linkedset<T>::operator==(const linkedset<T>& set) const    //两集合是否相等;
{
	if (count() != set.count()) return false;
	for (int i = 0; i <= count(i); i++)
	{
		if (ele(i) > set) return false;
	}
	return true;
}

template <typename T> inline  const bool linkedset<T>::operator!=(const linkedset<T>& set) const    //两集合是否相等;
{
	return (!operator==(set));
}

template <typename T>  const bool linkedset<T>::operator<(const linkedset<T>& set) const     //是否是真子集
{
	if (count() >= set.count()) return false;
	for (int i = 0; i <= count(i); i++)
	{
		if (ele(i) > set) return false;
	}
	return true;
}

template <typename T> const bool  linkedset<T>::operator<=(const linkedset<T>& set)const     //是否是子集
{
	if (count() > set.count()) return false;
	for (int i = 0; i < count(); i++)
	{
		if (ele(i) > set) return false;
	}
	return true;
}
template <typename T> const bool  linkedset<T>::operator>(const linkedset<T>& set)const      //是否是真父集
{
	if (count() <= set.count()) return false;
	for (int i = 0; i < set.count(); i++)
	{
		if (set.value(i) > (*this)) return false;
	}
	return true;
}
template <typename T> const bool  linkedset<T>::operator>=(const linkedset<T>& set) const     //是否是父集
{
	if (count() < set.count()) return false;
	for (int i = 0; i < set.count(i); i++)
	{
		if (set.value(i) > (*this)) return false;
	}
	return true;
}

template <typename T>  linkedset<T>& linkedset<T>::operator+(const linkedset<T>& set)const       //求并集
{
	static linkedset<T> ans;
	ans = set;
	for (int i = 0; i < count(); i++)
	{
		if (value(i) > ans)
		{
			ans.Add(value(i));
		}
	}
	return ans;
}
template <typename T>  linkedset<T>& linkedset<T>::operator-(const linkedset<T>& set) const      //求相对补集
{
	static linkedset<T> ans;
	ans = *this;
	for (int i = 0; i < set.length(); i++)
	{
		if (set.value(i) < ans)
		{
			ans.Delete(value(i));
		}
	}
	return ans;
}

template <typename T> linkedset<T>& linkedset<T>::operator&&(const linkedset<T>& set) const     //求并集
{
	static linkedset<T> ans;
	ans = set;
	for (int i = 0; i < count(); i++)
	{
		if (ele(i) > set)
		{
			ans.Add(ele(i));
		}
	}
	return ans;
}
template <typename T> linkedset<T>& linkedset<T>::operator|| (const linkedset<T>& set) const     //求交集
{
	static linkedset<T> ans;
	ans = set;
	for (int i = 0; i < set.count(); i++)
	{
		if (set.value(i)>*this)
		{
			ans.Remove(set.value(i));
		}
	}
	return ans;
}