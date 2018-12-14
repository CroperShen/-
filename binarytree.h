//=============================================
//BinaryTree.h
//Create by CroperShen
//last modified in Dec.15.2018
//�������������ϰ֮��
//����Ķ�����������һ����һ�ö�������һ�������Ĵ���ṹ����"����"����ʹ��SubTree�������ɣ����򲢲���һ�ô��������ϵ���
//==============================================
#pragma once
#define DEBUGMODE true

#include <stack>
#include <queue>
#include "doublepointer.h"
#include "linkedlist.h"

using std::stack;
using std::queue;

enum Childpos{ pos_left = 0,pos_right=1,pos_root=2,pos_def=-1};
enum TreeOrder{order_pre,order_in,order_post,order_level,order_def=order_level};

template <typename> class BinaryTreeNode;
template <typename> class BinaryTree;

template <typename T> class BinaryTreeNode
{
	friend class BinaryTree<T>;
private:
	T Value;
	BinaryTreeNode<T> *Parent;
	BinaryTreeNode<T> *LeftChild;
	BinaryTreeNode<T> *RightChild;
	BinaryTree<T> *Tree;                      //�����ڵ���Ч��ָ�����ڵ���

	int Order;
    //====================��������======================
	BinaryTreeNode();                         //���캯��
	BinaryTreeNode(const T&);                 //���캯��
	BinaryTreeNode(const BinaryTreeNode<T>&); //�������캯��
	~BinaryTreeNode();                        //��������

	const T& value() const;                                //����ֵ
	const bool isroot() const;                             //�Ƿ��Ǹ��ڵ�
	const bool isleaf() const;                             //�Ƿ���Ҷ�ڵ�
	const int depth() const;                               //�ڵ�ĸ߶�
	const Childpos pos() const;                            //���ؽڵ��λ��
	BinaryTreeNode<T>* child(Childpos) const;
	BinaryTreeNode<T>* leftchild() const;                  //���������ӽڵ� 
	BinaryTreeNode<T>* rightchild() const;                 //�����ӽڵ�
	BinaryTreeNode<T>* parent() const;                     //���ظ��ڵ�
	BinaryTreeNode<T>* sibing(Childpos = pos_def) const;   //ָ���ֵܽڵ��ָ�룬û���򷵻�NULL
	BinaryTreeNode<T>* leftsibing() const;                 //�������ֵ�
	BinaryTreeNode<T>* rightSibing() const;                //�������ֵ�
	BinaryTree<T>* tree() const;                           //�������ڵ���
	int order() const;                                     //���������еĴ���


	BinaryTreeNode<T>& operator=(T&);                   //���ظ�ֵ���ţ�ֱ�Ӷ�Data��ֵ����ͬ��setData
	BinaryTreeNode<T>& operator=(BinaryTreeNode<T>&);   


	void SetValue(T&);                                         //����ֵ 

	void SetLeftChild(BinaryTreeNode<T>*, bool=false);                     //���������ӽڵ�,���趨�Ƿ�������ӽڵ�
	void SetRightChild(BinaryTreeNode<T>*,bool=false);
	void SetChild(BinaryTreeNode<T>*,const Childpos=pos_def,bool=false);  
	void SetParent(BinaryTreeNode<T>*, const Childpos = pos_def);          //���ø��ڵ�
	void Swap(BinaryTreeNode<T>*, bool = false);                           //���ض��ڵ㽻��,���趨�Ƿ����ӽڵ�һ�𽻻�

	const bool AddLeftChild(const T&);                         //���Ӹ���ֵ�������ӽڵ㣬�����Ƿ���ӳɹ�
	const bool AddRightChild(const T&);                        
	const bool AddChild(const T&, Childpos = pos_def);         
};

template <typename T> class BinaryTree
{
	friend class BinaryTreeNode<T>;
private:
	BinaryTreeNode<T> *Root;                         //���ڵ�
	TreeOrder Order;                                 //Ĭ�����δ���
	linkedlist<BinaryTreeNode<T>*> OrderList;        //����ڵ�Ĵ���
    int Size;                                        //�������Ĵ�С
	bool WellOrdered;                                 //�������Ƿ��Ѿ������
													 //���������Ķ���WellOrdered��Ϊfalse����������Ҫ�������ʵ�ֵĺ���ʱ�����WellOrdered�����Ϊ����������ٽ��в�����
public:
	BinaryTree();                                    //���캯��
	BinaryTree(const BinaryTree<T>&);                //���ƹ��캯��
	BinaryTree(const std::initializer_list<T>&);     //���ݳ�ʼ�����캯��
	BinaryTree(const linkedlist<T>&);                //���������캯��
	BinaryTree(BinaryTreeNode<T>&);                  //���ݽڵ㼰���ӽڵ㴴����
	~BinaryTree();                                   //��������
	   
	const int size();
	const bool empty() const;                   //�Ƿ�Ϊ����
	const bool height();                        //�߶�
	BinaryTreeNode<T> *root() const;            //ָ����ڵ��ָ�룬û���򷵻�NULL
    BinaryTreeNode<T> *node(int) ;              //Ĭ�����δ����µ�ָ���ڵ�
	const T& value(int);

	void SetRoot(BinaryTreeNode<T>&);          //���ø��ڵ�
	void SetValue(int, const T&);                  //
	void Clear();                              //�����

	//���ζ�����
	TreeOrder treeorder() const;
	void SetTreeOrder(const TreeOrder);
	void ForTree(void(*)(BinaryTreeNode<T>&));    //�����趨�������� 
	void DoOrder();                               //��������
};

//�������ڵ㺯���Ķ���

template <typename T> BinaryTreeNode<T>::BinaryTreeNode()  //���캯��
{ 
	LeftChild = NULL;
	RightChild = NULL;
	Parent = NULL;
	Tree = NULL;
	Order = -1;
}
template <typename T> BinaryTreeNode<T>::BinaryTreeNode(const T& t) //���캯��
{
	Value = t;
	LeftChild = NULL;
	RightChild = NULL;
	Parent = NULL;
	Tree = NULL;
	Order = -1;
}

template <typename T> BinaryTreeNode<T>::BinaryTreeNode(const BinaryTreeNode<T>& t) //�������캯��
{
	Value = t.Value;
	LeftChild = NULL;
	RightChild = NULL;
	Parent = NULL;
	Tree = NULL;
	Order = -1;
}

template <typename T> BinaryTreeNode<T>::~BinaryTreeNode()  //��������
{
	if (LeftChild != NULL) LeftChild->Parent = NULL;
	if (RightChild != NULL) RightChild->Parent = NULL;
	if (Parent != NULL)
	{
		if (Parent->LeftChild == this) Parent->LeftChild = NULL;
		if (Parent->RightChild == this) Parent->RightChild = NULL;
	}
}

template <typename T> inline const T& BinaryTreeNode<T>::value() const                                 //����ֵ
{
	return Value;
}

template <typename T> inline const bool BinaryTreeNode<T>::isroot() const                             //�Ƿ��Ǹ��ڵ�
{
	if (Parent != NULL) return false;
	if (tree()== NULL) return false;
	if (tree()->root != this) return false;
	return true;
}

template <typename T> inline const bool BinaryTreeNode<T>::isleaf() const                             //�Ƿ���Ҷ�ڵ�
{
	return ((LeftChild == NULL) && (RightChild == NULL));
}

template <typename T> const int BinaryTreeNode<T>::depth() const                                           //�ڵ�����
{
	int i = 0;
	BinaryTreeNode<T>* p = Parent;
	while (p != NULL)
	{
		i++;
		p = p->Parent;
	}
	return i;
}

template <typename T> const Childpos BinaryTreeNode<T>::pos() const                                  //���ؽڵ��λ��
{
	if (Parent == NULL) return pos_root;
	if (Parent->LeftChild == this) return pos_left;
	return pos_right;
}

template <typename T> inline BinaryTreeNode<T>* BinaryTreeNode<T>::child(Childpos pos) const                  //�����ӽڵ� 
{
	switch (pos)
	{
	case pos_left:
		return LeftChild;
	case pos_right:
		return RightChild;
	case pos_def:
		if (LeftChild != NULL) return LeftChild;
		return RightChild;
	}
	return NULL;
}

template <typename T> inline BinaryTreeNode<T>* BinaryTreeNode<T>::leftchild() const                  //�������ӽڵ� 
{
	return LeftChild;
}
template <typename T> inline BinaryTreeNode<T>* BinaryTreeNode<T>::rightchild() const                 //�������ӽڵ�
{
	return RightChild;
}
template <typename T> inline BinaryTreeNode<T>* BinaryTreeNode<T>::parent() const                     //���ظ��ڵ�
{
	return Parent;
}

template <typename T> inline BinaryTreeNode<T>* BinaryTreeNode<T>::sibing(Childpos pos) const   //�����ֵܽڵ�
{
	if (Parent== NULL) return NULL;
	switch (pos)
	{
	case pos_left:
		if (Parent->RightChild == this) return Parent->LeftChild;
		return NULL;
	case pos_right:
		if (Parent->LeftChild == this) return Parent->RightChild;
		return NULL;
	case pos_def:
		if (Parent->RightChild == this) return Parent->LeftChild;
		if (Parent->LeftChild == this) return Parent->RightChild;
	}
	return NULL;
}

template <typename T> inline BinaryTreeNode<T>* BinaryTreeNode<T>::leftsibing() const                 //�������ֵ�
{
	if (Parent == NULL) return NULL;
	if (Parent->RightChild == this) return Parent->LeftChild;
	return NULL;
}
template <typename T> inline BinaryTreeNode<T>* BinaryTreeNode<T>::rightSibing() const                //�������ֵ�
{
	if (Parent == NULL) return NULL;
	if (Parent->LeftChild == this) return Parent->RightChild;
	return NULL;
}

template <typename T> inline BinaryTree<T>* BinaryTreeNode<T>::tree() const                             //�������ڵ���
{
	const BinaryTreeNode<T> *p = this;
	while (p->Parent == NULL) p = p->Parent;
	return p->Tree;
}


template <typename T> inline int BinaryTreeNode<T>::order() const                             //ȷ�������еĴ���
{
	if (tree() == NULL) return -1;
	if (tree()->WellOrderd == false) Tree->DoOrder();
	return Order;
}


template <typename T> BinaryTreeNode<T>& BinaryTreeNode<T>::operator=(T& t)                   //���ظ�ֵ���ţ�ֱ�Ӷ�Data��ֵ����ͬ��setData
{
	Value = t;
	return *this;
}

template <typename T> BinaryTreeNode<T>& BinaryTreeNode<T>::operator=(BinaryTreeNode<T>& t)   //���ظ�ֵ���ţ�ֱ�Ӷ�Data��ֵ����ͬ��setData
{
	Value = t.Value;
	return *this;
}

template <typename T> void BinaryTreeNode<T>::SetValue(T& t)                                          //����ֵ        
{
	Value = t;
}

template <typename T> void BinaryTreeNode<T>::SetLeftChild(BinaryTreeNode<T>* p,bool withchild)                            //�������ӽڵ�
{	
	if (LeftChild == p) return;    //�����ͬ�������κθĶ�
	if (p == NULL) if (tree() != NULL) tree()->WellOrdered = false;
	if (tree()!=p->tree())
	{
		if (tree() != NULL) tree()->WellOrdered = false;
		if (p->tree() != NULL) p->tree()->WellOrdered = false;
	}
	if (LeftChild != NULL) LeftChild->Parent = NULL;
	LeftChild = p;
	if (p!=NULL)
	{
	    p->Parent = this;
		if (withchild==false)
		{ 
	        p->LeftChild = NULL;
	        p->RightChild = NULL;
		}
	}
}

template <typename T> void BinaryTreeNode<T>::SetRightChild(BinaryTreeNode<T>* p,bool withchild)                            //�������ӽڵ�
{
	if (RightChild == p) return;    //�����ͬ�������κθĶ�
	if (p == NULL) if (tree() != NULL) tree()->WellOrdered = false;
	if (tree() != p->tree())
	{
		if (tree() != NULL) tree()->WellOrdered = false;
		if (p->tree() != NULL) p->tree()->WellOrdered = false;
	}
	if (RightChild != NULL) RightChild->Parent = NULL;
	RightChild = p;
	if (p != NULL)
	{
		p->Parent = this;
		if (withchild == false)
		{
			p->LeftChild = NULL;
			p->RightChild = NULL;
		}
	}
}

template <typename T> void BinaryTreeNode<T>::SetChild(BinaryTreeNode<T>* p, const Childpos pos,bool withchild)                            //���������ӽڵ�
{
	BinaryTreeNode<T> **pChild;
	if ((pos == pos_def) || (pos == pos_left))
	{
		pChild = &LeftChild;
	}
	else if (pos == pos_right)
	{
		pChild = &RightChild;
	}
	else return;

	if (*pChild == p) return;    //�����ͬ�������κθĶ�
	if (p == NULL) if (tree() != NULL) tree()->WellOrdered = false;
	if (tree() != p->tree())
	{
		if (tree() != NULL) tree()->WellOrdered = false;
		if (p->tree() != NULL) p->tree()->WellOrdered = false;
	}
	if (*pChild != NULL) (*pChild)->Parent = NULL;
	*pChild = p;
	if (p != NULL)
	{
		p->Parent = this;
		if (withchild == false)
		{
			p->LeftChild = NULL;
			p->RightChild = NULL;
		}
	}
}


template <typename T> void BinaryTreeNode<T>::SetParent(BinaryTreeNode<T>* p, const Childpos pos1)                            //���������ӽڵ�
{
	BinaryTreeNode<T> **pChild;
	Childpos pos0 = pos();

	if (p != NULL) if (p->child(pos0) == this) return;    //���pָ���������ĸ��ڵ���λ����ȷ�򲻽��д���
	if (isroot()) tree()->Root = NULL;                    //����Ǹ��ڵ��򽫶�Ӧ���ĸ��ڵ���ΪNULL ������Ҳû�ж�����������
	if (tree() != NULL) tree()->WellOrdered = false;      //�������λ��һ��������ô���������WellOrdered��Ϊfalse

	if (pos0 == pos_left) Parent->LeftChild = NULL;        //����������ӽڵ㣬���븸ĸ�Ͼ���ϵ
	if (pos0 == pos_right) Parent->RightChild = NULL;


	Parent = p;
	Tree = NULL;
	if (p != NULL)
	{
		switch (pos1)
		{
		case pos_left:
		     p->LeftChild = this;
		case pos_right:
			 p->RightChild = this;
		case pos_def:
			if ((p->LeftChild != NULL) && (p->RightChild == NULL)) p->RightChild = this;
			p->LeftChild = this;
		}
		if (tree() != NULL) tree()->WellOrdered = false;
	}
}


template <typename T> void BinaryTreeNode<T>::Swap(BinaryTreeNode<T>* p, bool withchild)                            //�����ڵ�
{
	BinaryTreeNode<T> *pTemp;
	BinaryTree<T> *tr1, *tr2;
	Childpos pos1, pos2;

	if (p == this) return;  //���pָ����������򲻽��д���
	if (p == NULL)          //���pΪNULL����Ϊ�������Ƴ����ڵ�
	{
		tr1 = tree();
		pos1 = pos();
		if (tr1 != NULL) tr1->WellOrdered = false;
		if (isroot()) tr1->root = NULL;
		if (pos = pos_left) Parent->LeftChild = NULL;
		if (pos = pos_right) Parent->RightChild = NULL;

		Parent = NULL;
		Tree = NULL;
		if (withchild == false)
		{
			if (LeftChild != NULL) LeftChild->Parent = NULL;
			if (RightChild != NULL) RightChild->Parent = NULL;
			LeftChild = NULL;
			RightChild = NULL;
		}
		return;
	}

	tr1 = tree();
	tr2 = p->tree();
	if (tr1!= tr2)
	{
		if (tr1 != NULL) tr1->WellOrdered = false;
		if (tr2 != NULL) tr2->WellOrdered = false;
	}
	if (isroot())
	{
		tr1->root = p;
		p->Tree = tr1;
	}

	if (p->isroot())
	{
		tr2->root = this;
		Tree = tr2;
	}

	pos1 = pos();
	pos2 = p->pos();

	if (pos1 == pos_left) Parent->LeftChild = p;
	if (pos1 == pos_right)Parent->RightChild = p;
	if (pos2 == pos_left) p->Parent->LeftChild = this;
	if (pos2 == pos_right) p->Parent->RightChild = this;

	pTemp = Parent;
	Parent = p->Parent;
	p->Parent = pTemp;


	if (withchild == false)
	{
		if (LeftChild != NULL) LeftChild->Parent = p;
		if (p->LeftChild != NULL) p->LeftChild->Parent = this;
		if (RightChild != NULL) RightChild->Parent = p;
		if (p->RightChild != NULL) p->RightChild=this;

		pTemp = LeftChild;
		LeftChild = p->LeftChild;
		p->LeftChild = pTemp;
		pTemp = RightChild;
		RightChild = p->RightChild;
		p->RightChild = pTemp;
	}
}

template <typename T> const bool  BinaryTreeNode<T>::AddChild(const T& t, const Childpos pos)                            //���Ӹ���ֵ�������ӽڵ�,�����Ƿ���ӳɹ�
{
	BinaryTreeNode<T> *child;

	switch (pos)
	{
		case pos_left:
		    if (LeftChild != NULL) return false;
			child = new BinaryTreeNode<T>(t);
			child->Parent = this;
			LeftChild = child;
			if (tree() != NULL) tree()->WellOrdered == false;
			return true;
		case pos_right:
			if (RightChild != NULL) return false;
			child = new BinaryTreeNode<T>(t);
			child->Parent = this;
			RightChild = child;
			if (tree() != NULL) tree()->WellOrdered == false;
			return true;
		case pos_def:
			if (LeftChild == NULL)
			{
				child = new BinaryTreeNode<T>(t);
				child->Parent = this;
				LeftChild = child;
				if (tree() != NULL) tree()->WellOrdered == false;
				return true;
			}
			else if (RightChild == NULL)
			{
				child = new BinaryTreeNode<T>(t);
				child->Parent = this;
				RightChild = child;
				if (tree() != NULL) tree()->WellOrdered == false;
				return true;
			}
	}
	return false;
}

template <typename T> const bool  BinaryTreeNode<T>::AddLeftChild(const T& t)                            //���Ӹ���ֵ�����ӽڵ�,�����Ƿ���ӳɹ�
{
	BinaryTreeNode<T> *child;

	if (LeftChild != NULL) return false;
	child = new BinaryTreeNode<T>(t);
	child->Parent = this;
	LeftChild = child;
	return true;

	if (tree() != NULL) tree()->WellOrdered = false;
}

template <typename T> const bool  BinaryTreeNode<T>::AddRightChild(const T& t)                            //���Ӹ���ֵ�����ӽڵ�,�����Ƿ���ӳɹ�
{
	BinaryTreeNode<T> *child;

	if (RightChild != NULL) return false;
	child = new BinaryTreeNode<T>(t);
	child->Parent = this;
	RightChild = child;
	return true;

	if (tree() != NULL) tree()->WellOrdered = false;
}

//================================================================================
	//����

template <typename T> BinaryTree<T>::BinaryTree()                                    //���캯��
{
	Root = NULL;
	Order = order_def;
	WellOrdered = true;
	Size = 0;
}

template <typename T> BinaryTree<T>::BinaryTree(const BinaryTree<T>& tree)                //���ƹ��캯��
{                                                                   
	Order = tree.Order;
	Root = NULL;
	if (tree.Root == NULL) return;                                          //���treeΪ�����򴴽�һ������                          
	BinaryTree<T>(*tree.root());                                            //����tree�ĸ��ڵ㴴������
}

template <typename T> BinaryTree<T>::BinaryTree(const std::initializer_list<T>& list)     //���ݳ�ʼ��������ȫ������
{
	//������Ϊ��ȫ������
	BinaryTreeNode<T> *Node;
	Size = list.size();
	Order = order_def;
	Root = NULL;
	if (Size == 0) return;

	Node = new BinaryTreeNode<T>[Size];
	auto p = list.begin();
	for (int i=0; i < Size; i++)
	{
		Node[i].SetValue((T)p[i]);
		if (2 * i + 1 < Size) Node[i].SetLeftChild(Node[2 * i + 1]);
		if (2 * i + 2 < Size) Node[i].SetRightChild(Node[2 * i + 2]);
	}
}

template <typename T> BinaryTree<T>::BinaryTree(const linkedlist<T>& list)                 //������������ȫ������
{
	//������Ϊ��ȫ������
	BinaryTreeNode<T> *Node;
	Size = list.size();
	Order = order_def;
	Root = NULL;
	if (Size == 0) return;

	Node = new BinaryTreeNode<T>[Size];
	for (int i = 0; i < Size; i++)
	{
		Node[i].SetValue(list.value(i));
		if (2 * i + 1 < Size) Node[i].SetLeftChild(Node[2 * i + 1]);
		if (2 * i + 2 < Size) Node[i].SetRightChild(Node[2 * i + 2]);
	}
}

template <typename T> BinaryTree<T>::BinaryTree(BinaryTreeNode<T>& Node)             //���ݽڵ㼰���ӽڵ㴴����
{
	dpointer<BinaryTreeNode<T>>  p, pNext;
	stack<dpointer<BinaryTreeNode<T>>> stk;

	Root = new BinaryTreeNode<T>(Node);                       //���ȸ��Ƹ��ڵ�
	p.p1 = &Node;
	p.p2 = Root;
	do
	{
		if (p.p1->RightChild != NULL)
		{
			p.p2->AddRightChild(p.p1->RightChild->value());
			pNext.p1 = p.p1->RightChild;
			pNext.p2 = p.p2->RightChild;
			stk.push(pNext);
		}
		if (p.p1->LeftChild != NULL)
		{
			p.p2->AddLeftChild(p.p1->LeftChild->value());
		}
		p.p1 = p.p1->LeftChild;
		p.p2 = p.p2->LeftChild;

		if (p.p1 == NULL)
		{
			if (!stk.empty())
			{
				p = stk.top();
				stk.pop();
			}
		}
	} while ((p.p1 != NULL) || (!stk.empty()));
}

template <typename T> BinaryTree<T>::~BinaryTree()                                   //��������
{
	for (int i = Size - 1; i >= 0; i--) delete node(i);

}

template <typename T> void BinaryTree<T>::DoOrder()                                   //����
{
	queue<BinaryTreeNode<T>*> que;
	stack<BinaryTreeNode<T>*> stk;
	BinaryTreeNode<T> *p;
	if (WellOrdered) return;
	Size = 0;
	OrderList.Clear();

	if (Root == NULL) return;

	switch (Order)
	{
	case order_level:                 
		que.push(Root);
		while (!que.empty())
		{
			p = que.front();
			que.pop();
			OrderList.Append(p);
			p->Order = Size;
			Size++;
			if (p->LeftChild != NULL) que.push(p->LeftChild);
			if (p->RightChild != NULL) que.push(p->RightChild);
		}
	case order_pre:
		p = Root;
		while (p!=NULL)
		{
			while (p != NULL)
			{
				OrderList.Append(p);
				p->Order = Size;
				Size++;
				if (p->RightChild != NULL) stk.push(p->RightChild);
				p = p->LeftChild;
			}
			if (!stk.empty())
			{
				p = stk.top();
				stk.pop();
			}
		}
	case order_in:
		p = Root;
		do
		{
			while (p != NULL)
			{
				stk.push(p);
				p = p->LeftChild;
			}

			p = stk.top();
			stk.pop();

			OrderList.Append(p);
			p->Order = Size;
			Size++;
			p = p->RightChild;
		}while ((p != NULL) || (!stk.empty()));

	case order_post:                 //�������Ϊ������ǰ���ٽ��з�ת����������д��̫�鷳
		p = Root;
		while (p != NULL)
		{
			while (p != NULL)
			{
				OrderList.Append(p);
				Size++;
				if (p->LeftChild != NULL) stk.push(p->LeftChild);
				p = p->RightChild;
			}
			if (!stk.empty())
			{
				p = stk.top();
				stk.pop();
			}
		}
		OrderList.Turn();
		for (int i = 0; i < Size; i++)
		{
			OrderList.value(i)->Order = i;
		}
	}

	WellOrdered = true;
}


template <typename T> const int BinaryTree<T>::size()
{
	if (WellOrdered == false) DoOrder();
	return Size;
}

template <typename T> const bool BinaryTree<T>::empty() const                   //�Ƿ�Ϊ����
{
	return (Root == false);
} 
template <typename T> const bool BinaryTree<T>::height()                       //�߶�
{
	int maxheight = 0;
	int h1;
	if (WellOrdered == false) DoOrder();
	for (int i = 0; i < Size; i++)
	{
		h1 = value(i)->depth();
		if (h1 > maxheight) maxheight = h1;
	}
	return maxheight;
}
template <typename T> BinaryTreeNode<T> *BinaryTree<T>::root() const      //ָ����ڵ��ָ�룬û���򷵻�NULL
{
	return Root;
}
template <typename T> BinaryTreeNode<T> *BinaryTree<T>::node(int i)       //Ĭ�����δ����µ�ָ���ڵ�
{
	if (WellOrdered == false) DoOrder();
	return OrderList.value(i);
}
template <typename T> const T& BinaryTree<T>::value(int i)
{
	if (WellOrdered == false) DoOrder();
	return OrderList->value(i)->Value;
}


template <typename T> void BinaryTree<T>::SetRoot(BinaryTreeNode<T>& t)   //���ø��ڵ�
{
	if (Root == &t) return;
	WellOrdered == false;
	Root = &t;
    t.SetParent(NULL);
	t.Tree = this;
}

template <typename T> void BinaryTree<T>::SetValue(int i, const T& t)   //���ø��ڵ�
{
	if (WellOrdered == false) DoOrder();
	OrderList.value(i)->Value = t;
}
template <typename T> void BinaryTree<T>::Clear()                   //�����
{
	if (Root == NULL) return;
	for (int i = 0;i <= Size; i++)
	{
		delete OrderList.value(i);
	}
	WellOrdered = false;
}
template <typename T> inline TreeOrder BinaryTree<T>::treeorder() const
{
	return Order;
}
template <typename T> void BinaryTree<T>::SetTreeOrder(const TreeOrder)
{
	if (Order == TreeOrder) return;
	Order = TreeOrder;
	WellOrdered = false;
}
template <typename T> void BinaryTree<T>::ForTree(void(*func1)(BinaryTreeNode<T>&))    //�����趨�������� 
{
	BinaryTreeNode<T> *p;
	if (WellOrdered = false) DoOrder();
	for (int i = 0; i < Size; i++)
	{
		p = OrderList.value(i);
		func1(*p);
	}
}