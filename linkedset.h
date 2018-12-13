//linkedset.h
//Created by Croper
//last modified in Dec.12.2018
//��������ʽ����ļ���

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

	bool Add(T&);    //���һ��Ԫ��,�����Ƿ���ӳɹ�
	template <typename TArr> void AddArr(TArr&); //��������ڵĶ��Ԫ��
	bool Remove(T&); //ɾ��һ��Ԫ�أ������Ƿ�ɾ���ɹ�
	T& Top();         //���ص�һ��Ԫ�ص�ָ�룬���Ϊ�ջᱨ��
	T& Buttom();         //���ص����Ԫ�ص�ָ�룬���Ϊ�ջᱨ��
	T& Ele(int);         //����ĳһ��Ԫ�ص�ָ�룬���Ϊ�ջᱨ��

	int count();       //���ؼ��ϵĴ�С
	bool empty();       //�Ƿ�Ϊ��

	void operator=(std::initializer_list<T> initlist);

	bool operator==(linkedset<T>&);    //�������Ƿ����;
	bool operator!=(linkedset<T>&);    //�����ϲ����;
	bool operator<(linkedset<T>&);     //�Ƿ������Ӽ�
	bool operator<=(linkedset<T>&);    //�Ƿ����Ӽ�
	bool operator>(linkedset<T>&);     //�Ƿ����游��
	bool operator>=(linkedset<T>&);     //�Ƿ��Ǹ���

	linkedset<T>& operator+(linkedset<T>&);      //�󲢼�
	linkedset<T>& operator-(linkedset<T>&);      //����Բ���

	linkedset<T>& operator&&(linkedset<T>&);     //�󲢼�
	linkedset<T>& operator||(linkedset<T>&);     //�󽻼�
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

template <typename T> bool linkedset<T>::Add(T& t) //���һ��Ԫ��,�����Ƿ���ӳɹ�
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
template <typename T> bool linkedset<T>::Remove(T& t) //ɾ��һ��Ԫ�أ������Ƿ�ɾ���ɹ�
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


template <typename T> T& linkedset<T>::Top()        //���ص�һ��Ԫ�أ����Ϊ�ջᱨ��
{
	return this->Value(0);
}
template <typename T> T& linkedset<T>::Buttom()        //���ص�һ��Ԫ�أ����Ϊ�ջᱨ��
{
	return this->Value(count());
}
template <typename T> T& linkedset<T>::Ele(int i)        //���ص�һ��Ԫ�أ����Ϊ�ջᱨ��
{
	return this->Value(i);
}


template <typename T> int linkedset<T>::count()       //���ؼ��ϵĴ�С
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

template <typename T> bool linkedset<T>::operator==(linkedset<T>& set)    //�������Ƿ����;
{
	if (count() != set.count()) return false;
	for (int i = 0; i <= count(i); i++)
	{
		if (Value(i) > set) return false;
	}
	return true;
}

template <typename T> inline bool linkedset<T>::operator!=(linkedset<T>& set)    //�������Ƿ����;
{
	return (!operator==(set));
}

template <typename T> bool  linkedset<T>::operator<(linkedset<T>& set)     //�Ƿ������Ӽ�
{
	if (count() >= set.count()) return false;
	for (int i = 0; i <= count(i); i++)
	{
		if (Value(i) > set) return false;
	}
	return true;
}

template <typename T> bool  linkedset<T>::operator<=(linkedset<T>& set)    //�Ƿ����Ӽ�
{
	if (count() > set.count()) return false;
	for (int i = 0; i < count(); i++)
	{
		if (this->Value(i) > set) return false;
	}
	return true;
}
template <typename T> bool  linkedset<T>::operator>(linkedset<T>& set)     //�Ƿ����游��
{
	if (count() <= set.count()) return false;
	for (int i = 0; i < set.count(); i++)
	{
		if (set.Value(i) > (*this)) return false;
	}
	return true;
}
template <typename T> bool  linkedset<T>::operator>=(linkedset<T>& set)     //�Ƿ��Ǹ���
{
	if (count() < set.count()) return false;
	for (int i = 0; i < set.count(i); i++)
	{
		if (set.Value(i) > (*this)) return false;
	}
	return true;
}

template <typename T>  linkedset<T>& linkedset<T>::operator+(linkedset<T>& set)      //�󲢼�
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
template <typename T>  linkedset<T>& linkedset<T>::operator-(linkedset<T>& set)      //����Բ���
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

template <typename T>  linkedset<T>& linkedset<T>::operator&&(linkedset<T>& set)     //�󲢼�
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
template <typename T>  linkedset<T>& linkedset<T>::operator|| (linkedset<T>& set)     //�󽻼�
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