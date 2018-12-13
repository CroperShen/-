//linkedset.h
//Created by Croper
//last modified in Dec.12.2018
//以链表形式储存的集合

#pragma once
#include "LinkedList.h"

template <typename T> class linkedset;

template <typename T> class linkedset :public linkedlist<T>
{
    template <typename T> friend bool operator<(const T&, linkedset<T>&);
	template <typename T> friend bool operator>(const T&, linkedset<T>&);
public:
	linkedset() {}
	linkedset(std::initializer_list<T> initlist);

	bool Add(T&);    //添加一个元素,返回是否添加成功
	template <typename TArr> void AddArr(TArr&); //添加数组内的多个元素
	bool Remove(T&); //删除一个元素，返回是否删除成功
	T& Top();         //返回第一个元素的指针，如果为空会报错
	T& Buttom();         //返回第最后元素的指针，如果为空会报错
	T& Ele(int);         //返回某一个元素的指针，如果为空会报错

	int count();       //返回集合的大小
	bool empty();       //是否为空

	void operator=(std::initializer_list<T> initlist);

	bool operator==(linkedset<T>&);    //两集合是否相等;
	bool operator!=(linkedset<T>&);    //两集合不相等;
	bool operator<(linkedset<T>&);     //是否是真子集
	bool operator<=(linkedset<T>&);    //是否是子集
	bool operator>(linkedset<T>&);     //是否是真父集
	bool operator>=(linkedset<T>&);     //是否是父集

	linkedset<T>& operator+(linkedset<T>&);      //求并集
	linkedset<T>& operator-(linkedset<T>&);      //求相对补集

	linkedset<T>& operator&&(linkedset<T>&);     //求并集
	linkedset<T>& operator||(linkedset<T>&);     //求交集
};


template <typename T> linkedset<T>::linkedset(std::initializer_list<T> initlist)
{
	for (auto pt = initlist.begin(); pt != initlist.end(); pt++)
	{
		Add(*pt);
	}
}

template <typename T> bool operator<(T& t, linkedset<T>& set)
{
	for (int i = 0; i < set.count(); i++)
	{
		if (t == set.Value(i)) return true;
	}
	return false;
}

template <typename T> bool operator>(T& t, linkedset<T>& set)
{
	for (int i = 0; i < set.count(); i++)
	{
		if (t == set.Value(i)) return false;
	}
	return true;
}

template <typename T> bool linkedset<T>::Add(T& t) //添加一个元素,返回是否添加成功
{
	if (t < (*this)) return false;
    this->Append(t);
	return true;
}

template <typename T> template <typename TArr> void linkedset<T>::AddArr(TArr& Arr)
{
	int n = sizeof(Arr) / sizeof(Arr[0]);
	for (int i = 0; i < n; i++)
	{
		Add(Arr[i]);
	}
}
template <typename T> bool linkedset<T>::Remove(T& t) //删除一个元素，返回是否删除成功
{
	for (int i = 0; i < count(); i++)
	{
		if (t == this->Value(i))
		{
			this->Delete(i);
			return true;
		}
	}
	return false;
}


template <typename T> T& linkedset<T>::Top()        //返回第一个元素，如果为空会报错
{
	return this->Value(0);
}
template <typename T> T& linkedset<T>::Buttom()        //返回第一个元素，如果为空会报错
{
	return this->Value(count());
}
template <typename T> T& linkedset<T>::Ele(int i)        //返回第一个元素，如果为空会报错
{
	return this->Value(i);
}


template <typename T> int linkedset<T>::count()       //返回集合的大小
{
	return this->Length();
}

template <typename T> inline bool linkedset<T>::empty()
{
	return (count() == 0);
}


template <typename T> void linkedset<T>::operator=(std::initializer_list<T> initlist)
{
	this->Clear();
	T tTemp;
	for (auto pt = initlist.begin(); pt != initlist.end(); pt++)
	{
		tTemp = *pt;
		Add(tTemp);
	}
}

template <typename T> bool linkedset<T>::operator==(linkedset<T>& set)    //两集合是否相等;
{
	if (count() != set.count()) return false;
	for (int i = 0; i <= count(i); i++)
	{
		if (Value(i) > set) return false;
	}
	return true;
}

template <typename T> inline bool linkedset<T>::operator!=(linkedset<T>& set)    //两集合是否相等;
{
	return (!operator==(set));
}

template <typename T> bool  linkedset<T>::operator<(linkedset<T>& set)     //是否是真子集
{
	if (count() >= set.count()) return false;
	for (int i = 0; i <= count(i); i++)
	{
		if (Value(i) > set) return false;
	}
	return true;
}

template <typename T> bool  linkedset<T>::operator<=(linkedset<T>& set)    //是否是子集
{
	if (count() > set.count()) return false;
	for (int i = 0; i < count(); i++)
	{
		if (this->Value(i) > set) return false;
	}
	return true;
}
template <typename T> bool  linkedset<T>::operator>(linkedset<T>& set)     //是否是真父集
{
	if (count() <= set.count()) return false;
	for (int i = 0; i < set.count(); i++)
	{
		if (set.Value(i) > (*this)) return false;
	}
	return true;
}
template <typename T> bool  linkedset<T>::operator>=(linkedset<T>& set)     //是否是父集
{
	if (count() < set.count()) return false;
	for (int i = 0; i < set.count(i); i++)
	{
		if (set.Value(i) > (*this)) return false;
	}
	return true;
}

template <typename T>  linkedset<T>& linkedset<T>::operator+(linkedset<T>& set)      //求并集
{
	static linkedset<T> ans;
	ans = set;
	for (int i = 0; i < count(); i++)
	{
		if (Value(i) > ans)
		{
			ans.Add(Value(i));
		}
	}
	return ans;
}
template <typename T>  linkedset<T>& linkedset<T>::operator-(linkedset<T>& set)      //求相对补集
{
	static linkedset<T> ans;
	ans = *this;
	for (int i = 0; i < set.length(); i++)
	{
		if (set.Value(i) < ans)
		{
			ans.Delete(Value(i));
		}
	}
	return ans;
}

template <typename T>  linkedset<T>& linkedset<T>::operator&&(linkedset<T>& set)     //求并集
{
	static linkedset<T> ans;
	ans = set;
	for (int i = 0; i < count(); i++)
	{
		if (this->Value(i) > set)
		{
			ans.Add(this->Value(i));
		}
	}
	return ans;
}
template <typename T>  linkedset<T>& linkedset<T>::operator|| (linkedset<T>& set)     //求交集
{
	static linkedset<T> ans;
	ans = set;
	for (int i = 0; i < set.count(); i++)
	{
		if (set.Value(i)>*this)
		{
			ans.Remove(set.Value(i));
		}
	}
	return ans;
}