//linkedset.h
//Created by Croper
//last modified in Dec.13.2018
//��������ʽ����ļ���

#pragma once
#include "linkedlist.h"

template <typename T> class linkedset;

template <typename T> class linkedset :private linkedlist<T>
{
    template <typename T> friend const bool operator<(const T&,const linkedset<T>&);
	template <typename T> friend const bool operator>(const T&,const linkedset<T>&);
public:
	linkedset() {}                                          //���캯��
	linkedset(const std::initializer_list<T>&);             //���캯��

	const bool empty() const;
	const int count() const;                              //���ؼ��ϵĴ�С
	const T&  top() const;                                //���ص�һ��Ԫ�أ����Ϊ�ջᱨ��
	const T&  buttom() const;                             //���ص����Ԫ�أ����Ϊ�ջᱨ��
	const T&  ele(int) const;                             //����ĳһ��Ԫ�أ����Ϊ�ջᱨ��

	const bool Add(const T&);                           //���һ��Ԫ��,�����Ƿ���ӳɹ�
	template <typename TArr> void AddArr(const TArr&);  //��������ڵĶ��Ԫ��
	const bool Remove(const T&);                        //ɾ��һ��Ԫ�أ������Ƿ�ɾ���ɹ�

	void operator=(const std::initializer_list<T>&);     //ʹ�ó�ʼ������

	const bool operator==(const linkedset<T>&) const;     //�������Ƿ����;
	const bool operator!=(const linkedset<T>&) const;     //�����ϲ����;
	const bool operator<(const linkedset<T>&)  const;     //�Ƿ������Ӽ�
	const bool operator<=(const linkedset<T>&) const;     //�Ƿ����Ӽ�
	const bool operator>(const linkedset<T>&)  const;     //�Ƿ����游��
	const bool operator>=(const linkedset<T>&) const;     //�Ƿ��Ǹ���

	linkedset<T>& operator+(const linkedset<T>&)const;      //�󲢼�
	linkedset<T>& operator-(const linkedset<T>&)const;      //����Բ���

	linkedset<T>& operator&&(const linkedset<T>&)const;     //�󲢼�
	linkedset<T>& operator||(const linkedset<T>&)const;     //�󽻼�
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

template <typename T> const bool linkedset<T>::Add(const T& t) //���һ��Ԫ��,�����Ƿ���ӳɹ�
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
template <typename T>  const bool linkedset<T>::Remove(const T& t) //ɾ��һ��Ԫ�أ������Ƿ�ɾ���ɹ�
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


template <typename T> const T& linkedset<T>::top() const           //���ص�һ��Ԫ�أ����Ϊ�ջᱨ��
{
	return this->head();
}
template <typename T> const T& linkedset<T>::buttom() const        //�������һ��Ԫ�أ����Ϊ�ջᱨ��
{
	return this->tail();
}
template <typename T> const T& linkedset<T>::ele(int i)  const      //����ĳһ��Ԫ�أ����Ϊ�ջᱨ��
{
	return this->value(i);
}

template <typename T> const bool linkedset<T>::empty() const
{
	return linkedlist<T>::empty();
}

template <typename T>  const int linkedset<T>::count() const       //���ؼ��ϵĴ�С
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

template <typename T>  const bool linkedset<T>::operator==(const linkedset<T>& set) const    //�������Ƿ����;
{
	if (count() != set.count()) return false;
	for (int i = 0; i <= count(i); i++)
	{
		if (ele(i) > set) return false;
	}
	return true;
}

template <typename T> inline  const bool linkedset<T>::operator!=(const linkedset<T>& set) const    //�������Ƿ����;
{
	return (!operator==(set));
}

template <typename T>  const bool linkedset<T>::operator<(const linkedset<T>& set) const     //�Ƿ������Ӽ�
{
	if (count() >= set.count()) return false;
	for (int i = 0; i <= count(i); i++)
	{
		if (ele(i) > set) return false;
	}
	return true;
}

template <typename T> const bool  linkedset<T>::operator<=(const linkedset<T>& set)const     //�Ƿ����Ӽ�
{
	if (count() > set.count()) return false;
	for (int i = 0; i < count(); i++)
	{
		if (ele(i) > set) return false;
	}
	return true;
}
template <typename T> const bool  linkedset<T>::operator>(const linkedset<T>& set)const      //�Ƿ����游��
{
	if (count() <= set.count()) return false;
	for (int i = 0; i < set.count(); i++)
	{
		if (set.value(i) > (*this)) return false;
	}
	return true;
}
template <typename T> const bool  linkedset<T>::operator>=(const linkedset<T>& set) const     //�Ƿ��Ǹ���
{
	if (count() < set.count()) return false;
	for (int i = 0; i < set.count(i); i++)
	{
		if (set.value(i) > (*this)) return false;
	}
	return true;
}

template <typename T>  linkedset<T>& linkedset<T>::operator+(const linkedset<T>& set)const       //�󲢼�
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
template <typename T>  linkedset<T>& linkedset<T>::operator-(const linkedset<T>& set) const      //����Բ���
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

template <typename T> linkedset<T>& linkedset<T>::operator&&(const linkedset<T>& set) const     //�󲢼�
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
template <typename T> linkedset<T>& linkedset<T>::operator|| (const linkedset<T>& set) const     //�󽻼�
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