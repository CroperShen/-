//linkedlist.h
//Created by CroperShen
//Last modified in Dec.11.2018
//链表结构，练习之做


#pragma once

#include <initializer_list>
#include <stdlib.h>

//声明类
template <typename T> class link;                  //链表节点
template <typename T> class linkedlist;            //链表

int min(int a1,int  a2)
{
	if (a1 > a2) return a2;
	return a1;
}

int max(int a1, int  a2)
{
	if (a1 > a2) return a1;
	return a2;
}
//类的声明结束

//=======================================================

//类的定义
template <typename T> class link    //链表节点
{
	friend class linkedlist<T>;
private:
	T Value;  // 值域
	link<T> *PreNode;
	link<T> *NextNode;
public:
	link();  //构造函数,
	link(T&);  //构造函数,
	link(link<T>&); //复制构造函数
	~link();  //析构函数

	void setData(T&);    //设置值      
};

//-----------------------------
template <typename T> class linkedlist //链表
{
private:
	link<T> *headernode;  //头节点,为虚节点,头节点的NextNode为首节点，PreNode为尾节点;
	int l;    //长度
protected:
	link<T> *iNode(int);         //获取指定节点，不限上下限(循环)
	link<T> *pNode(int);       //获取指定节点，限制上下限(返回NULL)
	link<T> *pHead();
	link<T> *pTail();
public:

	linkedlist();                 //构造函数,创建空链表
	template <typename TArr> linkedlist(TArr&, int=-1);      //根据数组创建链表  参数（数组，链表大小) 如链表大小为-1则为默认数组长度
	linkedlist(std::initializer_list<T>); //使用初始化表构造链表
	linkedlist(linkedlist<T>&);   //拷贝构造函数
	~linkedlist();                //析构函数  
	void operator=(linkedlist<T>&);             //重载赋值 使其变为复制

	inline bool empty() { return (l == 0); }    //是否是空链表
	link<T>& Append(T&);          //于尾部添加一个值
	link<T>& Insert(T&,int);      //于给定位置添加一个值，其他值顺延
	bool Delete(int);             //删除给定位置的值，如超限会返回失败
	void Clear();                  //清空链表
	linkedlist<T>& Turn();                  //转置链表，首变为尾尾变为首；

    virtual bool operator==(linkedlist<T>&);    //链表相等，只有在链表每一个元素都完全相同时才相等;
	virtual bool operator!=(linkedlist<T>&);    //链表不相等;

	int Length();                 //获取链表长度
    T& Value(int);                //获取给定位置的值
	T& Head();
	T& Tail();

	T *Array();                   //将元素重新填入数组中，返回数组，会复制元素

};
//声明结束

//========================================================================================================


//以下是link<T>（链表节点)的函数定义
template <typename T> link<T>::link() //构造函数
{
	PreNode = NULL;
	NextNode = NULL;
}


template <typename T> link<T>::link(T &data) //构造函数
{
	Value = data;
	PreNode = NULL;
	NextNode = NULL;
}

template <typename T> link<T>::link(link<T> &lk)  //拷贝构造函数
{
	Value = lk.Value;
	PreNode = NULL;
	NextNode = NULL;
}

template <typename T> link<T>::~link()        //析构函数
{
	PreNode = NULL;
	NextNode = NULL;
}

template <typename T> void link<T>::setData(T &data)   //设置值     
{
	Value = &data;
}
//--------

//以下是linkedlisk<T>链表的函数定义

	//==================================
	//定义
template <typename T> linkedlist<T>::linkedlist() //构造函数,创建空链表
{
	headernode = new link<T>;
	headernode->PreNode = headernode;
	headernode->NextNode = headernode;

	l = 0;
}
template <typename T> template <typename TArr> linkedlist<T>::linkedlist(TArr& Arr, int n)  //根据数组创建链表  参数（数组，链表大小) 如链表大小为-1则为默认数组长度
{
	link<T> *p, *pPre;
	int len = sizeof(Arr) / sizeof(Arr[0]);

	headernode = new link<T>;
	if ((n == -1) || (n > l)) n = l;
	if (n <= 0)
	{
		headernode->PreNode = headernode;
		headernode->NextNode = headernode;
		l = 0;
		return;
	}

	pPre = headernode;
	for (int i = 0;i < n;i++)
	{
		p = new link<T>(Arr[i]);
		p->PreNode = pPre;
		pPre->NextNode = p;
		pPre = p;
	}

	headernode->PreNode = p;
	p->NextNode = headernode;

	l = n;                                                             //长度=设定长度
}

template <typename T> linkedlist<T>::linkedlist(std::initializer_list<T> initlist) //使用初始化表构造链表
{
	link<T> *p, *pPre;
	T tTemp;

	headernode = new link<T>;

	if (initlist.size() <= 0)
	{
		headernode->PreNode = headernode;
		headernode->NextNode = headernode;
		l = 0;
		return;
	}

	p = headernode;
	for (auto tp = initlist.begin(); tp != initlist.end(); tp++)
	{
		pPre = p;
		tTemp = *tp;
		p = new link<T>(tTemp);
		p->PreNode = pPre;
		pPre->NextNode = p;
	}

	headernode->PreNode = p;
	p->NextNode = headernode;
	l = initlist.size();
}

template <typename T> linkedlist<T>::linkedlist(linkedlist<T>& list)   // 拷贝构造函数
{

	headernode = new link<T>;
	headernode->PreNode = headernode;
	headernode->NextNode = headernode;
	l = 0;

	int l1 = Length();
	int l2 = list.Length();
	for (int i = 0; i < min(l1, l2); i++) 
	{
		Value(i) = list.Value(i);
	}
	if (l1 < l2)
	{
		for (int i = l1; i < l2; i++)
		{
			Append(list.Value(i));
		}
	}
	else if (l1 > l2)
	{
		for (int i = l2; i < l1; l++)
		{
			Delete(i);
		}
	}

	l = l2;                                                         //长度=被复制链表的长度
}
//-----------
template <typename T> linkedlist<T>::~linkedlist()                   //析构函数  
{
	for (int i =0; i<Length(); i++)
	{
		Delete(i);
	}
	delete headernode;
}

template <typename T> void linkedlist<T>::operator=(linkedlist<T>& list)  //重载赋值 使其变为复制
{
	if (headernode == NULL)
	{
		headernode = new link<T>;
		headernode->PreNode = headernode;
		headernode->NextNode = headernode;
		l = 0;
	}
	int l1 = Length();
	int l2 = list.Length();
	for (int i = 0; i < min(l1, l2); i++)
	{
		Value(i) = list.Value(i);
	}
	if (l1 < l2)
	{
		for (int i = l1; i < l2; i++)
		{
			Append(list.Value(i));
		}
	}
	else if (l1 > l2)
	{
		for (int i = l2; i < l1; i++)
		{
			Delete(i);
		}
	}

	l = l2;
}
//---------------
template <typename T> link<T>& linkedlist<T>::Append(T& data)          //于尾部添加一个值
{
	return Insert(data, Length());
}
//----------------------
template <typename T> link<T>& linkedlist<T>::Insert(T& data,int i)   //于给定位置添加一个值，其他值顺延
{
	link<T> *p = new link<T>(data);

	i = min(Length(), max(0, i));                  //i必须位于0到最大长度之间

	p->PreNode = iNode(i - 1);
	p->NextNode = iNode(i);

	p->PreNode->NextNode = p;
	p->NextNode->PreNode = p;

	l++;                                          //长度+1

	return *p;
}

template <typename T> bool linkedlist<T>::Delete(int i) //删除给定位置的值，如超限会返回失败
{
	link<T> *p = pNode(i);
	if (p == NULL) return false;                                   //如没有此节点返回失败

	p->PreNode->NextNode = p->NextNode;
	p->NextNode->PreNode = p->PreNode;
	delete p;

	l--;                                                          //长度-1
	return true;
}

template <typename T> void linkedlist<T>::Clear() //清空链表
{
	while (Delete(0)) {}                                                  //长度-1
}

template <typename T> linkedlist<T>& linkedlist<T>::Turn()                  //转置链表，首变为尾尾变为首；
{
	link<T> *p, *pTemp;

	p = headernode;
	do
	{
		pTemp = p->PreNode;
		p->PreNode = p->NextNode;
		p->NextNode = pTemp;
		
		p = p->PreNode;
	} while (p != headernode);

	return *this;
}

template <typename T> bool linkedlist<T>::operator==(linkedlist<T>& list)
{
	link<T> *p1, *p2;
	if (Length() != list.Length()) return false;
	p1 = headernode->NextNode;
	p2 = list.headernode->NextNode;

	while (p1 != headernode)
	{
		if (p1->Value != p2->Value) return false;
		p1 = p1->NextNode;
		p2 = p2->NextNode;
	}
	return true;
}

template <typename T> bool linkedlist<T>::operator!=(linkedlist<T>& list)
{
	return (!operator==(list));
}

template <typename T>  link<T>*linkedlist<T>::iNode(int i)           //返回指向特定节点的指针,不限上下限
{
	link<T> *p = NULL;
	                                                                 //如果超限返回NULL
	p = headernode;
	for (int j = 0; j <= i; j++)
	{
		p = p->NextNode;
	}
	for (int j = 0; j > (i + 1); j--)
	{
		p = p->PreNode;
	}
	return p;
}


template <typename T>  link<T>*linkedlist<T>::pNode(int i)           //返回指向特定节点的指针
{
	link<T> *p = NULL;
	if (i < 0|| i >= Length()) return NULL;                        //如果超限返回NULL
	p = headernode;
	for (int j = 0; j <= i; j++)
	{
		p = p->NextNode;
	}
	return p;
}

template <typename T> link<T> *linkedlist<T>::pHead()                                                      //返回指向首节点的指针
{
	if (l > 0) return headernode->NextNode;
	return NULL;
}

template <typename T> link<T> *linkedlist<T>::pTail()
{
	if (l > 0) return headernode->PreNode;
	return NULL;
}

template <typename T> int linkedlist<T>::Length()
{
	return l;
}

template <typename T> T& linkedlist<T>::Value(int i)
{
	return pNode(i)->Value;
}

template <typename T> T& linkedlist<T>::Head()
{
	return pHead()->Value;
}

template <typename T> T& linkedlist<T>::Tail()
{
	return pTail()->Value;
}

template <typename T> T *linkedlist<T>::Array()
{
	T *a;
	a = new T[Length()];
	for (int i = 0; i < Length();i++)
	{
		a[i] = Value(i);
	}

	return a;
}