//linkedlist.h
//Created by CroperShen
//Last modified in Dec.11.2018
//����ṹ����ϰ֮��


#pragma once

#include <initializer_list>
#include <stdlib.h>

//������
template <typename T> class link;                  //����ڵ�
template <typename T> class linkedlist;            //����

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
//�����������

//=======================================================

//��Ķ���
template <typename T> class link    //����ڵ�
{
	friend class linkedlist<T>;
private:
	T Value;  // ֵ��
	link<T> *PreNode;
	link<T> *NextNode;
public:
	link();  //���캯��,
	link(T&);  //���캯��,
	link(link<T>&); //���ƹ��캯��
	~link();  //��������

	void setData(T&);    //����ֵ      
};

//-----------------------------
template <typename T> class linkedlist //����
{
private:
	link<T> *headernode;  //ͷ�ڵ�,Ϊ��ڵ�,ͷ�ڵ��NextNodeΪ�׽ڵ㣬PreNodeΪβ�ڵ�;
	int l;    //����
protected:
	link<T> *iNode(int);         //��ȡָ���ڵ㣬����������(ѭ��)
	link<T> *pNode(int);       //��ȡָ���ڵ㣬����������(����NULL)
	link<T> *pHead();
	link<T> *pTail();
public:

	linkedlist();                 //���캯��,����������
	template <typename TArr> linkedlist(TArr&, int=-1);      //�������鴴������  ���������飬�����С) �������СΪ-1��ΪĬ�����鳤��
	linkedlist(std::initializer_list<T>); //ʹ�ó�ʼ����������
	linkedlist(linkedlist<T>&);   //�������캯��
	~linkedlist();                //��������  
	void operator=(linkedlist<T>&);             //���ظ�ֵ ʹ���Ϊ����

	inline bool empty() { return (l == 0); }    //�Ƿ��ǿ�����
	link<T>& Append(T&);          //��β�����һ��ֵ
	link<T>& Insert(T&,int);      //�ڸ���λ�����һ��ֵ������ֵ˳��
	bool Delete(int);             //ɾ������λ�õ�ֵ���糬�޻᷵��ʧ��
	void Clear();                  //�������
	linkedlist<T>& Turn();                  //ת�������ױ�Ϊββ��Ϊ�ף�

    virtual bool operator==(linkedlist<T>&);    //������ȣ�ֻ��������ÿһ��Ԫ�ض���ȫ��ͬʱ�����;
	virtual bool operator!=(linkedlist<T>&);    //�������;

	int Length();                 //��ȡ������
    T& Value(int);                //��ȡ����λ�õ�ֵ
	T& Head();
	T& Tail();

	T *Array();                   //��Ԫ���������������У��������飬�Ḵ��Ԫ��

};
//��������

//========================================================================================================


//������link<T>������ڵ�)�ĺ�������
template <typename T> link<T>::link() //���캯��
{
	PreNode = NULL;
	NextNode = NULL;
}


template <typename T> link<T>::link(T &data) //���캯��
{
	Value = data;
	PreNode = NULL;
	NextNode = NULL;
}

template <typename T> link<T>::link(link<T> &lk)  //�������캯��
{
	Value = lk.Value;
	PreNode = NULL;
	NextNode = NULL;
}

template <typename T> link<T>::~link()        //��������
{
	PreNode = NULL;
	NextNode = NULL;
}

template <typename T> void link<T>::setData(T &data)   //����ֵ     
{
	Value = &data;
}
//--------

//������linkedlisk<T>����ĺ�������

	//==================================
	//����
template <typename T> linkedlist<T>::linkedlist() //���캯��,����������
{
	headernode = new link<T>;
	headernode->PreNode = headernode;
	headernode->NextNode = headernode;

	l = 0;
}
template <typename T> template <typename TArr> linkedlist<T>::linkedlist(TArr& Arr, int n)  //�������鴴������  ���������飬�����С) �������СΪ-1��ΪĬ�����鳤��
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

	l = n;                                                             //����=�趨����
}

template <typename T> linkedlist<T>::linkedlist(std::initializer_list<T> initlist) //ʹ�ó�ʼ����������
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

template <typename T> linkedlist<T>::linkedlist(linkedlist<T>& list)   // �������캯��
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

	l = l2;                                                         //����=����������ĳ���
}
//-----------
template <typename T> linkedlist<T>::~linkedlist()                   //��������  
{
	for (int i =0; i<Length(); i++)
	{
		Delete(i);
	}
	delete headernode;
}

template <typename T> void linkedlist<T>::operator=(linkedlist<T>& list)  //���ظ�ֵ ʹ���Ϊ����
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
template <typename T> link<T>& linkedlist<T>::Append(T& data)          //��β�����һ��ֵ
{
	return Insert(data, Length());
}
//----------------------
template <typename T> link<T>& linkedlist<T>::Insert(T& data,int i)   //�ڸ���λ�����һ��ֵ������ֵ˳��
{
	link<T> *p = new link<T>(data);

	i = min(Length(), max(0, i));                  //i����λ��0����󳤶�֮��

	p->PreNode = iNode(i - 1);
	p->NextNode = iNode(i);

	p->PreNode->NextNode = p;
	p->NextNode->PreNode = p;

	l++;                                          //����+1

	return *p;
}

template <typename T> bool linkedlist<T>::Delete(int i) //ɾ������λ�õ�ֵ���糬�޻᷵��ʧ��
{
	link<T> *p = pNode(i);
	if (p == NULL) return false;                                   //��û�д˽ڵ㷵��ʧ��

	p->PreNode->NextNode = p->NextNode;
	p->NextNode->PreNode = p->PreNode;
	delete p;

	l--;                                                          //����-1
	return true;
}

template <typename T> void linkedlist<T>::Clear() //�������
{
	while (Delete(0)) {}                                                  //����-1
}

template <typename T> linkedlist<T>& linkedlist<T>::Turn()                  //ת�������ױ�Ϊββ��Ϊ�ף�
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

template <typename T>  link<T>*linkedlist<T>::iNode(int i)           //����ָ���ض��ڵ��ָ��,����������
{
	link<T> *p = NULL;
	                                                                 //������޷���NULL
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


template <typename T>  link<T>*linkedlist<T>::pNode(int i)           //����ָ���ض��ڵ��ָ��
{
	link<T> *p = NULL;
	if (i < 0|| i >= Length()) return NULL;                        //������޷���NULL
	p = headernode;
	for (int j = 0; j <= i; j++)
	{
		p = p->NextNode;
	}
	return p;
}

template <typename T> link<T> *linkedlist<T>::pHead()                                                      //����ָ���׽ڵ��ָ��
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